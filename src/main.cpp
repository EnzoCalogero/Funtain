#include <Arduino.h>


//HC-SR04 A
const int trigPinR = 9;
const int echoPinR = 10;
int trigPin;
int echoPin;

// defines variables
long duration;
int distance;

//HC-SR04 B
const int trigPinL = 13;
const int echoPinL = 12;

// Motor A  Right
 
const int enA = 6;  
const int in1 = 8;
const int in2 = 7;
 
// Motor B Left
 
const int enB = 3;
const int in3 = 5;
const int in4 = 4;

// Motor Place Holders
int en;
int ina;
int inb;

//LED RGB
const int red_light_pin= 11;
const int green_light_pin = 0;
const int blue_light_pin = 1;


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
  
// LED

  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

}


void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}


void check_color(void)
{
// put your main code here, to run repeatedly:
  RGB_color(255, 0, 0); // Blue
  delay(1000);
  RGB_color(0, 255, 0); // Green
  delay(1000);
  RGB_color(0, 0, 255); // Red
  delay(1000);  
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
 
  
  
  // Now turn off motors
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
 
}
 


void engines(char flag, int distance)
{
 if (flag =='R'){
                  ina = in1;
                  inb = in2;
                  en = enA;

 }
  Serial.println("sono nel enginers");
  Serial.println(flag);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
 
  // Accelerate from zero to maximum speed
 // modified max from 256 to 150
  for (int i = 0; i < 250; i++)
 
  {
 
   analogWrite(enA, i);
   analogWrite(enB, i);
 
    delay(20);
 
  } 

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}
 
int hc_04(char flag)
{
  if (flag == 'R'){ //Right Sensor
                trigPin = trigPinR;
                echoPin = echoPinR;
                 }
  else           {  //Left Sensor      
                trigPin = trigPinL;
                echoPin = echoPinL;
                }

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance = duration*0.034/2;
// Prints the distance on the Serial Monitor
 Serial.print("Distance: ");
 Serial.print(flag);
 Serial.println(distance);
 if (distance < 7) {
                  distance = 0;
                  }
 else if (distance < 12) {
                  distance = 1;
                  }
 else if (distance < 20)
                  { 
                  distance = 2;
                  }
 else if (distance < 30)
                  { 
                  distance = 3;
                  }        
 else {
                  distance = 4;
}                        
Serial.println(distance);
return distance;
}


void loop()
 {
//Check Right side...
distance=hc_04('R');
Serial.println("in loop");
Serial.println(distance);
//Check Left side
distance=hc_04('L');
Serial.println(distance);
engines('R',2);
delay(1000);
}
