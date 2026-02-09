// Here is the source code for the transmitter component of the project. This code is responsible for sending data to a receiver and ensuring that it is transmitted correctly. The transmitter will typically take input from a user or another source, format it appropriately, and then send it over a communication channel to the receiver.
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "Realme";
const char* WIFI_PASSWORD = "ufju8614";

const char* MQTT_SERVER = "6562275e78db4a36bde88e4e8f6d87d2.s1.eu.hivemq.cloud";
const int MQTT_PORT = 8883;

const char* MQTT_USER = "jyotirmoy";
const char* MQTT_PASSWORD = "jon0987J@";

const char* SET_TOPIC_PREFIX = "home/channel/";

WiFiClientSecure espClientSecure;
PubSubClient client(espClientSecure);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    String clientId = "ESP32S3-TX-" + String(random(0xffff), HEX);

    espClientSecure.setInsecure();

    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(3000);
    }
  }
}

void sendCommand(int channel, const char* command) {
  char topic[50];
  snprintf(topic, 50, "%s%d/set", SET_TOPIC_PREFIX, channel);

  client.publish(topic, command, true);

  Serial.print("Sent -> ");
  Serial.print(topic);
  Serial.print(" : ");
  Serial.println(command);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int spaceIndex = input.indexOf(' ');
    if (spaceIndex > 0) {
      int channel = input.substring(0, spaceIndex).toInt();
      String command = input.substring(spaceIndex + 1);
      command.toUpperCase();

      if (channel >= 1 && channel <= 7 &&
          (command == "ON" || command == "OFF")) {
        sendCommand(channel, command.c_str());
      } else {
        Serial.println("Invalid command");
      }
    }
  }
}

