#include "ble_manager.h"

#include <Scheduler.h>
#include <ArduinoBLE.h>

#define BLUE_SENSE_BLE_UUID(identifier) ("e905de3e-" identifier "-44de-92c4-bb6e04fb0212")

static const int VERSION = 0x00000001;

static BLEService                     service                       (BLUE_SENSE_BLE_UUID("0000"));
static BLEUnsignedIntCharacteristic   versionCharacteristic         (BLUE_SENSE_BLE_UUID("1001"), BLERead);
//static BLEUnsignedShortCharacteristic ambientLightCharacteristic    (BLUE_SENSE_BLE_UUID("2001"), BLENotify); // 16-bit
//static BLECharacteristic              colorCharacteristic           (BLUE_SENSE_BLE_UUID("2002"), BLENotify, 3 * sizeof(unsigned short)); // Array of 16-bit, RGB
//static BLEUnsignedCharCharacteristic  proximityCharacteristic       (BLUE_SENSE_BLE_UUID("2003"), BLENotify); // Byte, 0 - 255 => close to far
//static BLEByteCharacteristic          gestureCharacteristic         (BLUE_SENSE_BLE_UUID("2004"), BLENotify); // NONE = -1, UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
static BLECharacteristic              accelerationCharacteristic    (BLUE_SENSE_BLE_UUID("3001"), BLENotify, 3 * sizeof(float)); // Array of 3 floats, G
static BLECharacteristic              gyroscopeCharacteristic       (BLUE_SENSE_BLE_UUID("3002"), BLENotify, 3 * sizeof(float)); // Array of 3 floats, dps
static BLECharacteristic              magneticFieldCharacteristic   (BLUE_SENSE_BLE_UUID("3003"), BLENotify, 3 * sizeof(float)); // Array of 3 floats, uT
//static BLECharacteristic              orientationCharacteristic     (BLUE_SENSE_BLE_UUID("3004"), BLENotify, 3 * sizeof(float)); // Array of 3 floats, rad
static BLEFloatCharacteristic         pressureCharacteristic        (BLUE_SENSE_BLE_UUID("4001"), BLERead | BLENotify); // Float, kPa
static BLEFloatCharacteristic         temperatureCharacteristic     (BLUE_SENSE_BLE_UUID("4002"), BLERead | BLENotify); // Float, Celcius
static BLEFloatCharacteristic         humidityCharacteristic        (BLUE_SENSE_BLE_UUID("4003"), BLERead | BLENotify); // Float, Percentage
static BLEFloatCharacteristic         altitudeCharacteristic        (BLUE_SENSE_BLE_UUID("4001"), BLERead | BLENotify); // Float, Meters (estimated)
//static BLECharacteristic              microphoneLevelCharacteristic (BLUE_SENSE_BLE_UUID("5001"), BLENotify, 32); // Int, RMS of audio input
//static BLECharacteristic              rgbLedCharacteristic          (BLUE_SENSE_BLE_UUID("6001"), BLERead | BLEWrite, 3 * sizeof(byte)); // Array of 3 bytes, RGB

static centralNodeConnectionCallback connectionCallback = NULL;

static SensorManager *sensorManager = NULL;

static bool is_central_connected;

static void ble_task() {

  bool is_connected = BLE.connected();

  if (connectionCallback && is_central_connected != is_connected) {
    is_central_connected = is_connected;
    connectionCallback(is_connected);
  }
  
  if (is_connected) {
    
  }

  BLE.poll();
  yield();  
}

/*
static void onPressureCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
  pressureCharacteristic.writeValue(sensorManager->sensors_read_pressure_data());
}

static void onTemperatureCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
  temperatureCharacteristic.writeValue(sensorManager->sensors_read_temperature_data());
}

static void onHumidityCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
  humidityCharacteristic.writeValue(sensorManager->sensors_read_humidity_data());
}*/

void ble_manager_start(SensorManager *manager, centralNodeConnectionCallback callback) {

  if (!BLE.begin()) {
    Serial.println("failed to initialize BLE!");
    while (1);
  }

  sensorManager = manager;
  connectionCallback = callback;  

  BLE.setLocalName("BlueSense");
  
  BLE.setAdvertisedService(service);
  
  service.addCharacteristic(versionCharacteristic);
  versionCharacteristic.setValue(VERSION);

  service.addCharacteristic(accelerationCharacteristic);
  service.addCharacteristic(gyroscopeCharacteristic);
  service.addCharacteristic(magneticFieldCharacteristic);
  
  service.addCharacteristic(pressureCharacteristic);
  //pressureCharacteristic.setEventHandler(BLERead, onPressureCharacteristicRead);
  service.addCharacteristic(temperatureCharacteristic);
  //temperatureCharacteristic.setEventHandler(BLERead, onTemperatureCharacteristicRead);
  service.addCharacteristic(humidityCharacteristic);
  //humidityCharacteristic.setEventHandler(BLERead, onHumidityCharacteristicRead);
  
  BLE.addService(service);

  BLE.advertise();

  Scheduler.startLoop(ble_task);
}