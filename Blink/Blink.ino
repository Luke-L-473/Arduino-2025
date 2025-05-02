#include <Servo.h> 

// variables
const int trigPin = 2;
const int echoPin  = 9;

long duration;
int  distance;

int buzzpin = 7;
int buzzState = LOW;

int ledRed = 3;
int ledGreen = 4;

int switchpin = 10;
int ledStatus = 8;

byte leds = 0;

bool canSpin = true;

unsigned long previousMillis = 0;

const long intervalFar = 250;
const long intervalClose = 50;
const long intervalIdle = 1250;

Servo myServo; 


void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  myServo.attach(12); 
  pinMode(buzzpin, OUTPUT);
  Serial.begin(9600);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(switchpin, INPUT);
  pinMode(ledStatus, OUTPUT);
}

// turning the radar on-off
void loop() {
  if (digitalRead(switchpin) == HIGH){
    digitalWrite(ledStatus, LOW);
    StartScan();
  }
  if (digitalRead(switchpin) == LOW){
    digitalWrite(ledStatus, HIGH);
  }
}

// calculating the distance to a detected object
int calculateDistance(){ 
  digitalWrite(trigPin,  LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // reads echoPin and returns the sound wave travel time (ms)
  distance = duration * 0.034 / 2;
  return distance;
}

// start scanning for objects
void StartScan() {
  // checking for every degree

  // first from right to left
  for (int i = 15; i <= 165; i++) {  
    myServo.write(i);
    delay(30);
    distance = calculateDistance();

    // checking if something is detected in the 40 cm range
    if (distance <= 40 && distance > 20) {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= intervalFar) {
        previousMillis = currentMillis;

        if (buzzState == LOW) {
          buzzState = HIGH;
        } else {
          buzzState = LOW;
        }

        digitalWrite(buzzpin, buzzState);
        digitalWrite(ledRed, buzzState); 
        digitalWrite(ledGreen, HIGH); 
      }
    } else if (distance <= 20 && distance > 0) {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= intervalClose) {
        previousMillis = currentMillis;

        if (buzzState == LOW) {
          buzzState = HIGH;
        } else {
          buzzState = LOW;
        }

        digitalWrite(buzzpin, buzzState);
        digitalWrite(ledRed, buzzState); 
        digitalWrite(ledGreen, HIGH); 
      }
    } else if (distance > 40) {
      digitalWrite(buzzpin, LOW);
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, HIGH); 
    }
      
    Serial.print(i); 
    Serial.print(","); 
    Serial.print(distance);  
    Serial.print(".");
  }

  // then from left to right
  for (int i = 165; i >= 15; i--) {  
    myServo.write(i);
    delay(30);
    distance  = calculateDistance();

    if (distance <= 40 && distance > 20) {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= intervalFar) {
        previousMillis = currentMillis;

        if (buzzState == LOW) {
          buzzState = HIGH;
        } else {
          buzzState = LOW;
        }

        digitalWrite(buzzpin, buzzState);
        digitalWrite(ledRed, buzzState); 
        digitalWrite(ledGreen, HIGH); 
      }
    } else if (distance <= 20 && distance > 0) {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= intervalClose) {
        previousMillis = currentMillis;

        if (buzzState == LOW) {
          buzzState = HIGH;
        } else {
          buzzState = LOW;
        }

        digitalWrite(buzzpin, buzzState);
        digitalWrite(ledRed, buzzState); 
        digitalWrite(ledGreen, HIGH); 
      }
    } else if (distance > 40) {
      digitalWrite(buzzpin, LOW);
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, HIGH); 
    }

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}