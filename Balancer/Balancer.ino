/*
Author: Einar Söderberg Beckman
Date 2025-02-07
A project that uses two servo motors and an accelerometer to create a stabilized plane.
*/

//Imports needed libraries
#include <Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

//Constructs objects
Servo xServo;
Servo yServo;
Servo zServo;
Adafruit_MPU6050 mpu;

//Initiates constant variables
const int xServoPin = 2;
const int yServoPin = 3;
const int zServoPin = 4;
const int xArrayLength = 5;
const int yArrayLength = 5;

//Initiates global variables
float xAngle = 45;
float yAngle = 45;
int xArray[xArrayLength];
int yArray[yArrayLength];
int xArrayPos = 0;
int yArrayPos = 0;
sensors_event_t a, g, temp;


void setup() {
  // Init communications
  Serial.begin(115200);

  //Attach servos to servo pins
  xServo.attach(xServoPin);
  yServo.attach(yServoPin);
  zServo.attach(zServoPin);

  //See that sensor is connected, if not it prints an error and stops the program, otherwise it continues.
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  //Sensor settings
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  mpu.getEvent(&a, &g, &temp); //Collects data from the sensor

  xAngle += averageX(float(g.gyro.y * -58 * 0.0160)); //Converts collected rotation values from radians to degrees in the other direction and adjust the values for multiple readings per second
  yAngle += averageY(float(g.gyro.x * -58 * 0.0160));
  xServo.write(xAngle);
  yServo.write(yAngle);
  delay(1); //The sensor needs a delay to work properly
}


/*
Stores incoming values in the "xArray" global array and extracts a mean worth intended for the x-axis servo.
Parameters: in as float
Returns: float
*/
float averageX(float in) {
  float xSum = 0;
  xArray[xArrayPos] = in;

  xArrayPos++;

  //Resets the position value if it is more than the array length
  if (xArrayPos > xArrayLength - 1) { 
    xArrayPos = 0;
  }

  for (int i = 0; i < xArrayLength; i++) {
    xSum = xSum + xArray[i];
  }

  xSum = xSum / xArrayLength;

  return xSum;
}


/*
Stores incoming values in the "yArray" global array and extracts a mean worth intended for the y-axis servo.
Parameters: in as float
Returns: float
*/
float averageY(float in) {
  float ySum = 0;
  yArray[yArrayPos] = in;

  yArrayPos++;

  //Resets the position value if it is more than the array length
  if (yArrayPos > yArrayLength - 1) {
    yArrayPos = 0;
  }

  for (int i = 0; i < yArrayLength; i++) {
    ySum = ySum + yArray[i];
  }

  ySum = ySum / yArrayLength;

  return ySum;
}