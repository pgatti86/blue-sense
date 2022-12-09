#ifndef SENSORS_MANAGER_H_
#define SENSORS_MANAGER_H_

#include <Arduino_LSM9DS1.h>
#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>

class SensorManager {

  public:
    
    SensorManager() {
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

    float sensors_read_pressure_data() {
      return BARO.readPressure();
    }

    float sensors_derive_altitude(float pressure) {
      return 44330 * ( 1.0 - pow(pressure/101.325, 0.1903));
    }

  private:
  
    void sensors_init_imu() {

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

    void sensors_init_environmental() {

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
};

#endif