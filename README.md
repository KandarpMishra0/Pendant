# MQTT-Based Home Automation System Using ESP32-S3 and ESP8266

## 1. Introduction
This project presents a secure and scalable home automation system based on the Message Queuing Telemetry Transport (MQTT) protocol. The system enables remote control of multiple electrical loads through cloud-based communication, making it suitable for modern Internet of Things (IoT) applications.

The design follows a distributed architecture in which control logic and hardware actuation are separated. An ESP32-S3 module functions as the transmitter, publishing control commands to a cloud-hosted MQTT broker, while an ESP8266 module acts as the receiver, subscribing to these commands and controlling relay channels accordingly.

---

## 2. System Architecture
The system uses a publisher–subscriber communication model implemented via an MQTT broker hosted on HiveMQ Cloud.

- The transmitter publishes control messages to predefined MQTT topics.
- The receiver subscribes to these topics and performs hardware-level switching.
- The MQTT broker handles message routing and ensures secure, reliable data exchange.

All communication between devices and the broker is encrypted using Transport Layer Security (TLS).

---

## 3. Hardware Components
- ESP32-S3 (Transmitter Unit)
- ESP8266 (Receiver Unit)
- 7-Channel Relay Module
- Wi-Fi Network
- External power supply for relay module

---

## 4. Software Technologies
- MQTT Protocol
- HiveMQ Cloud (MQTTS, Port 8883)
- Arduino Framework
- PubSubClient Library
- WiFiClientSecure Library

---

## 5. Communication Protocol
The project uses MQTT topics to organize control commands, state feedback, and system status.

- Control Topic Format:  
  `home/channel/<channel_number>/set`

- State Feedback Topic Format:  
  `home/channel/<channel_number>/state`

- Device Status Topic:  
  `home/esp8266/status`

Control messages use simple string payloads (`ON` / `OFF`) to minimize overhead and simplify parsing.

---

## 6. Functional Description
The transmitter connects to the MQTT broker over a secure connection and publishes control commands based on user input. Each command specifies the target relay channel and desired state.

The receiver continuously listens for incoming control messages. Upon receiving a valid command, it switches the corresponding relay channel and publishes the updated state back to the broker. The receiver also supports state synchronization and online/offline status reporting.

---

## 7. Key Features
- Secure MQTT communication using TLS
- Cloud-based remote control of electrical loads
- Independent control of seven relay channels
- Structured MQTT topic hierarchy
- Real-time command execution and state feedback
- Retained messages for state persistence
- Device availability monitoring using Last Will and Testament (LWT)
- Modular and scalable system design

---

## 8. Applications
- Smart home automation
- Remote appliance control
- IoT-based switching systems
- Educational and academic demonstrations

---

## 9. Future Scope
The system can be extended to support mobile applications, voice assistants, web dashboards, or integration with home automation platforms. Additional sensors and automation logic can be incorporated without altering the core communication architecture.

---

## 10. Conclusion
This project demonstrates a practical implementation of a secure MQTT-based home automation system using ESP32-S3 and ESP8266 microcontrollers. By leveraging cloud communication and modular design principles, the system provides a reliable foundation for scalable IoT automation solutions.
