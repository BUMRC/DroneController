#include "Communication.h"

/////////////////////////////////
// Pi - ESP32 Communication
/////////////////////////////////

#define RXD2 16
#define TXD2 17

#define UART_BAUD 9600
#define RX_BUF_SIZE 1024

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

void mavlinkTask(void *pvParameters) {
  uint8_t data[RX_BUF_SIZE];
  mavlink_message_t msg;
  mavlink_status_t status;

  while(1) {
      int len = uart_read_bytes(UART_PORT_NUM, data, RX_BUF_SIZE, 20 / portTICK_PERIOD_MS);
      
      for(int i = 0; i < len; i++) {
          if(mavlink_parse_char(MAVLINK_COMM_0, data[i], &msg, &status)) {
              // Handle incoming Mavlink messages
              switch(msg.msgid) {
                  case MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE:
                      mavlink_rc_channels_override_t rc_override;
                      mavlink_msg_rc_channels_override_decode(&msg, &rc_override);
                      
                      // Call sensor fusion before applying controls
                      float accel[3], gyro[3], mag[3], fused_attitude[3];
                      update_sensor_fusion(accel, gyro, mag, fused_attitude);
                      
                      // Apply motor controls (convert RC inputs to motor outputs)
                      apply_motor_controls(
                          rc_override.chan1_raw,
                          rc_override.chan2_raw,
                          rc_override.chan3_raw,
                          rc_override.chan4_raw
                      );
                      break;
                  
                  // Add more Mavlink message cases as needed
              }
          }
      }
      vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
