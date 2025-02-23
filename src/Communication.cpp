#include "Communication.h"

/////////////////////////////////
// Pi - ESP32 Communication
/////////////////////////////////

#define RXD2 16
#define TXD2 17

#define UART_BAUD 9600

HardwareSerial gpsSerial(2);

/////////////////////////////////
// WiFi Configuration
/////////////////////////////////

const char* ssid = "yourNetworkName";
const char* password = "yourNetworkPassword";

/////////////////////////////////
// LoRa Configuration
/////////////////////////////////

#define SS 5
#define RST 14
#define DIO0 2

#define BAND 915E6 // 915 MHz

#define SYNC_WORD 0xF3


void initCommunication(const CommConfig &config) {
    if (config.enableUART) {
        gpsSerial.begin(UART_BAUD, SERIAL_8N1, RXD2, TXD2);
        Serial.println("UART initialized.");
      }
      if (config.enableWiFi) {
        WiFi.begin(ssid, password);
        Serial.println("WiFi protocol enabled.");
      }
      if (config.enableLora) {
        LoRa.setPins(SS, RST, DIO0);
        if (!LoRa.begin(BAND)) {
          Serial.println("LoRa initialization failed.");
          while (1);
        }
        LoRa.setSyncWord(SYNC_WORD);
        Serial.println("LoRa protocol enabled.");
      }
}

void sendTelemetry() {
  // Send out telemetry data.
  // This might involve sending data over Serial, WiFi, or another interface.
}
