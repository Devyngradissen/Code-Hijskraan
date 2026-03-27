const int MotorPinA1A = 33; 
const int MotorPinA1B = 32; 
void setup() {
Serial.begin(9600);
pinMode(MotorPinA1A, OUTPUT);
pinMode(MotorPinA1B, OUTPUT);
}
void loop() {
//DCmotorOnOff();
DCmotorAnalog();
// DCmotorAnalogMillis();
}
void DCmotorOnOff() {
digitalWrite(MotorPinA1A, HIGH);
digitalWrite(MotorPinA1B, LOW);
delay(1000);
digitalWrite(MotorPinA1A, LOW);
digitalWrite(MotorPinA1B, HIGH);
delay(1000);
}
void DCmotorAnalog() {
unsigned int speedDCmotor = analogRead(34);
Serial.println(speedDCmotor);
analogWrite(MotorPinA1A, speedDCmotor);
analogWrite(MotorPinA1B, 0);

delay(3000);
analogWrite(MotorPinA1A, 0);
analogWrite(MotorPinA1B, speedDCmotor);
delay(3000);
}
void DCmotorAnalogMillis() {
static unsigned long prevousMillis = millis();
unsigned int speedDCmotor = analogRead(34);
Serial.println(speedDCmotor);
if (millis() - prevousMillis >= 1000) {
analogWrite(MotorPinA1A, speedDCmotor);
analogWrite(MotorPinA1B, 0);
}
if (millis() - prevousMillis >= 1000) {
prevousMillis = millis();
analogWrite(MotorPinA1A, 0);
analogWrite(MotorPinA1B, speedDCmotor);
}
}