#include "sensors.h"

static void print_imu_data(String sensor, float x, float y, float z);

void setup() {

  Serial.begin(9600);
  while (!Serial);

  digitalWrite(LED_PWR, LOW); // turn off POWER LED

  Serial.println("Init board sensors...");
  sensors_init();
}

void loop() {

  float aX=0, aY=0, aZ=0;
  sensors_read_accelerometer_data(aX, aY, aZ);
  print_imu_data("Accelerometer", aX, aY, aZ);

  float gX=0, gY=0, gZ=0;
  sensors_read_gyroscope_data(gX, gY, gZ);
  print_imu_data("Gyroscope", gX, gY, gZ);

  float mX=0, mY=0, mZ=0;
  sensors_read_magnetomer_data(mX, mY, mZ);
  print_imu_data("Magnetometer", mX, mY, mZ);

  float temperature = sensors_read_temperature_data();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  float humidity = sensors_read_humidity_data();
  Serial.print("Humidity: ");
  Serial.println(humidity);

  float pressure = sensors_read_pressure_data();
  Serial.print("Pressure = ");
  Serial.println(pressure);

  float altitude = sensors_read_derive_altitude();
  Serial.print("Altitude = ");
  Serial.println(altitude);

  delay(10000);
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


