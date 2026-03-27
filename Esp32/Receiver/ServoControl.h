// Sjak Verschuren, Engineering, Zuyd University, 29-03-2025
// - Update to ESP32 Core 3.x
// - improved function: void Servo(unsigned int val)
// install library: ESP32ServoController by MDO   https://github.com/mjdonders/ESP32ServoController

#ifndef ServoControl_h
#define ServoControl_h

#include "main.h"
#include <ESP32ServoController.h>

using namespace MDO::ESP32ServoController;
BestAvailableFactory oFactory;  //used to select the best available timer & channel based on the hardware setup
PWMController oPwm;

const uint32_t uiFreqHz = 50; //basic freq
const uint8_t uiPinNr = 19;
double dDuty = 0.00;  //a duty cycle of 33.3%

void setupServo() {
  Esp32LedcRegistry::instance()->begin(LEDC_CONFIG_ESP32_S3);  //change this for the relevant controller
                                                               //the actual PWM controller
  if (oPwm.begin(oFactory, uiPinNr, uiFreqHz, dDuty)) {
    Serial.println("PWM controller started");
  } else {
    Serial.println("Failed to start the PWM controller");
  }
}

void Servo(unsigned int val) {    // val=[1000-2000]us
  dDuty = val / 20000.0;          // us to PWM at 1/uiFreqHz = 1/50Hz=0.02sec=20000us
  if (dDuty < 0.0) dDuty = 0;     // PWM lower limit
  if (dDuty > 0.99) dDuty = 0.99; // PWM upper limit
  oPwm.fade(dDuty, 10, true);     //now a 10msec blocking call, so no delay required
}

#endif
