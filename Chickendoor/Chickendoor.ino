// Pinnummers voor knoppen en motor
const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N.
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N.

const int openButtonPin = 3; // Aanpassen naar het juiste pinnummer voor de openknop
const int closeButtonPin = 4; // Aanpassen naar het juiste pinnummer voor de dichtknop
const int sensorButtonPin = 2; // Aanpassen naar het juiste pinnummer voor de sensor

bool motor_running = false;
unsigned long motor_start_time = 0;
unsigned long motor_duration = 20; // Motor loopt initieel 20 seconden
unsigned long remaining_motor_duration = 0; // Resterende tijd van de motor

// Create servo object for motor
Servo motor;

// Variable to track button state
bool buttonPressed = false;

// Variable to track infrared sensor state
bool objectDetected = false;

void setup() {
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  digitalWrite(ENA_PIN, HIGH);

  pinMode(openButtonPin, INPUT_PULLUP); // Interne pull-up weerstand voor de vooruitknop
  pinMode(closeButtonPin, INPUT_PULLUP); // Interne pull-up weerstand voor de achteruitknop
  pinMode(sensorButtonPin, INPUT); // Interne pull-up weerstand voor de pauzeknop

  Serial.begin(9600);
  Serial.println("Motor gestopt. Druk op een knop om te starten.");
}

void loop() {
    // Controleer of de knop is ingedrukt
    int button_state = digitalRead(openButtonPin);
    if (button_state == LOW) {
        // Knop is ingedrukt, start de motor
        motor_running = true;
        motor_start_time = millis();
        //digitalWrite(motor_pin, HIGH);
        Serial.println("Motor gestart");
      // zet hier nog de code voor het starten van de motor
    }
    // controleer op object 
    if (ir_sensor_state == LOW) {
        // Object gedetecteerd, stop de motor
        motor_running = false;
        Serial.print("Object gedetecteerd, motor gestopt. Resterende tijd: ");
        // zet hier nog de code voor het stoppen van de motor
    }
     // controleer of object weg is
    if (ir_sensor_state == HIGH) {
        // Object is weg, start de motor
        motor_running = true;
        remaining_motor_duration = (millis() - motor_start_time);
        Serial.print("Object is weg, hervat motor. Resterende tijd: ");
        
        // als de looptijd nog niet overschreven is start de motor weer:
        if (millis() - motor_start_time >= remaining_motor_duration) {
        // zet hier nog de code voor het starten van de motor
        motor_start_time = millis() - remaining_motor_duration
        }
    }
}
