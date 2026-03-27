// ===============================
// PIN DEFINITIES
// ===============================

// --- Joystick loopkat ---
const int joyX = A0;        // X-as voor loopkat

// --- Joystick hijsen ---
const int joyY = A1;        // Y-as voor hijsen

// --- Joystick drukknop (noodstop) ---
const int joyBtn = 6;       // Ingedrukt = LOW

// --- Motor loopkat ---
const int motorKatA = 9;
const int motorKatB = 10;

// --- Motor hijsen ---
const int motorUp = 11;
const int motorDown = 12;

// --- Eindschakelaars loopkat ---
const int limitLinks = 4;
const int limitRechts = 5;

// --- Eindschakelaars hijsen ---
const int limitBoven = 7;
const int limitBeneden = 8;

// --- LED voor noodstop ---
const int ledNoodstop = 13;

// --- Deadzone ---
const int deadzoneLow = 450;
const int deadzoneHigh = 570;

// SETUP
void setup() {
  // Motor outputs
  pinMode(motorKatA, OUTPUT);
  pinMode(motorKatB, OUTPUT);
  pinMode(motorUp, OUTPUT);
  pinMode(motorDown, OUTPUT);

  // Eindschakelaars
  pinMode(limitLinks, INPUT_PULLUP);
  pinMode(limitRechts, INPUT_PULLUP);
  pinMode(limitBoven, INPUT_PULLUP);
  pinMode(limitBeneden, INPUT_PULLUP);

  // Joystick knop
  pinMode(joyBtn, INPUT_PULLUP);

  // LED
  pinMode(ledNoodstop, OUTPUT);
  digitalWrite(ledNoodstop, LOW);

  stopAlleMotoren();
}

// LOOP
void loop() {
  int joyXval = analogRead(joyX);
  int joyYval = analogRead(joyY);
  bool btnPressed = digitalRead(joyBtn) == LOW;

  bool linksBereikt = digitalRead(limitLinks) == LOW;
  bool rechtsBereikt = digitalRead(limitRechts) == LOW;
  bool bovenBereikt = digitalRead(limitBoven) == LOW;
  bool benedenBereikt = digitalRead(limitBeneden) == LOW;

  // NOODSTOP
  if (btnPressed) {
    stopAlleMotoren();
    digitalWrite(ledNoodstop, HIGH);
    return;   // Alles overslaan
  } else {
    digitalWrite(ledNoodstop, LOW);
  }

  // LOOPKAT BESTURING
  if (joyXval < deadzoneLow && !linksBereikt) {
    katIn();
  }
  else if (joyXval > deadzoneHigh && !rechtsBereikt) {
    katUit();
  }
  else {
    stopKat();
  }

  // HIJSEN BESTURING
  if (joyYval < deadzoneLow && !bovenBereikt) {
    hijsOmhoog();
  }
  else if (joyYval > deadzoneHigh && !benedenBereikt) {
    hijsOmlaag();
  }
  else {
    stopHijs();
  }
}

// MOTORFUNCTIES LOOPKAT
void katIn() {
  digitalWrite(motorKatA, HIGH);
  digitalWrite(motorKatB, LOW);
}

void katUit() {
  digitalWrite(motorKatA, LOW);
  digitalWrite(motorKatB, HIGH);
}

void stopKat() {
  digitalWrite(motorKatA, LOW);
  digitalWrite(motorKatB, LOW);
}

// MOTORFUNCTIES HIJSEN
void hijsOmhoog() {
  digitalWrite(motorUp, HIGH);
  digitalWrite(motorDown, LOW);
}

void hijsOmlaag() {
  digitalWrite(motorUp, LOW);
  digitalWrite(motorDown, HIGH);
}

void stopHijs() {
  digitalWrite(motorUp, LOW);
  digitalWrite(motorDown, LOW);
}

// ALLES STOPPEN
void stopAlleMotoren() {
  stopKat();
  stopHijs();
}
