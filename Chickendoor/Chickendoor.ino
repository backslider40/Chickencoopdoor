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

//int button_state = digitalRead(openButtonPin); // Default is High

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
  Serial.print("Timer is gestopt! Verstreken tijd: " + elapsedTime + "miliseconden");
}

void openPoortje() {
  digitalWrite(motor_pin, HIGH);
  Serial.print("Motor gestart")
}

void sluitPoortje() {
  digitalWrite(motor_pin, LOW);
  Serial.print("Motor gestart")
}

boolean checkKip() {
  if (digitalRead(sensorButtonPin) == LOW) {
    Serial.println("Kip gedetecteerd");
    return true;
  } else {
    Serial.println("Geen kip");
    return false;
  }
}

void loop (){
  int button_state = digitalRead(openButtonPin);
  checkKip() // checkt continu of er een kip is of niet.

  if (button_state == LOW && !checkKip()) {
    startTimer();
    openPoortje();

    while (elapsedTime < motor_duration) {
      elapsedTime = millis() - timerStart;
    }
    stopTimer();
  }
}

/*void loop() {
    // Controleer of de knop is ingedrukt
    if (button_state == LOW) {
        // Knop is ingedrukt, start de motor
        motor_running = true;
        motor_start_time = millis();
        //digitalWrite(motor_pin, HIGH);
        Serial.println("Motor gestart");
      // zet hier nog de code voor het starten van de motor
    }
    // controleer op object. LOW betekend gedetecteerd
    if (ir_sensor_state == LOW && motor_running) {
        // Object gedetecteerd, stop de motor
        motor_running = false;
        objectDetected = true;
        Serial.print("Object gedetecteerd, motor gestopt. Resterende tijd: ");
        
        Serial.println(remaining_motor_duration);
        // zet hier nog de code voor het stoppen van de motor
    }
     // controleer of object weg is
    if (ir_sensor_state == HIGH && objectDetected) {
        // Object is weg, start de motor
        motor_running = true;
        objectDetected = false;
        remaining_motor_duration = motor_duration - ((millis() - motor_start_time));
        
        
        // als de looptijd nog niet overschreven is start de motor weer:
        if (motor_duration <= remaining_motor_duration) {
        // zet hier nog de code voor het starten van de motor
        motor_start_time = (millis() - remaining_motor_duration);
        Serial.print("Object is weg, hervat motor. Resterende tijd: ");
        Serial.println(remaining_motor_duration);
        }
    }
}*/
