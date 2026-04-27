# Firmware: ESP32 IoT Gateway

This folder contains the source code for the ESP32 microcontroller, which acts as a gateway between BLE sensors and the AWS Cloud.

## 🚀 Key Features
* **NTP Synchronization:** Automatically syncs with `pool.ntp.org` to ensure valid TLS handshakes with AWS.
* **BLE Data Parsing:** Decodes Xiaomi Mi advertisement packets to extract temperature and humidity data.
* **Secure Connection:** Uses `WiFiClientSecure` for 1.2 TLS encrypted communication.

## 🛠 Setup
1. Define your Wi-Fi and AWS credentials in `secrets.h`.
2. Set the Arduino IDE Partition Scheme to **"Huge APP"**.
