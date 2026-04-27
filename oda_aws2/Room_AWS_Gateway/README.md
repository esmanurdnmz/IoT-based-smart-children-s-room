# Firmware: ESP32 IoT Gateway

This folder contains the source code for the ESP32 microcontroller, which acts as a gateway between BLE sensors and the AWS Cloud.

## 🚀 Key Features
* **NTP Synchronization:** Automatically syncs with `pool.ntp.org` to ensure valid TLS handshakes with AWS.
* **BLE Data Parsing:** Scans and decodes advertisement packets from Xiaomi Mi sensors (specifically looking for the `ATC_` prefix indicating custom firmware) to extract temperature and humidity data.
* **Secure Connection:** Uses `WiFiClientSecure` for TLS 1.2 encrypted communication.

## 🛠 Setup
1. Rename the `secrets_template.h` file to `secrets.h`.
2. Define your actual Wi-Fi credentials, AWS IoT Endpoint, and Certificates inside `secrets.h`.
3. Set the Arduino IDE Partition Scheme to **"Huge APP (3MB No OTA/1MB SPIFFS)"**.
4. Compile and upload to your ESP32 board.
