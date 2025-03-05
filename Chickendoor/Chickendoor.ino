// versie 0.3. Deze werkt. De teller telt op. Wanneer ik op de button klik gaat de teller op 0 en begint te tellen. Gaat op pauze zodra er een object gezien is.
// versie 0.4 / 0.5. Script vereenvoudigd.
// versie 0.5 werkt. Motor draait 20 seconden na indrukken. Gaat op pauze wanneer er een object gezien wordt.
// versie 0.6. Motor dicht / open toggle ingebouwd
// versie 07. Toggle eruit gehaald en script opgesplitst in een openbutton en closebutton.
// Todo: naamconsistentie, duur van het draaien van de motor bovenin definieren, snelheid van de motor als variable meegeven, bij het opengaan hoeft de sensor niet


// zie https://arduinogetstarted.com/tutorials/arduino-actuator
const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N.
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N.
const int openButtonPin = 3; // Aanpassen naar het juiste pinnummer voor de openknop
const int closeButtonPin = 4; // Aanpassen naar het juiste pinnummer voor de openknop
const int sensorButtonPin = 2; // Aanpassen naar het juiste pinnummer voor de sensor

int counter = 0; // Teller
bool startmotoropen = false;
bool startmotordicht = false;

void setup() {
  Serial.begin(9600);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  digitalWrite(ENA_PIN, HIGH);
  pinMode(openButtonPin, INPUT_PULLUP);
  pinMode(closeButtonPin, INPUT_PULLUP);
  pinMode(sensorButtonPin, INPUT);
}

void incrementCounter() {
    static unsigned long lastMillis = 0;
    unsigned long currentMillis = millis();
    
    if (currentMillis - lastMillis >= 1000) { // Tel elke seconde op
        lastMillis = currentMillis;
        counter++;
        Serial.println(counter);
    }
}

void motoruit() {
  digitalWrite(ENA_PIN, HIGH); // Motor uit
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
}

void motoropen() {
  digitalWrite(ENA_PIN, LOW); // Motor aan
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
}

void motordicht() {
  digitalWrite(ENA_PIN, LOW); // Motor aan
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
}

void loop() {
  // wanneer er op de open button geklikt wordt.
  if (digitalRead(openButtonPin) == LOW) {
    counter = 0;
    startmotoropen = true;
    startmotordicht = false;
  } 
  // wanneer er op de close button geklikt wordt.
  if (digitalRead(closeButtonPin) == LOW) {
    counter = 0;
    startmotordicht = true;
    startmotoropen = false;
  } 

  if (startmotoropen){
    if (digitalRead(sensorButtonPin) == LOW) {
      Serial.println("Kip gedetecteerd, teller gepauzeerd, motor uit");
      motoruit();
  } else if (digitalRead(openButtonPin) == HIGH) {
      Serial.println("Geen kip gedetecteerd");
      incrementCounter();
      Serial.println(counter);
      motoropen();
      if (counter >= 20) {
        Serial.println("20 seconden gedraaid. Hok is open!");
        startmotoropen = false;
        counter = 0;
      }
    }
  }

  if (startmotordicht){
    if (digitalRead(sensorButtonPin) == LOW) {
      Serial.println("Kip gedetecteerd, teller gepauzeerd, motor uit");
      motoruit();
  } else if (digitalRead(closeButtonPin) == HIGH) {
      Serial.println("Geen kip gedetecteerd");
      incrementCounter();
      Serial.println(counter);
      motordicht();
      if (counter >= 20) {
        Serial.println("20 seconden gedraaid. Hok is dicht!");
        startmotordicht = false;
        counter = 0;
      }
    }
  }

}
