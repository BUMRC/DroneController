// Include our modules (adjust the include path if needed)
#include "src/DroneControl.h"
#include "src/MotorControl.h"
#include "src/Sensors.h"
#include "src/Communication.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void setup() {
  Serial.begin(115200);
  // Initialize subsystems
  initMotors();
  initSensors();

  CommConfig myCommConfig = {
    true,        // enableUART
    false,        // enableWiFi
    false        // enableLoRa
  };

  CommConfig devCommConfig = {
    true,        // enableUART
    true,        // enableWiFi
    true        // enableLoRa
  };
  initCommunication();
  
  // Create a FreeRTOS task for drone control
  xTaskCreatePinnedToCore(
    DroneControlTask,   // Task function.
    "DroneControlTask", // Name of task.
    4096,               // Stack size (in words).
    NULL,               // Task input parameter.
    1,                  // Priority of the task.
    NULL,               // Task handle.
    1                   // Core to run the task (ESP32 has 2 cores: 0 or 1).
  );
}

void loop() {
  // The loop is not used because our tasks handle everything.
  // A simple delay keeps the loop from hogging CPU.
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
