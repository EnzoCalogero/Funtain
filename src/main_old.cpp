#include <Arduino.h>


//HC-SR04 A
const int trigPinR = 9;
const int echoPinR = 10;
int trigPin;
int echoPin;

// defines variables
long duration;
int distance;
int L_distance;
int R_distance;

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

//LED RGB Right
const int r_red_light_pin= 11;
const int r_green_light_pin = 0;
const int r_blue_light_pin = 1;

//LED RGB Left
const int l_red_light_pin= A2;
const int l_green_light_pin = A3;
const int l_blue_light_pin = A4;


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
 
  // for Debug 
  Serial.begin(9600); // Starts the serial communication

//Set for HC04 Left
  pinMode(trigPinL, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinL, INPUT); // Sets the echoPin as an Input
  
// LED Right

 pinMode(r_red_light_pin, OUTPUT);
 pinMode(r_green_light_pin, OUTPUT);
 pinMode(r_blue_light_pin, OUTPUT);

// LED Left
 pinMode(l_red_light_pin, OUTPUT);
 pinMode(l_green_light_pin, OUTPUT);
 pinMode(l_blue_light_pin, OUTPUT);
}


void r_RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(r_red_light_pin, red_light_value);
  analogWrite(r_green_light_pin, green_light_value);
  analogWrite(r_blue_light_pin, blue_light_value);
}

void l_RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(l_red_light_pin, red_light_value);
  analogWrite(l_green_light_pin, green_light_value);
  analogWrite(l_blue_light_pin, blue_light_value);
}



void OutPut(int R_distance, int L_distance)
{
// Right side  
int R_pwm; // Pulse Width Modulation range 0~255
  if (R_distance ==0) {
                  R_pwm = 255;
                  r_RGB_color(0, 0, 255);
                  }
 else if (R_distance == 1) {
                  R_pwm = 200;
                  r_RGB_color(255, 255, 0);
                  }
 else if (R_distance == 2)
                  { 
                  R_pwm = 150;
                  r_RGB_color(0, 255, 0);
                  }
 else if (R_distance == 3)
                  { 
                  R_pwm = 100;
                  r_RGB_color(255, 0, 0);
                  }        
 else {
                  R_pwm = 0;
                  r_RGB_color(0, 0, 0);
}               

// Left side  
int L_pwm; // Pulse Width Modulation range 0~255
  if (L_distance ==0) {
                  L_pwm = 255;
                  l_RGB_color(0, 0, 255);
                  }
 else if (L_distance == 1) {
                  L_pwm = 200;
                  l_RGB_color(255, 255, 0);
                  }
 else if (L_distance == 2)
                  { 
                  L_pwm = 150;
                  l_RGB_color(0 , 250, 0);
                  }
 else if (L_distance == 3)
                  { 
                  L_pwm = 100;
                  l_RGB_color(250 , 0, 0);
                  }        
 else {
                  L_pwm = 0;
                  l_RGB_color(0 , 0, 0);
}               

  //left side
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  // left side
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enA, R_pwm);
  analogWrite(enB, L_pwm);
 
  Serial.println();
  Serial.println(R_pwm);
  Serial.println(L_pwm);
  Serial.println();
  // led settings

  delay(1000);
 
  
  
  // Now turn off motors
 // to check....
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
 //Serial.print("Distance: ");
 //Serial.print(flag);
 //Serial.println(distance);
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
//Serial.println(distance);
return distance;
}


void loop()
 {
//r_check_color();   
//l_check_color();

//Check Right side...
R_distance = hc_04('R');
//Serial.println("in loop");
//Serial.println(distance);

//engines('R',distance);

//Check Left side
L_distance = hc_04('L');
OutPut( R_distance, L_distance);
//Serial.println(distance);
//engines('R',2);

delay(100);

}
