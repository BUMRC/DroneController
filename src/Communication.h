#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <WiFi.h>
#include <LoRa.h>
#include <SPI.h>
#include <MAVLink.h>

struct CommConfig {
    bool enableUART;       // Enable UART
    bool enableWiFi;       // Enable WiFi
    bool enableLora;       // Enable LoRa
};

// Initialize communication peripherals (WiFi, Bluetooth, etc.)
void initCommunication();

// Send telemetry or status data to a ground station or controller.
void sendTelemetry();

#endif // COMMUNICATION_H
