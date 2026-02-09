# Code: breakdown!

## Transmitter: ESP32-S3(box-3)

### 1. Library Initialization

The transmitter uses WiFi.h, WiFiClientSecure.h, and PubSubClient.h to enable Wi-Fi connectivity and secure MQTT communication over TLS (MQTTS). This ensures encrypted communication with the cloud broker.

### 2. Network & Broker Configuration

Wi-Fi credentials and HiveMQ Cloud broker details (hostname, port, username, and password) are defined. The broker operates on port 8883, which is the standard port for secure MQTT connections.

### 3. MQTT Client Setup

A WiFiClientSecure object is used to handle TLS communication, which is passed to PubSubClient. Certificate verification is disabled using setInsecure() to accommodate embedded memory limitations.

### 4. MQTT Reconnection Logic

The reconnect() function continuously attempts to establish a secure MQTT connection if the client is disconnected. A unique client ID is generated on each attempt to prevent broker conflicts.

### 5. Command Publishing Mechanism

The sendCommand() function dynamically constructs MQTT topics in the format
home/channel/<channel_number>/set
and publishes "ON" or "OFF" payloads. Messages are sent with the retained flag enabled, ensuring state persistence.

### 6. User Input Handling

The transmitter reads commands via the Serial interface in the format:
<channel_number> <ON/OFF>
Input is validated to ensure only channels 1–7 are accepted before publishing commands.

### 7. Main Execution Loop

The loop maintains the MQTT connection, processes incoming/outgoing MQTT traffic, and listens for user input to issue control commands in real time.



## RECEIVER (ESP8266)

### 1. Library Initialization

The receiver uses ESP8266WiFi.h, WiFiClientSecure.h, and PubSubClient.h to connect securely to the same MQTT broker and receive control commands.

### 2. Hardware Configuration

Seven GPIO pins are configured as outputs to control seven relay channels. Each relay is mapped to a specific channel number (1–7) for structured control.

### 3. Network & Broker Configuration

The receiver uses the same Wi-Fi credentials and HiveMQ Cloud broker details as the transmitter, ensuring seamless communication within the same MQTT ecosystem.

### 4. MQTT Topic Structure

The receiver subscribes to:

home/channel/+/set → to receive relay control commands

home/esp8266/get_states → to respond with current relay states

It also publishes:

home/channel/<n>/state → relay state feedback

home/esp8266/status → online/offline availability

### 5. Incoming Message Processing

The MQTT callback function:

Extracts the channel number from the topic

Interprets the payload (ON / OFF)

Switches the corresponding relay

Publishes the updated relay state for synchronization

### 6. State Synchronization

The publishAllStates() function publishes the status of all relay channels. This enables system recovery and state restoration after reboot or reconnection.

### 7. MQTT Reliability & Availability

A Last Will and Testament (LWT) message is configured so that the receiver automatically reports "Offline" if it disconnects unexpectedly, improving system reliability.

### 8. Main Execution Loop

The loop continuously maintains MQTT connectivity and processes incoming commands with minimal latency.