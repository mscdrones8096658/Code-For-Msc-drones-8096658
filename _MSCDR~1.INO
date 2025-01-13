
// Pin definitions for HC-SR04
#define TRIG_PIN 2
#define ECHO_PIN 3

// Pin definitions for Motor Driver L293D
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define ENA 9
#define ENB 10

// Pin definition for Buzzer
#define BUZZER_PIN 8

// Constants
const int DISTANCE_THRESHOLD = 20; // Απόσταση εμποδίου σε εκατοστά

void setup() {
  // Initialize motor driver pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize HC-SR04 pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Measure distance from obstacle
  long duration, distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Decision based on distance
  if (distance < DISTANCE_THRESHOLD) {
    stopMotors();         // Stop the vehicle
    activateBuzzer();     // Activate the buzzer
    changeDirection();    // Change direction
  } else {
    moveForward();        // Move forward
  }

  delay(100);
}

// Function to move the vehicle forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 150); // Speed for motor A
  analogWrite(ENB, 150); // Speed for motor B
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// Function to activate the buzzer
void activateBuzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500); // Buzzer on for 500ms
  digitalWrite(BUZZER_PIN, LOW);
}

// Function to change direction
void changeDirection() {
  // Reverse the motors for 1 second
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  delay(1000);

  // Stop the motors after changing direction
  stopMotors();
}
