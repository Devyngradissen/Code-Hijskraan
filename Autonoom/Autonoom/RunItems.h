#ifndef RunItems.h
#define RunItems.h
typedef struct struct_message {
  int id = 1; 
  int E_STOP;
  int GRIPPER;
  int CAT;
  int LIFT;
  int e = 255;
  int f;
  int g = 2;
} struct_message;


struct_message myData;
void RunKatForw(){
    myData.CAT = 1000;
}

void RunKatAft(){
    myData.CAT = -1000;
}
void RunLiftUp(){
    myData.LIFT = 60;
}
void RunLiftDown(){
    myData.LIFT = -60;
}
void RunGripThight(){
    myData.GRIPPER = 500;
}
void RunGripLoose(){
    myData.GRIPPER = -500;
}
void HaltGrip(){
    myData.GRIPPER = 0;
}
void HaltKat(){
    myData.CAT = 0;
}
void HaltLift(){
    myData.LIFT = 0;
}
void EMERGENCYSTOP(){
    myData.LIFT = 0;
    myData.CAT = 0;
    myData.GRIPPER = 0;
}
#endif