#include <OneWire.h>
#include <DallasTemperature.h>

// Assign a separate pin for each sensor
#define SENSOR1_PIN 2
#define SENSOR2_PIN 3
#define SENSOR3_PIN 4

// Create OneWire instances for each sensor
OneWire oneWire1(SENSOR1_PIN);
OneWire oneWire2(SENSOR2_PIN);
OneWire oneWire3(SENSOR3_PIN);

// Pass each to its own DallasTemperature instance
DallasTemperature sensor1(&oneWire1);
DallasTemperature sensor2(&oneWire2);
DallasTemperature sensor3(&oneWire3);

void setup() {
  Serial.begin(9600);
  Serial.println("=== DS18B20 - 3 Sensors (Separate Pins) ===");

  sensor1.begin();
  sensor2.begin();
  sensor3.begin();
}

void loop() {
  // Request temperatures from each sensor
  sensor1.requestTemperatures();
  sensor2.requestTemperatures();
  sensor3.requestTemperatures();

  float temp1 = sensor1.getTempCByIndex(0);
  float temp2 = sensor2.getTempCByIndex(0);
  float temp3 = sensor3.getTempCByIndex(0);

  Serial.print("Sensor 1: "); Serial.print(temp1); Serial.println(" °C");
  Serial.print("Sensor 2: "); Serial.print(temp2); Serial.println(" °C");
  Serial.print("Sensor 3: "); Serial.print(temp3); Serial.println(" °C");
  Serial.println("-------------------------");

  delay(2000);
}
