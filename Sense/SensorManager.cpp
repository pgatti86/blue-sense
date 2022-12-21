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
    IMU.readAcceleration(SensorManager::acceleration[0], SensorManager::acceleration[1], SensorManager::acceleration[2]);      
  }

  memcpy(destination, SensorManager::acceleration, 3*sizeof(float));
}


void SensorManager::readGyroscope(float destination[]) {
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(SensorManager::dps[0], SensorManager::dps[1], SensorManager::dps[2]);
  }

  memcpy(destination, SensorManager::dps, 3*sizeof(float));
}

void SensorManager::readMagneticField(float destination[]) {
  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(SensorManager::magneticField[0], SensorManager::magneticField[1], SensorManager::magneticField[2]);    
  }

  memcpy(destination, SensorManager::magneticField, 3*sizeof(float));
}

float SensorManager::readTemperature() {
  if (millis() - SensorManager::lastTemperatureReadMillis > ENVIRONMENTAL_SENSORS_READ_DELAY_MS) {
    SensorManager::lastTemperatureReadMillis = millis();
    SensorManager::temperature = HTS.readTemperature();
  }
  
  return SensorManager::temperature;
}

float SensorManager::readHumidity() {
  if (millis() - SensorManager::lastHimidityReadMillis > ENVIRONMENTAL_SENSORS_READ_DELAY_MS) {
    SensorManager::lastHimidityReadMillis = millis();
    SensorManager::humidity = HTS.readHumidity();
  }
  
  return SensorManager::humidity;
}

float SensorManager::readPressure() {
  if (millis() - SensorManager::lastPressureReadMillis > ENVIRONMENTAL_SENSORS_READ_DELAY_MS) {
    SensorManager::lastPressureReadMillis = millis();
    SensorManager::pressure = BARO.readPressure();
  }
  
  return SensorManager::pressure;
}

float SensorManager::deriveAltitude() {
  return 44330 * ( 1.0 - pow(SensorManager::pressure/101.325, 0.1903));
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