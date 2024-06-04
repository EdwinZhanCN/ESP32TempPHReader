#include <OneWire.h>
#include <DallasTemperature.h>
#include "temperature_sensor.h"

#define ONE_WIRE_BUS 14 // DS18B20 数据线连接的GPIO

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void initTemperatureSensor() {
    sensors.begin();
}

float readTemperature() {
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
}
