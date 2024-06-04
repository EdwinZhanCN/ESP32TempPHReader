#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "temperature_sensor.h"
#include "ph_sensor.h"
#include "wifi_connection.h"

AsyncWebServer server(9128);

const char* ssid = "2L left";
const char* password = "Zzh041126";

void setup() {
    Serial.begin(9600);

    initTemperatureSensor();
    initPHSensor();
    initWiFi(ssid, password, server);

    server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest *request){
        float temperature = readTemperature();
        float phValue = readPH();
        String json = "{\"temperature\":" + String(temperature) + ", \"ph\":" + String(phValue) + "}";
        request->send(200, "application/json", json);
    });
}

void loop() {
    // 空循环
    Serial.print("Temperature: ");
    Serial.print(readTemperature());
    Serial.println(" °C");
    Serial.print("PH: ");
    Serial.println(readPH());
    delay(1000);
}
