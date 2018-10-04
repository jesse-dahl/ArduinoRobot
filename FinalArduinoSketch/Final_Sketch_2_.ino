#include <Servo.h>

Servo servoLeft;
Servo servoRight;

void setup() {
  Serial.begin(9600);
  Serial.println("Testing QTI Sensor");

  tone(4, 500, 500); delay(500);
  tone(4, 1500, 500); delay(500);
  tone(4, 1000, 500); delay(500);
  tone(4, 2000, 500); delay(500);
  
  //--Setup Motors
  servoLeft.attach(11);
  servoRight.attach(12);
  halt();
  delay(1000);

  //--Setup IR LED and Detector
  pinMode(9, OUTPUT); //IR LED
  pinMode(10, INPUT); //IR Detector

}

void loop() {
////////////////////////////////////////////
// FAR RIGHT QTI SENSOR
////////////////////////////////////////////
  //-- Charger capacitator for 1ms
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  delay(1);

  //-- Wait 1ms and let capacitator discharge
  pinMode(2, INPUT);
  delay(1);

  //-- read pin 2

  byte sensor1 = digitalRead(2);

//////////////////////////////////////////
//MIDDLE RIGHT SENSOR
//////////////////////////////////////////
 //-- Charger capacitator for 1ms
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  delay(1);

  //-- Wait 1ms and let capacitator discharge
  pinMode(3, INPUT);
  delay(1);

  //-- read pin 3

  byte sensor2 = digitalRead(3);

/////////////////////////////////////////
//MIDDLE LEFT SENSOR
/////////////////////////////////////////
 //-- Charger capacitator for 1ms
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  delay(1);

  //-- Wait 1ms and let capacitator discharge
  pinMode(4, INPUT);
  delay(1);

  //-- read pin 4

  byte sensor3 = digitalRead(4);

////////////////////////////////////////
//FAR LEFT SENSOR
////////////////////////////////////////
 //-- Charger capacitator for 1ms
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  delay(1);

  //-- Wait 1ms and let capacitator discharge
  pinMode(5, INPUT);
  delay(1);

  //-- read pin 5

  byte sensor4 = digitalRead(5);

/////////////////////////////////////
//IR HEADLAMP
/////////////////////////////////////
  tone(9, 38000, 8); // turned on IR pulse
  delay(1);
  byte irDetect = digitalRead(10);
  delay(100);
/////////////////////////////////////
//Motion
/////////////////////////////////////

  Serial.println(irDetect);

  if (irDetect == 0)
  {
    halt();
    delay(3000);
  }
  
  if ((sensor1 == 0) && (sensor2 == 0))
  {
    veerLeft(100);
  }
  else
  {
    veerRight(100);
  }
  if ((sensor3 == 0) && (sensor4 == 0))
  {
    veerRight(100);
  }
  else
  {
    veerLeft(100);
  }
}

///////////////////////////////////////////////
//Navigation Functions
///////////////////////////////////////////////

void veerLeft(int time)
{
  servoLeft.writeMicroseconds(1500 + 40);
  servoRight.writeMicroseconds(1500 - 60);
  delay(time);
}

void veerRight(int time)
{
  servoLeft.writeMicroseconds(1500 + 60);
  servoRight.writeMicroseconds(1500 - 40);
  delay(time);
}

void halt()
{
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void moveForward(int time)
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(time);
}

void moveBackward(int time)
{
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  delay(time);
}

void turnRight90()
{
  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1600);
  delay(800); //adjust according to surface
}

void turnLeft90()
{
  servoLeft.writeMicroseconds(1400);
  servoRight.writeMicroseconds(1400);
  delay(800); //adjust according to surface
}
