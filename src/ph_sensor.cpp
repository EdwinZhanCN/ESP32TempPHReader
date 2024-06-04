#include <Arduino.h>
#include "ph_sensor.h"

#define PH_PIN 34
#define ADC_RESOLUTION 4095.0f
#define VOLTAGE 3.3f

void initPHSensor() {
    //
}


float readPH() {

    int val = analogRead(PH_PIN);
    Serial.println("ADC: " + String(val));
    float voltage = val * (VOLTAGE / ADC_RESOLUTION);

    Serial.println("Voltage: " + String(voltage));
    // Calculate the slope and intercept from the given data points
    float slope = (4.00 - 6.86) / (2.2 - 1.7); // Change in pH / Change in voltage
    float intercept = 4.00 - slope * 2.2; // pH - slope * voltage

    // Calculate the pH value from the voltage
    float phValue = slope * voltage + intercept;

    delay(300);

    return phValue;
}


