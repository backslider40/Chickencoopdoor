// Pinnummers voor knoppen en motor
const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N

const int openButtonPin = 3; // Aanpassen naar het juiste pinnummer voor de openknop
const int closeButtonPin = 4; // Aanpassen naar het juiste pinnummer voor de dichtknop
const int sensorButtonPin = 2; // Aanpassen naar het juiste pinnummer voor de sensor

bool motor_running = false;
unsigned long motor_start_time = 0;
unsigned long motor_duration = 20; // Motor loopt initieel 20 seconden
unsigned long remaining_motor_duration = 0; // Resterende tijd van de motor

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
        remaining_motor_duration = motor_duration * 1000; // Zet de resterende tijd opnieuw
        //digitalWrite(motor_pin, HIGH);
        Serial.println("Motor gestart");
    }

    // Controleer of de motor draait
    if (motor_running) {
        // Controleer of er een object wordt gedetecteerd door de infraroodsensor
        int ir_sensor_state = digitalRead(sensorButtonPin);
        if (ir_sensor_state == LOW) {
            // Object gedetecteerd, stop de motor
            motor_running = false;
            remaining_motor_duration -= (millis() - motor_start_time);
            //digitalWrite(motor_pin, LOW);
            Serial.print("Object gedetecteerd, motor gestopt. Resterende tijd: ");
            Serial.print(remaining_motor_duration / 1000);
            Serial.println(" seconden");
        } else {
            // Object niet gedetecteerd, controleer of de motor-duur is verstreken
            if (millis() - motor_start_time >= remaining_motor_duration) {
                motor_running = false;
                //digitalWrite(motor_pin, LOW);
                Serial.println("Motor gestopt (duur verstreken)");
            }
        }
    } else {
        // Motor is gestopt, controleer opnieuw of er een object wordt gedetecteerd
        int ir_sensor_state = digitalRead(sensorButtonPin);
        if (ir_sensor_state == HIGH) {
            // Object niet gedetecteerd, hervat de motor.
            motor_running = true;
            motor_start_time = millis();
            //digitalWrite(motor_pin, HIGH);
            Serial.println("Motor hervat");
        }
    }
}