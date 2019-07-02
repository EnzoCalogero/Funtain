#include <Arduino.h>


//HC-SR04 A
const int trigPinR = 9;
const int echoPinR = 10;

// defines variables
long durationR;
int distanceR;

//HC-SR04 B
const int trigPinL = 13;
const int echoPinL = 12;

// defines variables
long durationL;
int distanceL;

// Motor A  Right
 
int enA = 6;  //was 9
int in1 = 8;
int in2 = 7;
 
// Motor B Left
 
int enB = 3;
int in3 = 5;
int in4 = 4;
 
void setup()
 
{
 
  // Set all the motor control pins to outputs
 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 
//Set for HC04 Right
  pinMode(trigPinR, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinR, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

//Set for HC04 Left
  pinMode(trigPinL, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinL, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
 
void demoOne()
 
{
 
  // This function will run the motors in both directions at a fixed speed
 
  // Turn on motor A
 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enA, 100);
 
  // Turn on motor B
 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enB, 100);
 
  delay(2000);
 
  
  delay(2000);
 
  // Now turn off motors
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
 
}
 


void demoTwo()
 
{
 
  // This function will run the motors across the range of possible speeds
  // Note that maximum speed is determined by the motor itself and the operating voltage
 
  // Turn on motors
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
 
  // Accelerate from zero to maximum speed
 // modified max from 256 to 150
  for (int i = 0; i < 150; i++)
 
  {
 
    analogWrite(enA, i);
    analogWrite(enB, i);
 
    delay(20);
 
  } 
 
  // Decelerate from maximum speed to zero
 // modified max from 256 to 150
 
  for (int i = 150; i >= 0; --i)
 
  {
 
    analogWrite(enA, i);
    analogWrite(enB, i);
 
    delay(20);
 
  } 
 
  // Now turn off motors
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
 
}
 
void engines(int distR, int distL)
{
  Serial.print("Distance (Right): ");
  Serial.println(distR);
  Serial.print("Distance (Left): ");
  Serial.println(distL);
}

void loop()
 
{
 
  //demoOne();
  //delay(1000);
  //demoTwo();
  delay(500);

//Check Right side...

digitalWrite(trigPinR, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPinR, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinR, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
durationR = pulseIn(echoPinR, HIGH);
// Calculating the distance
distanceR= durationR*0.034/2;
// Prints the distance on the Serial Monitor



//Check Left side...

digitalWrite(trigPinL, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPinL, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinL, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
durationL = pulseIn(echoPinL, HIGH);
// Calculating the distance
distanceL= durationL*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Distance (Left): ");
//Serial.println(distanceL);
engines(distanceR, distanceL);
}