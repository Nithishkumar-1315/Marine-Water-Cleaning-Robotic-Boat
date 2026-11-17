
#include <SoftwareSerial.h>

// ESP32-CAM communication
SoftwareSerial espSerial(10, 11);

// L298N propulsion motor pins
#define ENA 3
#define IN1 4
#define IN2 7

#define ENB 5
#define IN3 8
#define IN4 12

// L293D conveyor motor pins
#define CONVEYOR_EN 6
#define CONVEYOR_IN1 A0
#define CONVEYOR_IN2 A1

// Ultrasonic sensor pins
#define TRIG A2
#define ECHO A3

// Obstacle distance threshold
#define OBSTACLE_DISTANCE 25

char detection = 'N';
bool turnDirection = false;

long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0) return 999;

  return duration * 0.034 / 2;
}

// Propulsion motor control
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void stopBoat() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 170);
  analogWrite(ENB, 170);

  delay(600);
  stopBoat();
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 170);
  analogWrite(ENB, 170);

  delay(600);
  stopBoat();
}

// Waste collection mechanism
void startConveyor() {
  digitalWrite(CONVEYOR_IN1, HIGH);
  digitalWrite(CONVEYOR_IN2, LOW);
  analogWrite(CONVEYOR_EN, 180);
}

void stopConveyor() {
  analogWrite(CONVEYOR_EN, 0);
  digitalWrite(CONVEYOR_IN1, LOW);
  digitalWrite(CONVEYOR_IN2, LOW);
}

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(CONVEYOR_EN, OUTPUT);
  pinMode(CONVEYOR_IN1, OUTPUT);
  pinMode(CONVEYOR_IN2, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  stopBoat();
  stopConveyor();

  Serial.println("Marine Cleaning Boat Started");
}

void loop() {

  // Receive ESP32-CAM classification
  if (espSerial.available()) {
    String message = espSerial.readStringUntil('\n');
    message.trim();

    if (message == "P") {
      detection = 'P';
      Serial.println("Plastic Detected");
    }
    else if (message == "NS") {
      detection = 'N';
      Serial.println("Non-Plastic Detected");
    }
  }

  // Check obstacle distance
  long distance = getDistance();

  if (distance <= OBSTACLE_DISTANCE) {

    stopBoat();
    stopConveyor();

    Serial.println("Obstacle Detected");

    if (turnDirection == false) {
      turnLeft();
    }
    else {
      turnRight();
    }

    turnDirection = !turnDirection;
  }

  else {

    moveForward();

    if (detection == 'P') {
      startConveyor();
    }
    else {
      stopConveyor();
    }
  }

  delay(100);
}
