// Sjak Verschuren, Engineering, Zuyd University, 15-02-2025

// =============
// ESP32: Migrating from version 2.x to 3.0 (Arduino IDE)
// https://randomnerdtutorials.com/esp32-migrating-version-2-to-3-arduino/
// https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/network/esp_now.html
// For use ESP32 in arduino IDE:
// copy URL to the packagemanager: file->preferences->asditional boards manager URLs:
// https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
// ==============

#include "main.h"
#include "wifi_data.h"
#include "WiFiMACaddress.h"
#include "ServoControl.h"
#include "SerialConnection.h"
#include "StepperControlDriver.h"

void setup() {
  setupInOutPorts();
  setupSerialConnection();
  setup_wifi();
  setupMAC();
  setupStepper();
  setupServo();
  Stepper1_PulseGenerator(1, DIR_STEPPER_1, DISABLE_STEPPER_1);
  Stepper2_PulseGenerator(1, DIR_STEPPER_2, DISABLE_STEPPER_2);
  previousWatchDogTime = millis();
}

void loop() {
  unsigned int E_STOP = myData.a;
  unsigned int GRIPPER = myData.b;
  int CAT = myData.c;
  int LIFT = myData.d;
  //unsigned int e = myData.e;
  //unsigned int f = myData.f;

  Servo(GRIPPER);
  // Serial.print("\t\t\t\t");
  // Serial.print(CAT);
  // Serial.print("\t");
  // Serial.print(LIFT);
  // Serial.print("\t");
  // Serial.print(DISABLE_STEPPER_1);
  // Serial.print("\n");
  Stepper1_PulseGenerator(CAT, DIR_STEPPER_1, DISABLE_STEPPER_1);
  Stepper2_PulseGenerator(LIFT, DIR_STEPPER_2, DISABLE_STEPPER_2);
  EMERGENTY(E_STOP, DISABLE_STEPPER_1, DISABLE_STEPPER_2);
  WatchDog();
}
