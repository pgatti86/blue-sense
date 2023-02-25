#ifndef BLE_SENSE_IDENTIFIERS_H
#define BLE_SENSE_IDENTIFIERS_H

class SensorManager {

  public:
    void initSensors();
    void readAcceleration(float destination[]);
    void readGyroscope(float destination[]);
    void readMagneticField(float destination[]);
    float readTemperature();
    bool canPollTemperatureSensor();
    float readHumidity();
    bool canPollHumiditySensor();
    float readPressure();
    float deriveAltitude();

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
    
    void initImu();
    void initEnvironmentalSensors();
};

#endif