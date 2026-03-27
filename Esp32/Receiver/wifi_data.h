// Sjak Verschuren, Engineering, Zuyd University, 15-02-2025
/*********
=============
https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/network/esp_now.html
copy string to the packagemanager: file->preferences->asditional boards manager URLs:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
LEDC library:
https://techtutorialsx.com/2017/07/01/esp32-arduino-controlling-a-buzzer-with-pwm/
==============
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-many-to-one-esp32/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/
#ifndef wifi_data.h
#define wifi_data .h

#include <esp_now.h>
#include <WiFi.h>
#include "main.h"

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int id = 1;
  int a = 0;
  int b = 1;
  int c = 1;
  int d = 1;
  int e = 1;
  int f = 1;
  int g = 1;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// // Create a structure to hold the readings from each board
// struct_message board1;
// struct_message board2;
// struct_message board3;

// // Create an array with all the structures
// struct_message boardsStruct[3] = { board1, board2, board3 };

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];

  //Serial.print("Packet received from: ");
  //snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
  //         mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  //Serial.println(macStr);

  memcpy(&myData, incomingData, sizeof(myData));
  //Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  Serial.println("------------------------");
  Serial.printf("ID       value: %d \n", myData.id);
  Serial.printf("E_STOP   value: %d \n", myData.a);
  Serial.printf("GRIPPER  value: %d \n", myData.b);
  Serial.printf("CAT      value: %d \n", myData.c);
  Serial.printf("LIFT     value: %d \n", myData.d);
  Serial.printf("e        value: %d \n", myData.e);
  Serial.printf("f        value: %d \n", myData.f);
  Serial.printf("g        value: %d \n", myData.g);
  Serial.println("------------------------");
  previousWatchDogTime = millis();
}

void setup_wifi() {

  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  // Serial.print("ESP Board MAC Address:  ");
  // Serial.println(WiFi.macAddress());
}

void WatchDog() {
  (millis() - previousWatchDogTime > 500) ? digitalWrite(LED_DATA_CAPTURED, false) : digitalWrite(LED_DATA_CAPTURED, true);
}

#endif
