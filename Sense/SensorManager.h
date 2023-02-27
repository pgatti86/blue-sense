#ifndef BLE_SENSE_IDENTIFIERS_H
#define BLE_SENSE_IDENTIFIERS_H

class SensorManager {

  public:
    void initSensors();
    void readAcceleration(float destination[]);
    void readGyroscope(float destination[]);
    void readMagneticField(float destination[]);
    float readTemperature();
    float readHumidity();
    float readPressure();
    float deriveAltitude();

  private:
    float acceleration[3];
    float dps[3];
    float magneticField[3];
    float temperature;
    unsigned long lastTemperatureReadMillis;
    bool canPollTemperatureSensor();
    float humidity;
    unsigned long lastHumidityReadMillis;
    bool canPollHumiditySensor();
    float pressure;
    unsigned long lastPressureReadMillis;
    bool canPollPressureSensor();
    
    void initImu();
    void initEnvironmentalSensors();
};

#endif