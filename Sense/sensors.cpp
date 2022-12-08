#include "sensors.h"

#include <Arduino_LSM9DS1.h>

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
  Serial.println("X\tY\tZ");

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");

  Serial.print("Magnetic field sample rate = ");
  Serial.print(IMU.magneticFieldSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Magnetic Field in uT");
  Serial.println("X\tY\tZ");
}

void sensors_init() {
  
  sensors_init_imu();
}

void read_accelerometer_data(float &x, float &y, float &z) {
  
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }
}

void read_gyroscope_data(float &x, float &y, float &z) {
  
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
  }
}

void read_magnetomer_data(float &x, float &y, float &z) {

  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(x, y, z);
  }
}
