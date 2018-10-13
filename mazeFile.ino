
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>
MeDCMotor motor_9(9);
MeDCMotor motor_10(10);   

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
void detectWall();
void detectWallWhileTurning();
void detectWallRight();
double WallDetected;
double DistToWall;
double RoomSize;
MeUltrasonicSensor ultrasonic_3(3);
void turnRight();
double Speed;
MeLineFollower linefollower_2(2);
void nudgeRight();
void nudgeLeft();
void turnLeft();
void Initialize();
double CmPerSecond;
void stopMovement();
void moveForward(double distance);
double Duration;
double currentTime = 0;
double lastTime = 0;


void _delay(float seconds){
  long endTime = millis() + seconds * 1000;
 while(millis() < endTime)_loop();
}

void _loop(){
  
}

void move(int direction, int speed)

{
   int leftSpeed = 0;
   int rightSpeed = 0;
   Serial.println("DEBUG2");
   Serial.println(speed);
   if(direction == 1){
      leftSpeed = speed;
      rightSpeed = speed;
   }else if(direction == 2){
      leftSpeed = -speed;
      rightSpeed = -speed;
   }else if(direction == 3){
      leftSpeed = -speed;
      rightSpeed = speed;
   }else if(direction == 4){
      leftSpeed = speed;
      rightSpeed = -speed;
   }
   
   motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
   motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}
        
double getLastTime(){
    return currentTime = millis()/1000.0 - lastTime;
}

void detectWall()
{
  WallDetected = 0;
  _delay(0.2);
  
  DistToWall = ultrasonic_3.distanceCm();

  Duration += 0.2;  

  if((DistToWall) < (2*RoomSize)){
    WallDetected = 1;
  } 
  
}

void detectWallWhileTurning() {
  {
  WallDetected = 0;
  _delay(0.2);
  
  DistToWall = ultrasonic_3.distanceCm();

  Duration += 0.2;  

  if((DistToWall) < (2 * RoomSize)){
    WallDetected = 1;
  } 
  }
}

void turnRight()
{
  move(4, 5 * Speed);
  
  _delay(0.25);
  

  //  _loop();
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  move(4, 5 * Speed);
  stopMovement();
  
}

void nudgeRight()
{
  move(4,(Speed) * (0.8));
  
  _delay(0.02);
  
  Duration += 0.02;
  
  move(1,Speed);
  
}

void nudgeLeft()
{
  move(3,(Speed) * (0.8));
  
  _delay(0.02);
  
  Duration += 0.02;
  
  move(1,Speed);
  
}
void turnLeft()
{
  move(3,Speed);
  
  _delay(0.25);
  
  
  stopMovement();
  
}

void Initialize()
{
  Serial.begin(9600);
  RoomSize = 10.00;
  
  CmPerSecond = 12.5;
  
  Speed = 100;
  
}

void stopMovement()
{
  move(1,0);
  
}

void moveForward(double distance)
{

  lastTime = millis()/1000.0;
  
  Duration = (distance) / (CmPerSecond);
  
  move(1,(Speed));
  
  //stopMovement();
  
}

void setup() {
  Initialize();
  
}

void detectWallRight(){
  _delay(1);
  detectWallWhileTurning();
}

void loop(){

  if((WallDetected) == 0) {
  moveForward(RoomSize);
  detectWall();
  
  }else {
    stopMovement();
    turnRight();
    detectWallRight();
  }
  
  
}




