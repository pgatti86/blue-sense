#include "sensors_manager.h"
#include "ble_manager.h"

static void print_imu_data(String sensor, float x, float y, float z);

static void ble_connection_callback(bool is_central_node_connected);

SensorManager sensorManager;

void setup() {

  Serial.begin(9600);
  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT); // initialize the built-in LED pin to indicate when a central is connected

  digitalWrite(LED_PWR, LOW); // turn off POWER LED
  
  ble_manager_start(&sensorManager, ble_connection_callback);
}

void loop() {

  float aX=0, aY=0, aZ=0;
  sensorManager.sensors_read_accelerometer_data(aX, aY, aZ);
  print_imu_data("Accelerometer", aX, aY, aZ);

  float gX=0, gY=0, gZ=0;
  sensorManager.sensors_read_gyroscope_data(gX, gY, gZ);
  print_imu_data("Gyroscope", gX, gY, gZ);

  float mX=0, mY=0, mZ=0;
  sensorManager.sensors_read_magnetomer_data(mX, mY, mZ);
  print_imu_data("Magnetometer", mX, mY, mZ);

  float temperature = sensorManager.sensors_read_temperature_data();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  float humidity = sensorManager.sensors_read_humidity_data();
  Serial.print("Humidity: ");
  Serial.println(humidity);

  float pressure = sensorManager.sensors_read_pressure_data();
  Serial.print("Pressure = ");
  Serial.println(pressure);

  float altitude = sensorManager.sensors_derive_altitude(pressure);
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

static void ble_connection_callback(bool is_central_node_connected) {
  digitalWrite(LED_BUILTIN, is_central_node_connected ? HIGH : LOW);
}


