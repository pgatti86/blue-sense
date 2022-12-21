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
    float lastTemperatureReadMillis;
    float humidity;
    float lastHimidityReadMillis;
    float pressure;
    float lastPressureReadMillis;

  private:  
    void initImu();
    void initEnvironmentalSensors();
};

#endif