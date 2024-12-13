#include <Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Servo xServo;
Servo yServo;
Servo zServo;
Adafruit_MPU6050 mpu;

const int xServoPin = 1;
const int yServoPin = 2;
const int zServoPin = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xServo.attach(xServoPin);
  yServo.attach(yServoPin);
  zServo.attach(zServoPin);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  
}
