#ifndef BLE_SENSE_DEFINITIONS_H
#define BLE_SENSE_DEFINITIONS_H

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

#endif