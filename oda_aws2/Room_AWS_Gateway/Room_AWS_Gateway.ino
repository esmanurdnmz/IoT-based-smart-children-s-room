#include <WiFi.h>
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <time.h>

#define AWS_IOT_PUBLISH_TOPIC   "sensor/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "sensor/sub"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
BLEScan* pBLEScan;
const int scanTime = 5; // BLE tarama süresi

float lastTemperature = 0.0;
int lastHumidity = 0;
bool dataReadyToSend = false;
unsigned long lastScanTime = 0;

void syncClock() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Saat eşitleniyor");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {  // 1970'ten uzak bir zaman
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println(" -> Zaman ayarlandı!");

  Serial.print("Cihaz saati: ");
  Serial.println(ctime(&now));
}

void connectAWS() {
  Serial.println("AWS IoT'ye bağlanılıyor...");
  Serial.print("Free heap: ");
  Serial.println(ESP.getFreeHeap());

  client.setServer(AWS_IOT_ENDPOINT, 8883);

  int retries = 0;
  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    Serial.print(" Hata kodu: ");
    Serial.println(client.state());  // MQTT durum kodu
    delay(1000);
    retries++;
    if (retries > 10) {
      Serial.println("\nAWS bağlantı hatası! Saat, sertifika veya policy kontrol edilmeli.");
      return;
    }
  }

  Serial.println("\nAWS IoT'ye bağlandı!");
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
}

void publishSensorData(float temperature, int humidity) {
  StaticJsonDocument<200> doc;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
  Serial.print("AWS'ye veri gönderildi: ");
  Serial.println(jsonBuffer);
}

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.haveName() && advertisedDevice.getName().startsWith("ATC_")) {
      if (advertisedDevice.haveServiceData()) {
        String serviceData = advertisedDevice.getServiceData();
        const uint8_t* data = (const uint8_t*)serviceData.c_str();
        int dataLength = serviceData.length();

        if (dataLength >= 13) {
          int16_t tempRaw = (data[6] << 8) | data[7];
          float temperature = tempRaw / 10.0;
          int humidity = data[8];

          lastTemperature = temperature;
          lastHumidity = humidity;
          dataReadyToSend = true;

          Serial.print("Tespit edilen sıcaklık: ");
          Serial.print(temperature);
          Serial.print(" °C, Nem: ");
          Serial.print(humidity);
          Serial.println(" %");
        }
      }
    }
  }
};

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("WiFi bağlanıyor...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi bağlı!");

  syncClock();  // 🔐 TLS için zorunlu

  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  connectAWS();

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {
  client.loop();

  if (!client.connected()) {
    Serial.print("MQTT bağlantısı koptu. Kod: ");
    Serial.println(client.state());
    connectAWS();
  }

  if (dataReadyToSend && client.connected()) {
    publishSensorData(lastTemperature, lastHumidity);
    dataReadyToSend = false;
  }

  if (millis() - lastScanTime > 60000) {
    Serial.println("BLE taraması başlatılıyor...");
    pBLEScan->start(scanTime, true); // Non-blocking
    lastScanTime = millis();
  }

  delay(250);
}
