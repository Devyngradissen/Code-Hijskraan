// --- Pin definities ---
const int joyY = A1;        // Joystick Y-as voor hijsen
const int joyBtn = 6;       // Joystick drukknop (ingedrukt = LOW)

const int motorUp = 11;     // Motor driver ingang omhoog
const int motorDown = 12;   // Motor driver ingang omlaag

const int limitBoven = 8;   // Eindschakelaar boven
const int limitBeneden = 9; // Eindschakelaar beneden

const int ledNoodstop = 7;  // LED voor noodstop-indicatie

// Deadzone
const int deadzoneLow = 450;
const int deadzoneHigh = 570;

void setup() {
  pinMode(motorUp, OUTPUT);
  pinMode(motorDown, OUTPUT);

  pinMode(limitBoven, INPUT_PULLUP);
  pinMode(limitBeneden, INPUT_PULLUP);

  pinMode(joyBtn, INPUT_PULLUP);

  pinMode(ledNoodstop, OUTPUT);
  digitalWrite(ledNoodstop, LOW);

  stopMotor();
}

void loop() {
  int joyValue = analogRead(joyY);
  bool btnPressed = digitalRead(joyBtn) == LOW;

  bool bovenBereikt = digitalRead(limitBoven) == LOW;
  bool benedenBereikt = digitalRead(limitBeneden) == LOW;

  // --- NOODSTOP ---
  if (btnPressed) {
    stopMotor();
    digitalWrite(ledNoodstop, HIGH);
    return;
  } else {
    digitalWrite(ledNoodstop, LOW);
  }

  // --- HIJSEN OMHOOG ---
  if (joyValue < deadzoneLow && !bovenBereikt) {
    hijsOmhoog();
  }
  // --- HIJSEN OMLAAG ---
  else if (joyValue > deadzoneHigh && !benedenBereikt) {
    hijsOmlaag();
  }
  // --- Middenstand of eindschakelaar geraakt ---
  else {
    stopMotor();
  }
}

// --- Motorfuncties ---
void hijsOmhoog() {
  digitalWrite(motorUp, HIGH);
  digitalWrite(motorDown, LOW);
}

void hijsOmlaag() {
  digitalWrite(motorUp, LOW);
  digitalWrite(motorDown, HIGH);
}

void stopMotor() {
  digitalWrite(motorUp, LOW);
  digitalWrite(motorDown, LOW);
}
