#ifndef CheckSensors.h
#define CheckSensors.h

bool MaxKat, MinKat, MaxHijs, MinHijs;
int MaxKatSen, MinKatSen, MaxHijsSen, MinHijsSen;

void CheckSensorLimits(){
  if(digitalRead(MaxKatSen) == HIGH){
    MaxKat = true;
  } else{
    MaxKat = false;
  }
    if(digitalRead(MinKatSen) == HIGH){
    MinKat = true;
  } else{
    MinKat = false;
  }
    if(digitalRead(MaxHijsSen) == HIGH){
    MaxHijs = true;
  } else{
    MaxHijs = false;
  }
    if(digitalRead(MinHijsSen) == HIGH){
    MinHijs = true;
  } else{
    MinHijs = false;
  }
}

#endif