#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

#define POWER 23
#define LED 19

float tolerance = 150; // Tolerance for detecting a significant change in magnetic field measured in uT
sensors_event_t initial_event; // Variable to store the initial magnetic field event
float initial_magnitude = 0; // Variable to store the initial magnitude of the magnetic field

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
  Serial.println("Gain set to +/- 8.1 Ga");
  Serial.println("------------------------------------");
  Serial.println("");
}

void setup() {
  pinMode(POWER, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(POWER, LOW);
  delay(100);
  digitalWrite(POWER, HIGH);
  delay(2000);
  Serial.begin(115200);
  Serial.println("HMC5883L Magnetometer Test"); Serial.println("");


  if(!mag.begin()) {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }

  displaySensorDetails();
  mag.setMagGain(HMC5883_MAGGAIN_8_1);

  // Dummy event to get rid of bad first reading
  mag.getEvent(&initial_event);
  delay(500);

  Serial.println("Starting initial calibrations..."); Serial.println("");
  mag.getEvent(&initial_event);
  Serial.print("Initial X: "); Serial.print(initial_event.magnetic.x); Serial.print("  ");
  Serial.print("Initial Y: "); Serial.print(initial_event.magnetic.y); Serial.print("  ");
  Serial.print("Initial Z: "); Serial.print(initial_event.magnetic.z); Serial.print("  ");Serial.println("uT");
  initial_magnitude = sqrt(pow(initial_event.magnetic.x, 2) + pow(initial_event.magnetic.y, 2) + pow(initial_event.magnetic.z, 2));
  Serial.print("Initial Magnitude: "); Serial.print(initial_magnitude); Serial.println(" uT");
  Serial.println("Initial calibration complete."); Serial.println("");
  Serial.println("------------------------------------");
  Serial.println("");
}

void loop() {
  sensors_event_t event; 
  mag.getEvent(&event);
  
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  float magnitude = sqrt(pow(event.magnetic.x, 2) + pow(event.magnetic.y, 2) + pow(event.magnetic.z, 2));
  Serial.print("Magnitude: "); Serial.print(magnitude); Serial.println(" uT");

  if (magnitude > initial_magnitude + tolerance)
  {
    Serial.println("Magnet detected!");
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }

  delay(500);
}