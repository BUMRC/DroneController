#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

// Initialize sensor hardware (IMU, gyroscopes, etc.)
void initSensors();

// Read sensor data and update global or module-level variables.
void readSensors();

#endif // SENSORS_H
