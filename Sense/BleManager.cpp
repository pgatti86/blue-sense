#include "BleManager.h"
#include "ble_definitions.h"

MeasureReadCallBack measureCallback = NULL;

void onPressureCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
 if(measureCallback)
    measureCallback(Pressure);
}

void onTemperatureCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
  if(measureCallback)
    measureCallback(Temperature);
}

void onHumidityCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
 if(measureCallback)
    measureCallback(Humidity);
}

void onAltitudeCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
  if(measureCallback)
    measureCallback(Altitude);
}

void bleManager_init(int fwVersion, MeasureReadCallBack callback) {
  
  measureCallback = callback;

  if (!BLE.begin()) {
    Serial.println("failed to initialize BLE!");
    while (1);
  }

  String deviceName = "BleSense-" + BLE.address().substring(0,8);
  BLE.setLocalName(deviceName.c_str());

  BLE.setAdvertisedService(service);

  service.addCharacteristic(versionCharacteristic);
  versionCharacteristic.setValue(fwVersion);

  service.addCharacteristic(accelerationCharacteristic);
  service.addCharacteristic(gyroscopeCharacteristic);
  service.addCharacteristic(magneticFieldCharacteristic);
  service.addCharacteristic(pressureCharacteristic);
  pressureCharacteristic.setEventHandler(BLERead, onPressureCharacteristicRead);
  service.addCharacteristic(temperatureCharacteristic);
  temperatureCharacteristic.setEventHandler(BLERead, onTemperatureCharacteristicRead);
  service.addCharacteristic(humidityCharacteristic);
  humidityCharacteristic.setEventHandler(BLERead, onHumidityCharacteristicRead);
  service.addCharacteristic(altitudeCharacteristic);
  altitudeCharacteristic.setEventHandler(BLERead, onAltitudeCharacteristicRead);

  BLE.addService(service);

  BLE.advertise();
}

bool bleManager_isConnected() {
  return BLE.connected();
}

bool bleManager_isSubscribedToAccelerometerCharacteristic() {
  return accelerationCharacteristic.subscribed();
}

void bleManager_writeAccelerometerData(float data[], int size) {
  accelerationCharacteristic.writeValue(data, size);
}

bool bleManager_isSubscribedToGyroscopeCharacteristic() {
  return gyroscopeCharacteristic.subscribed();
}

void bleManager_writeGyroscopeData(float data[], int size) {
  gyroscopeCharacteristic.writeValue(data, size);
}

bool bleManager_isSubscribedToMagneticFieldCharacteristic() {
  return magneticFieldCharacteristic.subscribed();
}

void bleManager_writeMagneticFieldData(float data[], int size) {
  magneticFieldCharacteristic.writeValue(data, size);
}

bool bleManager_isSubscribedToTemperatureCharacteristic() {
  return temperatureCharacteristic.subscribed();
}

void bleManager_writeTemperatureData(float data) {
  temperatureCharacteristic.writeValue(data);
}

bool bleManager_isSubscribedToHumidityCharacteristic() {
  return humidityCharacteristic.subscribed();
}

void bleManager_writeHumidityData(float data) {
  humidityCharacteristic.writeValue(data);
}

bool bleManager_isSubscribedToPressureCharacteristic() {
  return pressureCharacteristic.subscribed();
}

void bleManager_writePressureData(float data) {
  pressureCharacteristic.writeValue(data);
}

bool bleManager_isSubscribedToAltutideCharacteristic() {
  return altitudeCharacteristic.subscribed();
}

void bleManager_writeAltitudeData(float data) {
  altitudeCharacteristic.writeValue(data);
}

