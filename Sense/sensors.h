#ifndef BLUE_SENSORS_H_
#define BLUE_SENSORS_H_

void sensors_init();

void read_accelerometer_data(float &x, float &y, float &z);

void read_gyroscope_data(float &x, float &y, float &z);

void read_magnetomer_data(float &x, float &y, float &z);

#endif