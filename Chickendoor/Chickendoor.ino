// versie 0.3. Deze werkt. De teller telt op. Wanneer ik op de button klik gaat de teller op 0 en begint te tellen. Gaat op pauze zodra er een object gezien is.
// versie 0.4 / 0.5. Script vereenvoudigd.
// versie 0.5 werkt. Motor draait 20 seconden na indrukken. Gaat op pauze wanneer er een object gezien wordt.
// versie 0.6. Motor dicht / open toggle ingebouwd
// ToDo: script opsplitsen in een openbutton en close button.


// zie https://arduinogetstarted.com/tutorials/arduino-actuator
const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N.
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N.
const int openButtonPin = 3; // Aanpassen naar het juiste pinnummer voor de openknop
const int sensorButtonPin = 2; // Aanpassen naar het juiste pinnummer voor de sensor

int counter = 0; // Teller
bool startmotor = false;
bool motorDirection = false;  // Motor draairichting (false = voorwaarts, true = achteruit)

void setup() {
  Serial.begin(9600);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  digitalWrite(ENA_PIN, HIGH);
  pinMode(openButtonPin, INPUT_PULLUP);
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

void loop() {
  if (digitalRead(openButtonPin) == LOW) {
    counter = 0;
    startmotor = true;
  } 
  
  if (startmotor){
    if (digitalRead(sensorButtonPin) == LOW) {
      Serial.println("Kip gedetecteerd, teller gepauzeerd");
      digitalWrite(IN1_PIN, LOW);  // Motor uit
      digitalWrite(IN2_PIN, LOW);  // motor uit
  } else if (digitalRead(openButtonPin) == HIGH) {
      Serial.println("Geen kip gedetecteerd");
      incrementCounter();
      Serial.println(counter);
      if (motorDirection) {
        digitalWrite(IN1_PIN, LOW);  // Draai motor achteruit
        digitalWrite(IN2_PIN, HIGH);
        Serial.println("Motor dicht stand");
      } else {
        digitalWrite(IN1_PIN, HIGH); // Draai motor vooruit
        digitalWrite(IN2_PIN, LOW);
        Serial.println("Motor open stand");
  }

      if (counter >= 20) {
        Serial.println("20 sec gedraaid");
        startmotor = false;
        counter = 0;
        motorDirection = !motorDirection;
      }
    }
  }

}
