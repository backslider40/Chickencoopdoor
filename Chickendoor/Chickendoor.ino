// versie 0.3. Deze werkt. De teller telt op. Wanneer ik op de button klik gaat de teller op 0 en begint te tellen. Gaat op pauze zodra er een object gezien is.
// versie 0.4. Script vereenvoudigd.
// versie 0.5. Script vereenvoudigd.

const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N.
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N.
const int openButtonPin = 3; // Aanpassen naar het juiste pinnummer voor de openknop
const int sensorButtonPin = 2; // Aanpassen naar het juiste pinnummer voor de sensor

int counter = 0; // Teller
bool paused = false;

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
    // paused = true;
  } 
  
  if (digitalRead(sensorButtonPin) == LOW) {
    Serial.println("Kip gedetecteerd, teller gepauzeerd");
    // paused = true;
  } else if (digitalRead(openButtonPin) == HIGH) {
    Serial.println("Geen kip gedetecteerd");
    incrementCounter();
    Serial.println(counter);
    // paused = false;
    if (counter == 20) {
      // paused = true;
    }
  }
  

}
