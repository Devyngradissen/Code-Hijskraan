// Sjak Verschuren, Engineering, Zuyd University, 15-02-2025

#ifndef main_h
#define main_h

#define LED_wifi 4                    
#define LED_DATA_CAPTURED 13 
#define SENSOR 17           

#define GPIO_Stepper_1 33
#define GPIO_Stepper_2 27

#define DIR_STEPPER_1 25
#define DIR_STEPPER_2 14 

#define DISABLE_STEPPER_1 32 
#define DISABLE_STEPPER_2 26

#define channel_stepper_1 1 //timer for freq_1
#define channel_stepper_2 3 //timer for freq_2

#define servo1Pin 19

unsigned int data;

unsigned long previousWatchDogTime;

void setupInOutPorts(){
  pinMode(LED_wifi,OUTPUT);             
  pinMode(LED_DATA_CAPTURED,OUTPUT);        

  pinMode(SENSOR,INPUT);
  pinMode(DIR_STEPPER_1,OUTPUT);
  pinMode(DISABLE_STEPPER_1,OUTPUT);
  pinMode(DIR_STEPPER_2,OUTPUT);
  pinMode(DISABLE_STEPPER_2,OUTPUT);
}

#endif
