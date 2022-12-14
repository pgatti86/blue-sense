#include "sensors.h"

static void print_imu_data(String sensor, float x, float y, float z);

void setup() {

  Serial.begin(9600);
  while (!Serial);

  Serial.println("Init board sensors...");
  sensors_init();
}

void loop() {

  float aX=0, aY=0, aZ=0;
  read_accelerometer_data(aX, aY, aZ);
  print_imu_data("Accelerometer", aX, aY, aZ);

  float gX=0, gY=0, gZ=0;
  read_gyroscope_data(gX, gY, gZ);
  print_imu_data("Gyroscope", gX, gY, gZ);

  float mX=0, mY=0, mZ=0;
  read_magnetomer_data(mX, mY, mZ);
  print_imu_data("Magnetometer", mX, mY, mZ);
}

static void print_imu_data(String sensor, float x, float y, float z) {
  
  Serial.print(sensor);
  Serial.print("-");
  Serial.print(x);
  Serial.print('\t');
  Serial.print(y);
  Serial.print('\t');
  Serial.println(z);
}


