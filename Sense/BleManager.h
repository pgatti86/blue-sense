#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

enum MeasureType { Temperature, Humidity, Pressure, Altitude };

typedef void (*MeasureReadCallBack)(MeasureType);

void bleManager_init(int fwVersion, MeasureReadCallBack callback);
bool bleManager_isConnected();

bool bleManager_isSubscribedToAccelerometerCharacteristic();
void bleManager_writeAccelerometerData(float data[], int size = 3*sizeof(float));

bool bleManager_isSubscribedToGyroscopeCharacteristic();
void bleManager_writeGyroscopeData(float data[], int size = 3*sizeof(float));

bool bleManager_isSubscribedToMagneticFieldCharacteristic();
void bleManager_writeMagneticFieldData(float data[], int size = 3*sizeof(float));

bool bleManager_isSubscribedToTemperatureCharacteristic();
void bleManager_writeTemperatureData(float data);

bool bleManager_isSubscribedToHumidityCharacteristic();
void bleManager_writeHumidityData(float data);

bool bleManager_isSubscribedToPressureCharacteristic();
void bleManager_writePressureData(float data);

bool bleManager_isSubscribedToAltutideCharacteristic();
void bleManager_writeAltitudeData(float data);

bool bleManager_isSubscribedToOrientationCharacteristic();
void bleManager_writeOrientationData(float data[], int size = 3*sizeof(float));

bool bleManager_isSubscribedToHeadingCharacteristic();
void bleManager_writeHeadingData(float data);

#endif