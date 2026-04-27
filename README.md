# IoT-Based Smart children-s Room Monitoring System


This project is an end-to-end IoT ecosystem developed under the **TÜBİTAK 2209-A University Students Research Projects Support Program**. Its primary goal is to provide continuous, secure, and real-time monitoring of environmental factors (temperature and humidity) in a baby's room.

> 💡 **Note:** This repository contains the **IoT Edge Node, Gateway, and Server (Cloud/Database)** layers of the project. The mobile application component is managed by our teammate and is therefore not included in this repository.

## 🏗 System Architecture

The system features a multi-layered architecture where low-cost hardware integrates with robust cloud computing and local server architectures:

1. **Sensing Layer (Edge Nodes):** Xiaomi Mi 2 BLE sensors collect ambient temperature and humidity data.
2. **Gateway:** The ESP32 microcontroller parses sensor data via BLE and transmits it to **AWS IoT Core** (MQTT) over Wi-Fi, establishing a secure TLS 1.2 connection.
3. **Server Layer:** **Node-RED** running on a Raspberry Pi 4 subscribes to AWS IoT, retrieves the data, processes it, and saves it to a **MongoDB** database with a timestamp.
4. **User Interface (Mobile App):** Users log into the system via an Android (Kotlin)-based mobile application using Firebase authentication to monitor real-time environmental data.

## 🚀 Technologies Used

* **Hardware:** ESP32 Development Board, Raspberry Pi 4 Model B (8GB), Xiaomi Mi 2 BLE Sensor
* **Cloud & Communication:** AWS IoT Core, MQTT, Bluetooth Low Energy (BLE), TLS/SSL
* **Server & Database:** Node.js, Node-RED, MongoDB

## 📂 Repository Structure

* 📁 `oda_aws2/`: ESP32 Gateway C++ source codes and AWS TLS certificate templates.
* 📁 `server/`: Diagrams illustrating the Node-RED flow logic on the Raspberry Pi (`Logic_Explanation.jpeg`) and dashboard visuals.
* 📁 `documentation/`: TÜBİTAK final report, project architectural diagrams, and research outputs.

## ⚙️ Setup and Execution

1. Rename the `secrets_template.h` file in the `oda_aws2/Room_AWS_Gateway/` directory to `secrets.h` and enter your Wi-Fi and AWS IoT certificate credentials. Upload it to the ESP32 via the Arduino IDE. (Partition Scheme must be set to "Huge APP").
2. Complete the Node-RED and MongoDB installations on the Raspberry Pi. To set up the system flow on Node-RED, you can reference the node architecture in the `server/Logic_Explanation.jpeg` image. (Since the hardware is no longer active, the original `flows.json` file is not included in the repository).

## 👥 Team and Contributors

* **İhsan Yiğit ÖNAY** - Project Manager (System integration, hardware setup, and testing)
* **Esmanur DÖNMEZ** - Developer (AWS IoT cloud architecture, Node-RED server integration, and database management)
* **Berna ÇELİK** - Developer (Requirements analysis and test optimizations)
* **Assist. Prof. Dr. Ebru AYDOĞAN** - Project Advisor

---
*For detailed analysis and hardware test results, please refer to the TÜBİTAK Final Report in the `documentation` folder.*
