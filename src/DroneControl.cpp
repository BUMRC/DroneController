#include "DroneControl.h"
#include "MotorControl.h"
#include "Sensors.h"
#include "Communication.h"

void DroneControlTask(void * parameter) {
  while (true) {
    // Read sensors (e.g., IMU, barometer)
    readSensors();

    // Process sensor data and determine motor outputs.
    // (Insert your flight control algorithm here)
    // For demonstration, we set all four motors to a fixed speed.
    setMotorSpeed(1, 100);
    setMotorSpeed(2, 100);
    setMotorSpeed(3, 100);
    setMotorSpeed(4, 100);
    
    // Optionally send telemetry data
    sendTelemetry();

    // Delay to yield control to other tasks (e.g., 50ms)
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}
