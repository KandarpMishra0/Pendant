# Key features!

### • Secure MQTT (MQTTS) communication using HiveMQ Cloud  
  Ensures encrypted and authenticated message exchange between transmitter and receiver over the internet.

### • Encrypted TLS-based data transfer  
  Protects control commands and device status data from interception or tampering during transmission.

### • 7-channel relay control with scalable architecture  
  Allows independent control of seven electrical loads and can be easily extended to more channels.

### • Structured topic hierarchy for clean command routing  
  Uses well-defined MQTT topics to separate control commands, state updates, and system status.

### • Real-time ON/OFF control via cloud messaging  
  Enables instantaneous switching of relays from a remote transmitter through the MQTT broker.

### • Retained MQTT messages for state persistence  
  Preserves the last known relay state so devices can recover correctly after reboot or reconnection.

### • Device online/offline status monitoring  
  Publishes availability information using MQTT LWT to detect unexpected device disconnections.

### • Automatic reconnection and fault tolerance  
  Continuously attempts reconnection to Wi-Fi and MQTT broker to maintain uninterrupted operation.

### • Separation of control and execution units  
  Improves system modularity by isolating command generation from hardware actuation logic.

### • Expandable to voice control, mobile apps, or dashboards  
  The MQTT-based design allows seamless integration with voice assistants, apps, and web interfaces.

### • Suitable for smart home and IoT automation systems  
  Designed following industry-standard IoT communication practices for real-world deployment.
