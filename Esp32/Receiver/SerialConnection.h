// Sjak Verschuren, Engineering, Zuyd University, 15-02-2025

#ifndef SerialConnection_h
#define SerialConnection_h

#define dataArrayLength 6   // length of dataStorage array
#define startDataByte 48    // first [DEC] value of data dump (startDataByte==255)

char dataArray[10];

unsigned int freqStepper1;
unsigned int freqStepper2;
unsigned int angleServo;
unsigned int button1;
unsigned int button2;
unsigned int button3;   

void setupSerialConnection(){
  Serial.begin(115200);
  while (!Serial);
  delay(1000);
  Serial.print("start serial connection....");
  Serial.println("  ready.");
}

void refreshData(){   // serial input, not in use
  freqStepper1 = dataArray[0];
  freqStepper2 = dataArray[1];
  angleServo   = dataArray[2];
  button1      = dataArray[3];
  button2      = dataArray[4];
  button3      = dataArray[5];

  angleServo= map(angleServo,0,255,0,180);
}

void printdataArray(){
  Serial.println("+printdataArray+");
  for (int i=0;i<dataArrayLength;i++){
    Serial.print(i);
    Serial.print("\t");
    Serial.print(dataArray[i],DEC);
    Serial.print("\n");
  }
  Serial.println("-printdataArray-");
}

void SerialRead(){
unsigned int inByte;
static unsigned int index;  
static bool flagFillArray = 0;

  if (Serial.available() > 0 ){
    inByte = Serial.read();
    if (flagFillArray){
      dataArray[index]= inByte;
      Serial.print(index);
      Serial.print("\t");
      // Serial.print(dataArray[index],DEC);
      Serial.print("\n");
      index++;
      if(index>=dataArrayLength) {
        Serial.println("array filled");
        refreshData();
        printdataArray();
        flagFillArray=0;
        }
    }
    if (inByte == startDataByte){    // start data dump if (inByte==255)
      //for(i=0;i<=9;i++){dataArray[i]=0} //clean array
      index=0;
      flagFillArray=1;
    }
  }
}

#endif
