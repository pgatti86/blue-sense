#include "BleManager.h"
#include <Scheduler.h>
#include <ArduinoBLE.h>

#define BLE_UUID(identifier) ("e905de3e-" identifier "-44de-92c4-bb6e04fb0212")  // TODO check BLE default characteristics

BLEService                     service                       (BLE_UUID("0000"));
BLEUnsignedIntCharacteristic   versionCharacteristic         (BLE_UUID("1001"), BLERead);
//static BLEUnsignedShortCharacteristic ambientLightCharacteristic    (BLE_UUID("2001"), BLENotify); // 16-bit
//static BLECharacteristic              colorCharacteristic           (BLE_UUID("2002"), BLENotify, 3 * sizeof(unsigned short)); // Array of 16-bit, RGB
//static BLEUnsignedCharCharacteristic  proximityCharacteristic       (BLE_UUID("2003"), BLENotify); // Byte, 0 - 255 => close to far
//static BLEByteCharacteristic          gestureCharacteristic         (BLE_UUID("2004"), BLENotify); // NONE = -1, UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
BLECharacteristic              accelerationCharacteristic    (BLE_UUID("2001"), BLENotify, 3 * sizeof(float)); // Array of 3 floats, G
BLECharacteristic              gyroscopeCharacteristic       (BLE_UUID("2002"), BLENotify, 3 * sizeof(float)); // Array of 3 floats, dps
BLECharacteristic              magneticFieldCharacteristic   (BLE_UUID("2003"), BLENotify, 3 * sizeof(float)); // Array of 3 floats, uT
//static BLECharacteristic              orientationCharacteristic     (BLE_UUID("3004"), BLENotify, 3 * sizeof(float)); // Array of 3 floats, rad
BLEFloatCharacteristic         pressureCharacteristic        (BLE_UUID("3001"), BLERead | BLENotify); // Float, kPa
BLEFloatCharacteristic         temperatureCharacteristic     (BLE_UUID("3002"), BLERead | BLENotify); // Float, Celcius
BLEFloatCharacteristic         humidityCharacteristic        (BLE_UUID("3003"), BLERead | BLENotify); // Float, Percentage
BLEFloatCharacteristic         altitudeCharacteristic        (BLE_UUID("4001"), BLERead | BLENotify); // Float, Meters (estimated)
//static BLECharacteristic              microphoneLevelCharacteristic (BLE_UUID("5001"), BLENotify, 32); // Int, RMS of audio input
//static BLECharacteristic              rgbLedCharacteristic          (BLE_UUID("6001"), BLERead | BLEWrite, 3 * sizeof(byte)); // Array of 3 bytes, RGB

float acceleration[3];
float dps[3];
float magneticField[3];

SensorManager *_sensorManager;

void onPressureCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
  pressureCharacteristic.writeValue(_sensorManager->readPressure());
}

void onTemperatureCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
  temperatureCharacteristic.writeValue(_sensorManager->readTemperature());
}

void onHumidityCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
  humidityCharacteristic.writeValue(_sensorManager->readHumidity());
}

void onAltitudeCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
  altitudeCharacteristic.writeValue(_sensorManager->deriveAltitude());
}

void bleTask() {

  bool isConnected = BLE.connected();

  digitalWrite(LED_BUILTIN, isConnected ? HIGH : LOW);

  if (isConnected) {

    if (accelerationCharacteristic.subscribed()) {
      _sensorManager->readAcceleration(acceleration);
      accelerationCharacteristic.writeValue(acceleration, sizeof(acceleration));
    }

    if (gyroscopeCharacteristic.subscribed()) {
      _sensorManager->readGyroscope(dps);
      gyroscopeCharacteristic.writeValue(dps, sizeof(dps));
    }

    if (magneticFieldCharacteristic.subscribed()) {
      _sensorManager->readMagneticField(magneticField);
      magneticFieldCharacteristic.writeValue(magneticField, sizeof(magneticField));
    }

    if (temperatureCharacteristic.subscribed()) {
      temperatureCharacteristic.writeValue(_sensorManager->readTemperature());
    }

    if (humidityCharacteristic.subscribed()) {
      humidityCharacteristic.writeValue(_sensorManager->readHumidity());
    }

    if (pressureCharacteristic.subscribed()) {
      pressureCharacteristic.writeValue(_sensorManager->readPressure());
    }

    if (altitudeCharacteristic.subscribed()) {
      _sensorManager->readPressure();
      altitudeCharacteristic.writeValue(_sensorManager->deriveAltitude());
    }
  }

  yield();
}

void BleManager::init(int fwVersion, SensorManager *sensorManager) {
 
  _sensorManager = sensorManager;

  if (!BLE.begin()) {
    Serial.println("failed to initialize BLE!");
    while (1);
  }

  BLE.setLocalName("BlueSense");

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

  Scheduler.startLoop(bleTask, 2048);
}