//Waardes van pinnen nog aanpassen
// --- Pin definities ---
const int joyX = A0;        // Joystick X-as
const int joyBtn = 6;       // Joystick drukknop (ingedrukt = LOW)

const int motorA = 9;       // Motor driver ingang A
const int motorB = 10;      // Motor driver ingang B

const int limitLinks = 4;   // Eindschakelaar links
const int limitRechts = 5;  // Eindschakelaar rechts

const int ledNoodstop = 7;  // LED voor noodstop-indicatie

// Drempelwaarden joystick
const int deadzoneLow = 450;
const int deadzoneHigh = 570;

void setup() {
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);

  pinMode(limitLinks, INPUT_PULLUP);
  pinMode(limitRechts, INPUT_PULLUP);

  pinMode(joyBtn, INPUT_PULLUP);

  pinMode(ledNoodstop, OUTPUT);
  digitalWrite(ledNoodstop, LOW);

  stopMotor();
}

void loop() {
  int joyValue = analogRead(joyX);
  bool btnPressed = digitalRead(joyBtn) == LOW;

  bool linksBereikt = digitalRead(limitLinks) == LOW;
  bool rechtsBereikt = digitalRead(limitRechts) == LOW;

  // --- NOODSTOP ---
  if (btnPressed) {
    stopMotor();
    digitalWrite(ledNoodstop, HIGH);  // LED AAN
    return;
  } else {
    digitalWrite(ledNoodstop, LOW);   // LED UIT
  }

  // --- IN-katten ---
  if (joyValue < deadzoneLow && !linksBereikt) {
    motorIn();
  }
  // --- UIT-katten ---
  else if (joyValue > deadzoneHigh && !rechtsBereikt) {
    motorUit();
  }
  // --- Middenstand of eindschakelaar ---
  else {
    stopMotor();
  }
}

// --- Motorfuncties ---
void motorIn() {
  digitalWrite(motorA, HIGH);
  digitalWrite(motorB, LOW);
}

void motorUit() {
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, HIGH);
}

void stopMotor() {
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, LOW);
}
