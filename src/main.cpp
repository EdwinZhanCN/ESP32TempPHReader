#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <PubSubClient.h>
#include <ESPAsyncWebServer.h>
#include "temperature_sensor.h"
#include "ph_sensor.h"
#include "wifi_connection.h"

// WiFi credentials
const char* ssid = "2L left";
const char* password = "Zzh041126";

// MQTT broker settings
const char* mqtt_server = "192.168.124.9";
const int mqtt_port = 9001;
// const char* mqtt_user = "your_mqtt_username"; // if needed
// const char* mqtt_password = "your_mqtt_password"; // if needed

WiFiClient espClient;
PubSubClient client(espClient);

// Callback function for handling incoming messages
void callback(char* topic, byte* payload, unsigned int length) {
    // Handle incoming messages here (if needed)
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP32Client")) {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("outTopic", "hello world");
            // ... and resubscribe
            client.subscribe("inTopic");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void setup() {
    //start a server
    AsyncWebServer server(80);
    
    Serial.begin(9600);

    initTemperatureSensor();
    initPHSensor();
    initWiFi(ssid, password, server);

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);

    while (!client.connected()) {
        reconnect();
    }
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    float temperature = readTemperature();
    float phValue = readPH();
    String tempload = "{\"temperature\":" + String(temperature) + "}";
    String phload = "{\"ph\":" + String(phValue) + "}";

    
    client.publish("sensor/temp", tempload.c_str());
    client.publish("sensor/ph", phload.c_str());
    
    delay(5000); // Publish data every 5 seconds
}

