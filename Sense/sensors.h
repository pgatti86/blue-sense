#ifndef BLUE_SENSORS_H_
#define BLUE_SENSORS_H_

void sensors_init();

void sensors_read_accelerometer_data(float &x, float &y, float &z);

void sensors_read_gyroscope_data(float &x, float &y, float &z);

void sensors_read_magnetomer_data(float &x, float &y, float &z);

float sensors_read_temperature_data();

float sensors_read_humidity_data();

#endif