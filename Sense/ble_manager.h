#ifndef BLUE_BLE_MANAGER_H_
#define BLUE_BLE_MANAGER_H_

#include "sensors_manager.h"

typedef void (*centralNodeConnectionCallback)(bool isConnected);

void ble_manager_start(SensorManager *manager, centralNodeConnectionCallback callback);

#endif