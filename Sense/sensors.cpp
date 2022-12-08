#include "sensors.h"

#include <Arduino_LSM9DS1.h>
#include <Arduino_HTS221.h>

static void sensors_init_imu() {

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");

  Serial.print("Magnetic field sample rate = ");
  Serial.print(IMU.magneticFieldSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Magnetic Field in uT");
}

static void sensors_init_environmental() {

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

   Serial.println("HTS221 initialized");
}

void sensors_init() {
  
  sensors_init_imu();
  sensors_init_environmental();
}

void sensors_read_accelerometer_data(float &x, float &y, float &z) {
  
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }
}

void sensors_read_gyroscope_data(float &x, float &y, float &z) {
  
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
  }
}

void sensors_read_magnetomer_data(float &x, float &y, float &z) {

  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(x, y, z);
  }
}

float sensors_read_temperature_data() {
  return HTS.readTemperature();
}

float sensors_read_humidity_data() {
  return HTS.readHumidity();
}

