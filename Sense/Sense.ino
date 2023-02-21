#include "SensorManager.h"
#include "BleManager.h"
#include <Scheduler.h>

const int FW_VERSION = 1;

float acceleration[3];
float dps[3];
float magneticField[3];

SensorManager sensorManager;

void setup() {

  Serial.begin(9600);
  //while (!Serial); // block sketch untill serial connection

  digitalWrite(LED_PWR, LOW);

  sensorManager.initSensors();
  
  bleManager_init(FW_VERSION, onMeasureRequestedCallback);

  Scheduler.startLoop(bleTask, 2048);
}

void loop() {
  delay(500);
}

void bleTask() {

  bool isConnected = bleManager_isConnected();

  digitalWrite(LED_BUILTIN, isConnected ? HIGH : LOW);

  if (isConnected) {

    if (bleManager_isSubscribedToAccelerometerCharacteristic()) {
      sensorManager.readAcceleration(acceleration);
      bleManager_writeAccelerometerData(acceleration);
    }

    if (bleManager_isSubscribedToGyroscopeCharacteristic()) {
      sensorManager.readGyroscope(dps);
      bleManager_writeGyroscopeData(dps);
    }

    if (bleManager_isSubscribedToMagneticFieldCharacteristic()) {
      sensorManager.readMagneticField(magneticField);
      bleManager_writeMagneticFieldData(magneticField);
    }

    if (bleManager_isSubscribedToTemperatureCharacteristic() && sensorManager.canPollTemperatureSensor()) {
      writeTemperatureCharacteristic();
    }

    if (bleManager_isSubscribedToHumidityCharacteristic()) {
      writeHumidityCharacteristic();
    }

    if (bleManager_isSubscribedToPressureCharacteristic()) {
      writePressureCharacteristic();
    }

    if (bleManager_isSubscribedToAltutideCharacteristic()) {
      writeAltitudeCharacteristic();
    }
  }

  yield();
}

void writeTemperatureCharacteristic() {
  bleManager_writeTemperatureData(sensorManager.readTemperature());
}

void writeHumidityCharacteristic() {
  bleManager_writeHumidityData(sensorManager.readHumidity());
}

void writePressureCharacteristic() {
  bleManager_writePressureData(sensorManager.readPressure());
}

void writeAltitudeCharacteristic() {
  sensorManager.readPressure();
  bleManager_writeAltitudeData(sensorManager.deriveAltitude());
}

void onMeasureRequestedCallback(MeasureType type) {
  switch(type) {
    case Temperature:
      writeTemperatureCharacteristic();
      break;
    case Humidity:
      writeHumidityCharacteristic();
      break;
    case Pressure:
      writePressureCharacteristic();
      break;
    case Altitude: {
      writeAltitudeCharacteristic();
    }
  }
}



