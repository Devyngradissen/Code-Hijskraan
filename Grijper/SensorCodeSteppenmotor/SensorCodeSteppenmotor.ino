//Later doen: STEP, Knoppen en DIR pinnen aanpassen GEDAAN - kalibreren van sensoren/aanpassen VERRANDERD NAAR 2000 VOR MIDDEN PUNT WAARDE

// PIN-INSTELLINGEN

const int stepPin = 25;     // STEP-signaal naar driver (stuurt stappen)
const int dirPin  = 26;     // DIR-signaal naar driver (bepaalt richting)

const int closeButton = 32; // Sluit-knop (toggle: 1x drukken = starten/stoppen)
const int openButton  = 33; // Open-knop (momentary: werkt zolang je indrukt)

// FSR druksensoren
const int fsrMain = 34;   // Druksensor

// INSTELLINGEN

int pressureThreshold = 2000;   // Drempelwaarde voor druk (moet je kalibreren)
int stepDelay = 800;           // Snelheid van de stappenmotor (microseconden)

// Variabelen voor de sluit-knop (toggle)
bool gripperClosing = false;   // Houdt bij of de grijper moet sluiten
bool lastCloseButtonState = HIGH; // Voor het detecteren van knopveranderingen

//-----------------------------
// SETUP

void setup() {
  Serial.begin(9600);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(closeButton, INPUT_PULLUP); // Interne pull-up: knop = LOW wanneer ingedrukt
  pinMode(openButton, INPUT_PULLUP);

  // Standaard richting op SLUITEN zetten
  digitalWrite(dirPin, HIGH);
}


void loop() {

  bool closeState = digitalRead(closeButton);
  bool openState  = digitalRead(openButton);
  int MainValue = analogRead(fsrMain);

  // Toggle-functie voor sluit-knop
  // Alleen reageren wanneer de knop van HIGH → LOW gaat
if (MainValue < pressureThreshold) {          // alleen reageren als sensorwaarde onder threshold
  if (closeState == LOW && lastCloseButtonState == HIGH) {
      gripperClosing = !gripperClosing;   // wissel tussen starten/stoppen
      delay(200); // debounce
  }
}
lastCloseButtonState = closeState;


  bool MainPressed = MainValue >= pressureThreshold;

  // Debug-informatie naar Serial Monitor

  Serial.print("Sensor: ");
  Serial.print(MainValue);
  Serial.print(" | Sluiten actief: ");
  Serial.println(gripperClosing ? "JA" : "NEE");

  // -----------------------------------------------------------
  // OPENEN VAN DE GRIJPER (momentary knop)
  // -----------------------------------------------------------

  if (openState == LOW) {
    // Richting op OPENEN zetten
    digitalWrite(dirPin, LOW);

    // Eén stap openen
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);

    return; // Skip sluit-logica zolang open-knop actief is
  }

  // -----------------------------------------------------------
  // SLUITEN VAN DE GRIJPER (toggle knop)
  // -----------------------------------------------------------

  if (gripperClosing) {

    // Veiligheidsstop: sensor moet druk voelen
    if (MainPressed) {
      Serial.println("Object vast! Motor stopt.");
      gripperClosing = false;   // grijper blijft uitgeschakelt
      return; // Motor stopt automatisch
    }

    // Richting op SLUITEN zetten
    digitalWrite(dirPin, HIGH);

    // Eén stap sluiten
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
}
