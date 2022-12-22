#include "SensorManager.h"

#include <Arduino_LSM9DS1.h>
#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>

const int ENVIRONMENTAL_SENSORS_READ_DELAY_MS = 500;

void SensorManager::initSensors() {
 
  initImu();
  initEnvironmentalSensors();
}

void SensorManager::readAcceleration(float destination[]) {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(this->acceleration[0], this->acceleration[1], this->acceleration[2]);      
  }

  memcpy(destination, this->acceleration, 3*sizeof(float));
}

void SensorManager::readGyroscope(float destination[]) {
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(this->dps[0], this->dps[1], this->dps[2]);
  }

  memcpy(destination, this->dps, 3*sizeof(float));
}

void SensorManager::readMagneticField(float destination[]) {
  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(this->magneticField[0], this->magneticField[1], this->magneticField[2]);    
  }

  memcpy(destination, this->magneticField, 3*sizeof(float));
}

float SensorManager::readTemperature() {
  if (millis() - this->lastTemperatureReadMillis > ENVIRONMENTAL_SENSORS_READ_DELAY_MS) {
    this->lastTemperatureReadMillis = millis();
    this->temperature = HTS.readTemperature();
  }
  
  return this->temperature;
}

float SensorManager::readHumidity() {
  if (millis() - this->lastHimidityReadMillis > ENVIRONMENTAL_SENSORS_READ_DELAY_MS) {
    this->lastHimidityReadMillis = millis();
    this->humidity = HTS.readHumidity();
  }
  
  return this->humidity;
}

float SensorManager::readPressure() {
  if (millis() - this->lastPressureReadMillis > ENVIRONMENTAL_SENSORS_READ_DELAY_MS) {
    this->lastPressureReadMillis = millis();
    this->pressure = BARO.readPressure();
  }
  
  return this->pressure;
}

float SensorManager::deriveAltitude() {
  return 44330 * ( 1.0 - pow(this->pressure/101.325, 0.1903));
}

void SensorManager::initImu() {

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

void SensorManager::initEnvironmentalSensors() {

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }

  Serial.println("Environmental sensors initialized");
}