#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "wifi_connection.h"

void initWiFi(const char* ssid, const char* password, AsyncWebServer& server) {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    server.begin();
}
