# Server-Side Implementation

The server-side layer is the central intelligence of the system, hosted on a **Raspberry Pi 4 Model B**. It processes, stores, and visualizes the environmental data received from the cloud.

## ⚙️ Technologies Used
* **Node-RED:** A flow-based development tool for visual programming of IoT logic.
* **MQTT:** Protocol used to subscribe to AWS IoT Core topics.
* **MongoDB:** A NoSQL database for high-availability sensor data storage.
* **Node-RED Dashboard:** For real-time monitoring of environmental data.

## 🔄 The Data Flow
1. **Subscription:** Node-RED subscribes to the `sensor/pub` topic on AWS IoT Core using secure credentials.
2. **Parsing:** Incoming JSON payloads are parsed to extract `temperature` and `humidity` values.
3. **Storage:** The processed data is timestamped and saved into a MongoDB collection named `Ortam1.ortam`.
4. **Visualization:** Data is pushed to gauge nodes on the web dashboard for real-time tracking.

## 📊 System Features
* **Real-time Gauges:** Instant display of current room conditions on the dashboard.
* **Backend Alert Infrastructure:** Node-RED HTTP endpoints and email nodes are configured to trigger background alerts if values exceed safety thresholds.

### Logic Nodes Explanation
Since the system is flow-based, the core logic consists of the following nodes (visualized in `Logic_Explanation.jpeg`):
- **MQTT In:** Listens to the AWS Cloud.
- **JSON Node:** Converts the raw buffer into a readable JavaScript object.
- **Function Nodes:** Extracts specific values (like temperature and humidity) and formats them for database and API requests.
- **MongoDB Out:** Persists the validated data to the database.

> 💡 **Note:** The original `flows.json` file is omitted since the hardware is no longer active, but the complete node logic is documented in the provided diagram.
