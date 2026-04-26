# Server-Side Implementation

The server-side layer is the central intelligence of the system, hosted on a **Raspberry Pi 4 Model B**. It processes, stores, and visualizes the environmental data received from the cloud.

## ⚙️ Technologies Used
* **Node-RED:** A flow-based development tool for visual programming of IoT logic.
* **MQTT:** Protocol used to subscribe to AWS IoT Core topics.
* **MongoDB:** A NoSQL database for high-availability sensor data storage.
* **Node-RED Dashboard:** For real-time monitoring and historical trend analysis.

## 🔄 The Data Flow
1. **Subscription:** Node-RED subscribes to the `sensor/pub` topic on AWS IoT Core using secure credentials.
2. **Parsing:** Incoming JSON payloads are parsed to extract `temperature` and `humidity` values.
3. **Storage:** The processed data is timestamped and saved into a MongoDB collection named `RoomData`.
4. **Visualization:** Data is pushed to gauge and chart nodes on the web dashboard.

## 📊 Dashboard Features
* **Real-time Gauges:** Instant display of current room conditions.
* **Historical Charts:** 24-hour temperature and humidity trend lines.
* **Alert Logic:** Triggers notifications if values exceed pre-defined safety thresholds.

### Logic Nodes Explanation
Since the system is flow-based, the core logic consists of the following nodes:
- **MQTT In:** Listens to the AWS Cloud.
- **JSON Node:** Converts the raw buffer into a readable JavaScript object.
- **Function Node:** Filters out noise and validates data ranges (e.g., Temperature between -10°C and 50°C).
- **MongoDB Out:** Persists the validated data to the database.