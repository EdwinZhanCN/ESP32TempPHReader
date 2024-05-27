#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DFRobot_PH.h>


// 定义连接 DS18B20 的 GPIO 引脚
const int oneWireBus = 14; 

// 设置 OneWire 实例
OneWire oneWire(oneWireBus);

// 传递 oneWire 引用给 Dallas Temperature 库
DallasTemperature sensors(&oneWire);

void setup() {
  // 初始化串口通信
  Serial.begin(9600);

  // 启动 Dallas Temperature 库
  sensors.begin();
}

void loop() {
  // 请求温度
  sensors.requestTemperatures();
  

  // 获取温度（摄氏度）
  float temperatureC = sensors.getTempCByIndex(0);

  // 通过串口输出温度
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // 延时1秒
  delay(1000);
}