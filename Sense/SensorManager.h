#ifndef BLE_SENSE_IDENTIFIERS_H
#define BLE_SENSE_IDENTIFIERS_H

#include <MadgwickAHRS.h>

class SensorManager {

  public:
    void initSensors();
    void readAcceleration(float destination[]);
    void readGyroscope(float destination[]);
    void readMagneticField(float destination[]);
    bool canPollTemperatureSensor();
    float readTemperature();
    bool canPollHumiditySensor();
    float readHumidity();
    bool canPollPressureSensor();
    float readPressure();
    float deriveAltitude();
    bool canPollOrientation();
    void readOrientation(float destination[]);

  private:
    float acceleration[3];
    float dps[3];
    float magneticField[3];
    float temperature;
    unsigned long lastTemperatureReadMillis;
    float humidity;
    unsigned long lastHumidityReadMillis;
    float pressure;
    unsigned long lastPressureReadMillis;
    Madgwick madgwickFilter;
    float orientation[3];
    unsigned long lastOrientationReadMicros;
    void initImu();
    void initEnvironmentalSensors();
};

#endif