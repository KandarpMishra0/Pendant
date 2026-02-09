// Here is the source code for the Receiver component of the project. This code is responsible for receiving data from a sender and processing it accordingly.

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

const int CHANNEL_PINS[] = {D0, D1, D2, D4, D5, D6, D7};
const int NUM_CHANNELS = 7;
const int RELAY_ON_STATE = HIGH;
const int RELAY_OFF_STATE = LOW;

const char* WIFI_SSID = "Realme";
const char* WIFI_PASSWORD = "ufju8614";

const char* MQTT_SERVER = "6562275e78db4a36bde88e4e8f6d87d2.s1.eu.hivemq.cloud";
const int MQTT_PORT = 8883;

const char* MQTT_USER = "jyotirmoy";
const char* MQTT_PASSWORD = "jon0987J@";

const char* STATUS_TOPIC = "home/esp8266/status";
const char* SET_TOPIC_PREFIX = "home/channel/";
const char* STATE_TOPIC_PREFIX = "home/channel/";
const char* GET_STATES_TOPIC = "home/esp8266/get_states";

WiFiClientSecure espClientSecure;
PubSubClient client(espClientSecure);

void publishAllStates() {
  for (int i = 0; i < NUM_CHANNELS; i++) {
    int channelId = i + 1;
    bool isRelayOn = (digitalRead(CHANNEL_PINS[i]) == RELAY_ON_STATE);

    char stateTopic[50];
    snprintf(stateTopic, 50, "%s%d/state", STATE_TOPIC_PREFIX, channelId);
    client.publish(stateTopic, isRelayOn ? "ON" : "OFF", true);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  char messageBuffer[length + 1];
  memcpy(messageBuffer, payload, length);
  messageBuffer[length] = '\0';
  String message = String(messageBuffer);
  message.toUpperCase();

  String topicStr(topic);

  if (topicStr.startsWith(SET_TOPIC_PREFIX) && topicStr.endsWith("/set")) {
    int start = String(SET_TOPIC_PREFIX).length();
    int end = topicStr.length() - String("/set").length();
    int channelId = topicStr.substring(start, end).toInt();

    if (channelId >= 1 && channelId <= NUM_CHANNELS) {
      int pinIndex = channelId - 1;
      bool turnOn = (message == "ON");

      digitalWrite(CHANNEL_PINS[pinIndex], turnOn ? RELAY_ON_STATE : RELAY_OFF_STATE);

      char stateTopic[50];
      snprintf(stateTopic, 50, "%s%d/state", STATE_TOPIC_PREFIX, channelId);
      client.publish(stateTopic, turnOn ? "ON" : "OFF", true);
    }
  }

  if (topicStr.equals(GET_STATES_TOPIC)) {
    publishAllStates();
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTTS connection...");
    String clientId = "ESP8266-HomeHub-" + String(random(0xffff), HEX);

    espClientSecure.setInsecure();

    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD,
                       STATUS_TOPIC, 1, true, "Offline")) {
      char setTopic[50];
      snprintf(setTopic, 50, "%s+/set", SET_TOPIC_PREFIX);
      client.subscribe(setTopic);
      client.subscribe(GET_STATES_TOPIC);

      client.publish(STATUS_TOPIC, "Online", true);
      publishAllStates();
    } else {
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_CHANNELS; i++) {
    pinMode(CHANNEL_PINS[i], OUTPUT);
    digitalWrite(CHANNEL_PINS[i], RELAY_OFF_STATE);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
