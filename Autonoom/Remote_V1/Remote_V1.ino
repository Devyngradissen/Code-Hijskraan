// Sjak Verschuren, Engineering, Zuyd University, 15-02-2025
/*********
=============
https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/network/esp_now.html
For use ESP32 in arduino IDE:
copy URL to the packagemanager: file->preferences->asditional boards manager URLs:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
==============
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-many-to-one-esp32/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH THE RECEIVER'S MAC Address
uint8_t broadcastAddress[] = {0x00, 0x70, 0x07, 0x1d, 0x15, 0xa8};
//uint8_t broadcastAddress[] = {0x48, 0xE7, 0x29, 0xB2, 0xFB, 0x8C};
//uint8_t broadcastAddress[] = { 0xC8, 0xC9, 0xA3, 0xFD, 0x02, 0x40 };

#define LED_Wifi 4

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int id = 1;  // must be unique for each sender board
  int E_STOP;
  int GRIPPER;
  int CAT;
  int LIFT;
  int e = 255;
  int f;
  int g = 2;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create peer interface
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  setWifiLED(status);
}

void setWifiLED(bool status) {
  // status == ESP_NOW_SEND_SUCCESS ? digitalWrite(LED_Wifi, true) : digitalWrite(LED_Wifi, false);  //LED_Wifi ON/OFF

  if (status == ESP_NOW_SEND_SUCCESS) {  //LED_Wifi ON/OFF
    digitalWrite(LED_Wifi, true);
  } else {
    digitalWrite(LED_Wifi, false);
  }
}

void setup() {
  // Init Serial Monitor
  Serial.begin(9600);
  printMACadress();
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  //esp_now_register_send_cb(OnDataSent);
  esp_now_send_cb_t( ); //2026-02-02 ivm error ESP32_now

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  pinMode(LED_Wifi, OUTPUT);
}

void loop() {

  SetValuesToSend();

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
  delay(250);
}

void SetValuesToSend() {
  myData.GRIPPER = random(1000, 2000);
  myData.CAT = ((analogRead(34)/ 3) - 682);
  myData.LIFT = ((analogRead(34)/ 3) - 682);
  myData.e += 1;
  myData.f -= 3;
  myData.g *= 2;
  if (myData.e > 9999) myData.e = 255;  // overflow protection
  if (myData.f < -999)  myData.f = 2;    // overflow protection
  if (myData.g > 99999) myData.g = 2;    // overflow protection
}


void printMACadress() {
  Serial.printf("\nuint8_t broadcastAddress[] = { 0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X };",
                broadcastAddress[0],
                broadcastAddress[1],
                broadcastAddress[2],
                broadcastAddress[3],
                broadcastAddress[4],
                broadcastAddress[5]);
  Serial.println("\n");
}