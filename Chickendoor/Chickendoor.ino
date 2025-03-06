// versie 0.8. Naamconsistentie, duur van het draaien van de motor in variabele, 
// versie 0.81 else if veranderd naar else
// versie 0.82 sensor check uit de startmotoropen gehaald.

// zie https://arduinogetstarted.com/tutorials/arduino-actuator
const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N.
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N.
const int openButtonPin = 3; // Aanpassen naar het juiste pinnummer voor de openknop
const int closeButtonPin = 4; // Aanpassen naar het juiste pinnummer voor de openknop
const int sensorButtonPin = 2; // Aanpassen naar het juiste pinnummer voor de sensor

int counter = 0; // Teller
unsigned long motor_duration = 20; // Motor loopt initieel 20 seconden
bool startmotoropen = false;
bool startmotorclose = false;

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

void motoroff() {
  digitalWrite(ENA_PIN, HIGH); // Motor uit
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
}

void motoropen() {
  digitalWrite(ENA_PIN, LOW); // Motor aan
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
}

void motorclose() {
  digitalWrite(ENA_PIN, LOW); // Motor aan
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
}

void loop() {
  // wanneer er op de open button geklikt wordt.
  if (digitalRead(openButtonPin) == LOW) {
    counter = 0;
    startmotoropen = true;
    startmotorclose = false;
    Serial.println("Hok gaat open!");
  } 
  // wanneer er op de close button geklikt wordt.
  if (digitalRead(closeButtonPin) == LOW) {
    counter = 0;
    startmotorclose = true;
    startmotoropen = false;
    Serial.println("Hok gaat dicht!");
  } 

  if (startmotoropen){
  //  if (digitalRead(sensorButtonPin) == LOW) {
  //    Serial.println("Kip gedetecteerd, teller gepauzeerd, motor uit");
  //    motoroff();
//  } else {
      Serial.println("Hok gaat open!");
      incrementCounter();
      Serial.println(counter);
      motoropen();
      if (counter >= motor_duration) {
        Serial.println(String(motor_duration) + " seconden gedraaid. Hok is open!");
        startmotoropen = false;
        counter = 0;
      }
//    }
  }

  if (startmotorclose){
    if (digitalRead(sensorButtonPin) == LOW) {
      Serial.println("Kip gedetecteerd, teller gepauzeerd, motor uit");
      motoroff();
  } else {
      Serial.println("Geen kip gedetecteerd, hok gaat dicht!");
      incrementCounter();
      Serial.println(counter);
      motorclose();
      if (counter >= motor_duration) {
        Serial.println(String(motor_duration) + " seconden gedraaid. Hok is dicht!");
        startmotorclose = false;
        counter = 0;
      }
    }
  }

}
