#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 8;

const int threshold = 15;   
const int targetCount = 5;  

Servo myServo;

int triggerCount = 0;
bool handNow = false;
bool actionDone = false;

float readDistanceCm() {
  long duration;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); 

  if (duration == 0) return -1;

  return duration * 0.0343 / 2.0;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(servoPin, INPUT);  

  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  float distance = readDistanceCm();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Count: ");
  Serial.println(triggerCount);

  bool handDetected = (distance > 0 && distance < threshold);

  if (handDetected && !handNow) {
    triggerCount++;
    Serial.print("Hand detected: ");
    Serial.println(triggerCount);
  }

  handNow = handDetected;


  if (triggerCount >= targetCount && !actionDone) {
    Serial.println("Servo move");

    myServo.attach(servoPin);
    delay(300);

    myServo.write(90);      
    delay(1000);

    myServo.detach();       
    pinMode(servoPin, INPUT);

    actionDone = true;
  }

  delay(200);
}
