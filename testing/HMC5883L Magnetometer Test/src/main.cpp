#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

#define POWER 23

// This time I'm testing it as a compass because I have never tried it
// and this is one of the main uses for a magnetometer.

void displaySensorDetails(void) {
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print("Sensor:       "); Serial.println(sensor.name);
  Serial.print("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
}

void setup() {
  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, LOW);
  delay(100);
  digitalWrite(POWER, HIGH);
  delay(500);
  Serial.begin(115200);
  Serial.println("HMC5883L Magnetometer Test"); Serial.println("");


  if(!mag.begin()) {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }

  displaySensorDetails();
  mag.setMagGain(HMC5883_MAGGAIN_8_1);
  Serial.println("Gain set to +/- 8.1 Ga");
}

void loop() {
  sensors_event_t event; 
  mag.getEvent(&event);
  
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  delay(500);
}