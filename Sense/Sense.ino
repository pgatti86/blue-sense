#include "SensorManager.h"
#include "BleManager.h"

const int FW_VERSION = 1;

SensorManager sensorManager;
BleManager bleManager;

void setup() {

  Serial.begin(9600);
  //while (!Serial); // block sketch untill serial connection

  digitalWrite(LED_PWR, LOW); // turn off POWER LED

  sensorManager.initSensors();
  bleManager.init(FW_VERSION, &sensorManager);
}

void loop() {
  delay(500);
}



