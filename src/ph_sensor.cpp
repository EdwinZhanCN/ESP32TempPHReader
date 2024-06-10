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
    
    // Calculate the pH value from the voltage
    float phValue = (-5.88 * voltage + 22.98)/2;

    delay(300);

    return phValue;
}


