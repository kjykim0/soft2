/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/faq/how-to-control-speed-of-servo-motor
 */

#include <Servo.h>

#define SND_VEL 346.0
#define PIN_LED  9
#define PIN_SERVO 10
#define PIN_TRIG 12
#define PIN_ECHO 13
#define PULSE_DURATION 10
#define SCALE (0.001 * 0.5 * SND_VEL)

Servo myServo;
unsigned long MOVING_TIME = 1000; // moving time is 3 seconds
unsigned long moveStartTime;
int angleUD = -1;
bool ifStart = false;
float dist;

void setup() {
  Serial.begin(57600);
  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_TRIG,OUTPUT);
  pinMode(PIN_ECHO,INPUT);
  digitalWrite(PIN_TRIG, LOW);
  myServo.attach(PIN_SERVO);
  moveStartTime = millis(); // start moving

  myServo.write(0); // Set position
  delay(500);
  moveStartTime = millis();
}

void loop() {
  Serial.println("sigmoid");
  sigmoid_Block();
  Serial.println("sin");
  sin_Block();
}

void sigmoid_Block(){
  unsigned long progress;
  dist = USS_measure(PIN_TRIG,PIN_ECHO);
  while(dist > 200){
    dist = USS_measure(PIN_TRIG,PIN_ECHO);
  }
  moveStartTime = millis();
  progress = 0;
  while(progress <= MOVING_TIME){
    progress = millis() - moveStartTime;
    float angle = (float(progress) / (MOVING_TIME / 2) - 1) * 4;
    angle = sigmoid(angle) * 90;
    myServo.write(angle);
  }
  while(dist <= 200){
    dist = USS_measure(PIN_TRIG,PIN_ECHO);
  }
  moveStartTime = millis(); // reset start time for next movement
  progress = 0;
  while (progress <= MOVING_TIME) {
  // while moving
    progress = millis() - moveStartTime;
    float angle = (float(progress) / (MOVING_TIME / 2) - 1) * 4 * -1;
    angle = sigmoid(angle) * 90; 
    myServo.write(angle);
  }
}

void sin_Block(){
  unsigned long progress;
  dist = USS_measure(PIN_TRIG,PIN_ECHO);
  while(dist > 200){
    dist = USS_measure(PIN_TRIG,PIN_ECHO);
  }
  moveStartTime = millis();
  progress = 0;
  while(progress <= MOVING_TIME){
    progress = millis() - moveStartTime;
    float angle = (float(progress) / (MOVING_TIME / 2) - 1) * 90;
    angle = sin(radians(angle)) * 45 + 45;
    myServo.write(angle);
  }
  while(dist <= 200){
    dist = USS_measure(PIN_TRIG,PIN_ECHO);
  }
  moveStartTime = millis(); // reset start time for next movement
  progress = 0;
  while (progress <= MOVING_TIME) {
  // while moving
    progress = millis() - moveStartTime;
    float angle = (float(progress) / (MOVING_TIME / 2) - 1) * 90 * -1;
    angle = sin(radians(angle)) * 45 + 45;
    myServo.write(angle);
  }
}

float sigmoid(float x){
  return 1.0 / (1.0 + exp(-x));
}

float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH) * SCALE; // unit: mm
}
  
