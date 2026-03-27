#include <esp_now.h>
#include <WiFi.h>
#include "DefineInts.h"
#include "RunItems.h"
#include "CheckSensors.h"
#include "SetQuota.h"

uint8_t broadcastAddress[] = {0x00, 0x70, 0x07, 0x1d, 0x15, 0xa8};
#define LED_Wifi 4

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  setWifiLED(status);
}

void setWifiLED(bool status) {
 

  if (status == ESP_NOW_SEND_SUCCESS) {
    digitalWrite(LED_Wifi, true);
  } else {
    digitalWrite(LED_Wifi, false);
  }
}
int KatPos, HijsPos;
void setup() {
  Serial.begin(9600);
  printMACadress();
  DefineDataVariables();
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  esp_now_send_cb_t( );


  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;


if (esp_now_add_peer(&peerInfo) != ESP_OK) 
  {
    Serial.println("Failed to add peer");
    return;
  }
  pinMode(LED_Wifi, OUTPUT);
}

void loop() {

  CheckQuotaDif();
  CheckSensorLimits();
  if(MaxKat == true){
    HaltKat();
  }
  if(MinKat == true){
    HaltKat();
    KatPos = 0;
  }
  if(MaxHijs == true){
    HaltLift();
  }
  if(MinHijs == true){
    HaltLift);
    HijsPos = 0;
  }
  SetValuesToSend();

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
  if (myData.e > 9999) myData.e = 255; 
  if (myData.f < -999)  myData.f = 2;  
  if (myData.g > 99999) myData.g = 2;  
}

void CheckQuotaDif()
{
  if(KatPos < KatTarget){
    RunKatForw();
  }
  if(KatPos > KatTarget){
    RunKatAft();
  }
  if(HijsPos < HijsTarget){
    RunLiftDown();
  }
  if(Hijspos > HijsTarget){
    RunLiftUp();
  }
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
