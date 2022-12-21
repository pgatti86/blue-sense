#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include "SensorManager.h"

class BleManager {
  
  public:
    void init(int fwVersion, SensorManager *sensorManager);
  };

#endif