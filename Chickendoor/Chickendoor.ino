// versie 0.3. Deze werkt. De teller telt op. Wanneer ik op de button klik gaat de teller op 0 en begint te tellen. Gaat op pauze zodra er een object gezien is.


// Pinnummers voor knoppen en motor
const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N.
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N.
const int openButtonPin = 3; // Aanpassen naar het juiste pinnummer voor de openknop
const int closeButtonPin = 4; // Aanpassen naar het juiste pinnummer voor de dichtknop
const int sensorButtonPin = 2; // Aanpassen naar het juiste pinnummer voor de sensor. E18-D80NK Bruin 5v, Blue GND, Zwart signal

// Default waardes
unsigned long timerStart = 0;
unsigned long timerEnd = 0;
unsigned long elapsedTime = 0;
unsigned long motor_duration = 20000;
int counter = 0; // Teller
bool paused = false;
bool startmotor = false;

void setup() {
  Serial.begin(9600);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  digitalWrite(ENA_PIN, HIGH);
  pinMode(openButtonPin, INPUT_PULLUP); // Interne pull-up weerstand voor de vooruitknop
  pinMode(closeButtonPin, INPUT_PULLUP); // Interne pull-up weerstand voor de achteruitknop
  pinMode(sensorButtonPin, INPUT); // Interne pull-up weerstand voor de pauzeknop
}

void startTimer() {
  timerStart = millis();
  timerEnd = 0;
  elapsedTime = 0;
  Serial.println("Timer is gestart!");
}

void stopTimer() {
  timerEnd = millis();
  elapsedTime = timerEnd - timerStart;
  //Serial.print("Timer is gestopt! Verstreken tijd: " + elapsedTime + "miliseconden");
}

void incrementCounter() {
    unsigned long currentMillis = millis();
     static unsigned long lastMillis = 0;
   
    if (currentMillis - lastMillis >= 1000) { // Tel elke seconde op
        lastMillis = currentMillis;
        counter++;
        Serial.println(counter);
    }
}

 void openPoortje() {
//  digitalWrite(motor_pin, HIGH);
  Serial.print("Motor gestart");
}

void sluitPoortje() {
  // digitalWrite(motor_pin, LOW);
  Serial.print("Motor gestart");
}

boolean checkKip() {
  if (digitalRead(sensorButtonPin) == LOW) {
    Serial.println("Kip gedetecteerd");
    Serial.println(counter);
    // stop motor script hier.
    return true;
  } else {
    Serial.println("Geen kip");
    incrementCounter();
    Serial.println(counter);
    // start motor script hier.
    return false;
  }
}

void loop (){
  int button_state = digitalRead(openButtonPin);
  checkKip(); // checkt continu of er een kip is of niet.
  if (button_state == LOW){
    startmotor = true;
    counter = 0;
  } 
  
  if (startmotor) {
      paused = true;
  } else {
      paused = false;
      
  }

  if (!paused) {
      incrementCounter();
      Serial.println(counter);

  }
}