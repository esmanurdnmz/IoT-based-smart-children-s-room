# IoT-Based Smart children-s Room Monitoring System


This project is an end-to-end IoT ecosystem developed under the **TÜBİTAK 2209-A University Students Research Projects Support Program**[cite: 2]. Its primary goal is to provide continuous, secure, and real-time monitoring of environmental factors (temperature and humidity) in a baby's room[cite: 213].

> 💡 **Note:** This repository contains the **IoT Edge Node, Gateway, and Server (Cloud/Database)** layers of the project[cite: 248, 273]. The mobile application component is managed by our teammate and is therefore not included in this repository.

## 🏗 System Architecture

The system features a multi-layered architecture where low-cost hardware integrates with robust cloud computing and local server architectures[cite: 220]:

1. **Sensing Layer (Edge Nodes):** Xiaomi Mi 2 BLE sensors collect ambient temperature and humidity data[cite: 420].
2. **Gateway:** The ESP32 microcontroller parses sensor data via BLE and transmits it to **AWS IoT Core** (MQTT) over Wi-Fi, establishing a secure TLS 1.2 connection[cite: 221, 224, 225].
3. **Server Layer:** **Node-RED** running on a Raspberry Pi 4 subscribes to AWS IoT, retrieves the data, processes it, and saves it to a **MongoDB** database with a timestamp[cite: 273, 279, 294].
4. **User Interface (Mobile App):** Users log into the system via an Android (Kotlin)-based mobile application using Firebase authentication to monitor real-time environmental data[cite: 348, 353, 386].

## 🚀 Technologies Used

* **Hardware:** ESP32 Development Board [cite: 221], Raspberry Pi 4 Model B (8GB) [cite: 273], Xiaomi Mi 2 BLE Sensor [cite: 420]
* **Cloud & Communication:** AWS IoT Core [cite: 224], MQTT [cite: 224], Bluetooth Low Energy (BLE) [cite: 221], TLS/SSL [cite: 225]
* **Server & Database:** Node.js [cite: 278], Node-RED [cite: 278], MongoDB [cite: 293]

## 📂 Repository Structure

* 📁 `oda_aws2/`: ESP32 Gateway C++ source codes and AWS TLS certificate templates.
* 📁 `server/`: Diagrams illustrating the Node-RED flow logic on the Raspberry Pi (`Logic_Explanation.jpeg`) and dashboard visuals.
* 📁 `documentation/`: TÜBİTAK final report, project architectural diagrams, and research outputs.

## ⚙️ Setup and Execution

1. Rename the `secrets_template.h` file in the `oda_aws2/Room_AWS_Gateway/` directory to `secrets.h` and enter your Wi-Fi and AWS IoT certificate credentials. Upload it to the ESP32 via the Arduino IDE. (Partition Scheme must be set to "Huge APP").
2. Complete the Node-RED and MongoDB installations on the Raspberry Pi[cite: 278, 293]. To set up the system flow on Node-RED, you can reference the node architecture in the `server/Logic_Explanation.jpeg` image[cite: 279]. (Since the hardware is no longer active, the original `flows.json` file is not included in the repository).

## 👥 Team and Contributors

* **İhsan Yiğit ÖNAY** - Project Manager (System integration, hardware setup, and testing) [cite: 8]
* **Esmanur DÖNMEZ** - Developer (AWS IoT cloud architecture, Node-RED server integration, and database management) [cite: 149]
* **Berna ÇELİL** - Developer (Requirements analysis and test optimizations) [cite: 149]
* **Assist. Prof. Dr. Ebru AYDOĞAN** - Project Advisor [cite: 208]

---
*For detailed analysis and hardware test results, please refer to the TÜBİTAK Final Report in the `documentation` folder.*
