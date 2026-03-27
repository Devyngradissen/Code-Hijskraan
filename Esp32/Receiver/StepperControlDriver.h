// Sjak Verschuren, Engineering, Zuyd University, 15-02-2025

// https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/ledc.html
// https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/ledc.html
// https://randomnerdtutorials.com/esp32-pwm-arduino-ide/
// migrated to ESP32 platform v3.x

#ifndef StepperControlDriver_h
#define StepperControlDriver_h

#include "main.h"

#define resolution 1

//unsigned int pulseDurationStepper2 = 0;

void setupStepper() {
  static uint16_t freq = 0;  // Frequency in Hz
  uint16_t SetFreq = 4096;
  ledcAttachChannel(GPIO_Stepper_1, SetFreq, resolution, channel_stepper_1);
  ledcAttachChannel(GPIO_Stepper_2, SetFreq, resolution, channel_stepper_2);
  ledcWriteTone(GPIO_Stepper_1, freq);
  ledcWriteTone(GPIO_Stepper_2, freq);
}
// generate frequency and  
void Stepper1_PulseGenerator(int freq, unsigned int DIRpin, unsigned int DISABLEpin) {
  static int previousFreq = freq;
  if (freq < 0) {
    freq *= -1;
    digitalWrite(DIRpin, 1);
  } else digitalWrite(DIRpin, 0);
  if (freq <= 5) digitalWrite(DISABLEpin, 1);                   //joystick noisefloor threshold
  else digitalWrite(DISABLEpin, 0);
  if (freq <= 11) freq = 11;                                    //lowest frequency
  if (freq >= previousFreq + 10 || freq <= previousFreq - 10) { //makes speed regulation more stable
    previousFreq = freq;
    ledcWriteTone(GPIO_Stepper_1, freq);
  }
}

void Stepper2_PulseGenerator(int freq, unsigned int DIRpin, unsigned int DISABLEpin) {
  static int previousFreq = freq;
  if (freq < 0) {
    freq *= -1;
    digitalWrite(DIRpin, 1);
  } else digitalWrite(DIRpin, 0);
  if (freq <= 5) digitalWrite(DISABLEpin, 1);                   //joystick noisefloor threshold
  else digitalWrite(DISABLEpin, 0);
  if (freq <= 11) freq = 11;                                    //lowest frequency
  if (freq >= previousFreq + 10 || freq <= previousFreq - 10) { //makes speed regulation more stable
    previousFreq = freq;
    ledcWriteTone(GPIO_Stepper_2, freq);
  }
}

void EMERGENTY(int E_STOP, uint8_t DISABLEpin1, uint8_t DISABLEpin2) {
  if (E_STOP == 1) {
    digitalWrite(DISABLEpin1, 1);
    digitalWrite(DISABLEpin2, 1);
    while (1)
      ;
  }
}

#endif
