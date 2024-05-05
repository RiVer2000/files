#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>

//Servo Limits
////////////////////////////////////
#define J1SERVO_MIN 0
#define J1SERVO_MAX 160
#define J2SERVO_MIN 70
#define J2SERVO_MAX 160
////////////////////////////////////

//PING Sensor Constants
const int SigPin = 2;
float ping_invcmCosnt = (2*1000000)/(100*344.8); //cmDist=rawTime/invcmCosnt

//IMU Constants and Global Variables
const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;

//Arm Servo Objects
Servo joint1servo;         //range is 0 to 160. midpoint is 90
Servo joint2servo;         // range is 70 to 160
Servo gripperservo;       //range is 15 to 85? open is 85, close is 15

//Drive Motor Pins
int driveLPin = 5; // PWM for left motor
int driveRPin = 11;  // PWM for right motor
int dirLPin = 12;   //direction for left motor  
int dirRPin = 13;   //direction for right motor
char keyboard_input = 0;



int current_angleJ1 = joint1servo.read();
int current_angleJ2 = joint2servo.read();
int current_angleG = gripperservo.read();

void drive_forward()
{
  //Set wheel directions to move forward
  digitalWrite(dirLPin,0);
  digitalWrite(dirRPin,1);
  //Drive forward for t time in ms and stop.
  analogWrite(driveLPin,80);
  analogWrite(driveRPin,80);
  delay(25);
}

void drive_backward()
{
    //Set wheel directions to move backward
  digitalWrite(dirLPin,1);
  digitalWrite(dirRPin,0);
  //Drive forward for t time in ms and stop.
  analogWrite(driveLPin,80);
  analogWrite(driveRPin,80);
  delay(25);
}

void turn_left()
{
    //Set wheel directions to move forward
  digitalWrite(dirLPin,0);
  digitalWrite(dirRPin,1);
  //Turn left
  analogWrite(driveLPin,20);
  analogWrite(driveRPin,120);
  delay(25);
}

void turn_right()
{
    //Set wheel directions to move forward
  digitalWrite(dirLPin,0);
  digitalWrite(dirRPin,1);
  //Turn left
  analogWrite(driveLPin,120);
  analogWrite(driveRPin,20);
  delay(25);
}

void arm_stow(){
  //Stow position
joint1servo.write(140);
delay(1000);
joint2servo.write(80);
//gripperservo.write(50);
}

void arm_deploy(){
// straight out
joint1servo.write(18);
delay(1000);
joint2servo.write(75);
}

//////////////////////////////////////////////////////////////////////////////////////////

void arm_up()
{
  // Increase the angle of the servo to move the gripper up
  if (current_angleJ1<J1SERVO_MAX)
    {
      current_angleJ1+= 5;
      joint1servo.write(current_angleJ1);
    }
  else
    Serial.println("Max position reached");
  delay(20);
}

void arm_down()
{
  // Decrease the angle of the servo to move the gripper down
  if (current_angleJ1>J1SERVO_MIN)
    {
      current_angleJ1-= 5;
      joint1servo.write(current_angleJ1);
    }
  else
    Serial.println("Min position reached");
  delay(20);
}


void arm_right()
{
  // Increase the angle of the servo to move the gripper right
  if (current_angleJ2<J2SERVO_MAX)
    {
      current_angleJ2+= 5;
      joint2servo.write(current_angleJ2);
    }
  else
    Serial.println("Max position reached");
  delay(20);
}

void arm_left()
{
  // Decrease the angle of the servo to move the gripper left
  if (current_angleJ2>J2SERVO_MIN)
    {
      current_angleJ2-= 5;
      joint2servo.write(current_angleJ2);
    }
  else
    Serial.println("Max position reached");
  delay(20);
}

void gripper_close()
{
  // Close configuration angle
  gripperservo.write(85);
  delay(20);
}

void gripper_open()
{
  // Open Configuration angle
  gripperservo.write(15);
  delay(20);
}

// IMU Error Function
void calculate_IMU_error() {
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values 200 times
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccY = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    // Sum all readings
    AccErrorX = AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
    AccErrorY = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
    c++;
  }
  //Divide the sum by 200 to get the error value
  AccErrorX = AccErrorX / 200;
  AccErrorY = AccErrorY / 200;
  c = 0;
  // Read gyro values 200 times
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    GyroX = Wire.read() << 8 | Wire.read();
    GyroY = Wire.read() << 8 | Wire.read();
    GyroZ = Wire.read() << 8 | Wire.read();
    // Sum all readings
    GyroErrorX = GyroErrorX + (GyroX / 131.0);
    GyroErrorY = GyroErrorY + (GyroY / 131.0);
    GyroErrorZ = GyroErrorZ + (GyroZ / 131.0);
    c++;
  }
  //Divide the sum by 200 to get the error value
  GyroErrorX = GyroErrorX / 200;
  GyroErrorY = GyroErrorY / 200;
  GyroErrorZ = GyroErrorZ / 200;
  // Print the error values on the Serial Monitor
  Serial.print("AccErrorX: ");
  Serial.println(AccErrorX);
  Serial.print("AccErrorY: ");
  Serial.println(AccErrorY);
  Serial.print("GyroErrorX: ");
  Serial.println(GyroErrorX);
  Serial.print("GyroErrorY: ");
  Serial.println(GyroErrorY);
  Serial.print("GyroErrorZ: ");
  Serial.println(GyroErrorZ);
}



/////////////////////////////////////////////////////////////////////////////////////////
// Setup 
////////////////////////////////////////////////////////////////////////////////////////

void setup() {
// Serial Setup
Serial.begin(9600); 
Serial.println("Use AWSD keys to drive, IJKL keys to command arm:");

// Attach servos
joint1servo.attach(9);
joint2servo.attach(6);
gripperservo.attach(3);

// Set pinmodes
pinMode(driveLPin, OUTPUT);
pinMode(driveRPin, OUTPUT);

//IMU Setup
Wire.begin();                      // Initialize comunication
Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
Wire.write(0x6B);                  // Talk to the register 6B
Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
Wire.endTransmission(true);        //end the transmission
calculate_IMU_error();

}

void loop() {
// Check for serial input. Call function based on input string. 

if(Serial.available()>0){
  keyboard_input = Serial.read();

  switch(keyboard_input)
{
  case 'w':
    Serial.println("drive forward");
    drive_forward();
    break;
  case 's':
    Serial.println("drive backward");
    drive_backward();
    break;
  case 'a':  
    Serial.println("left");
    turn_left();
    break;
  case 'd':
    Serial.println("right");
    turn_right();
    break;
  case 'n':
    Serial.println("stow position");
    arm_stow();
    break;
  case 'm':
    Serial.println("straight out");
    arm_deploy();
    break;
  case 'j':
    Serial.println("arm left");
    arm_left();
    break;
  case 'k':
    Serial.println("arm down");
    arm_down();
    break;
  case 'l':
    Serial.println("arm right");
    arm_right();
    break;
  case 'i':
    Serial.println("arm up");
    arm_up();
    break;
  case 'o':
    Serial.println("gripper open");
    gripper_open();
    break;
  case 'c':
    Serial.println("gripper close");
    gripper_close();
    break;

}
  }
  // Bring the drive pins back to low at the end
  digitalWrite(driveLPin,LOW);
  digitalWrite(driveRPin,LOW);

  // PING Sensor Reading
  float rawTime;
  float cmDist; //declare variables
  pinMode(SigPin, OUTPUT);
  digitalWrite(SigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(SigPin, LOW);
  /* Now same Sign pin is to be used to monitor if the return echo has been received. Essentially, 
  Sig pin remains HIGH until a return echo is received and at that time it goes LOW. So measure
  the time duration for HIGH at the Sig pin */
  pinMode(SigPin, INPUT);
  rawTime = pulseIn(SigPin, HIGH); //measured in u-seconds
  cmDist = rawTime/ping_invcmCosnt;

  // IMU Sensor Reading
    // === Read acceleromter data === //
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
  // Calculating Roll and Pitch from the accelerometer data
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)
  // === Read gyroscope data === //
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  // Correct the outputs with the calculated error values
  GyroX = GyroX + 0.56; // GyroErrorX ~(-0.56)
  GyroY = GyroY - 2; // GyroErrorY ~(2)
  GyroZ = GyroZ + 0.79; // GyroErrorZ ~ (-0.8)
  // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
  gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
  gyroAngleY = gyroAngleY + GyroY * elapsedTime;
  yaw =  yaw + GyroZ * elapsedTime;
  // Complementary filter - combine acceleromter and gyro angle values
  roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
  
  // Print the values on the serial monitor
  Serial.print(roll);
  Serial.print("/");
  Serial.print(pitch);
  Serial.print("/");
  Serial.print(yaw);
  Serial.print("/");
  Serial.println(cmDist);

  
}
