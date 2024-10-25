/*
* Name: clock and temp project
* Author: Einar Söderberg Beckman
* Date: 2024-10-11
* Description: This project uses a ds3231 to measure time and displays the time to an 1306 oled display,
* Further, it measures temprature with a analog temprature module and displays a mapped value to a 9g-servo-motor and uses a piezo to sound
* an alarm which can be set by pressing two buttons
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include "U8glib.h"
#include <Servo.h>

// Init constants
const int tempPin = A0;
const int servoPin = 2;
const int beepPin = A1;
const int increasePin = 13;
const int decreasePin = 12;

// Init global variables
int alarmHour = 10;
int alarmMinute = 50;

// construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
Servo myservo;

void setup() {
  // init communication
  Serial.begin(9600);
  Wire.begin();

  // Init Hardware
  rtc.begin();
  pinMode(tempPin, INPUT);
  pinMode(beepPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);
  pinMode(increasePin, INPUT);
  pinMode(decreasePin, INPUT);

  //Settings
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  u8g.setFont(u8g_font_unifont);
}

void loop() {
  oledWrite();
  servoWrite();
  alarmAdjust();
  alarm();
}

/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime() {
  DateTime now = rtc.now();
  int hour = now.hour();
  int minute = now.minute();
  int second = now.second();
  String hourString = String(hour);
  String minuteString = String(minute);
  String secondString = String(second);
  if (hour < 10) {
    hourString = "0" + hourString;
  }
  if (minute < 10) {
    minuteString = "0" + minuteString;
  }
  if (second < 10) {
    secondString = "0" + secondString;
  }
  return (hourString + ":" + minuteString + ":" + secondString);
}

/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp in degrees celsius
*Parameters: Void
*Returns: temprature as float
*/
float getTemp() {
  int ThermistorPin = 0;
  int Vo;
  float R1 = 10000;
  float logR2, R2, T;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

  
  Vo = analogRead(tempPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

  return T;
}

/*
* Displays the time, temperature and the time for the set alarm
*Parameters: None
*Returns: void
*/
void oledWrite() {
  String textString = String(getTemp());
  textString = textString + "C";
  String alarmMinuteString = String(alarmMinute);
  String alarmHourString = String(alarmHour);
  String text2String = alarmHourString + ":" + alarmMinuteString;
  u8g.firstPage();  
  do {
    u8g.drawStr(22, 22, getTime().c_str());
    u8g.drawStr(22, 44, textString.c_str());
    u8g.drawStr(88, 55, text2String.c_str());
  } while( u8g.nextPage() );
}

/*
* Uses the getTemp function to get a temprature value and maps it to a corresponding degree on a servo
*Parameters: None
*Returns: void
*/
void servoWrite() {
  myservo.write(map(getTemp(), 10, 30, 0, 180));
}

/*
* Powers an piezo on beepPin when the time reaches the set alarm time for one second
* Parameters: None
* Returns: void
*/
void alarm() {
  DateTime now = rtc.now();
  if ((now.hour() == alarmHour) && (now.minute() == alarmMinute) && (now.second() == 0)){
    analogWrite(beepPin, 300);
  }
  else {
    analogWrite(beepPin, 0);
  }
}

/*
* Adjusts the set alarm when the increase or decrease buttons are pressed, also adjusts the set time when it goes under 0:00 
* or over 23:59
* Parameters: None
* Returns: void
*/
void alarmAdjust() {
  if (digitalRead(decreasePin) == HIGH) {
    alarmMinute = alarmMinute - 5;
    if (alarmMinute <= 0) {
      alarmMinute = 59;
      alarmHour = alarmHour - 1;
    }
  }
  if (digitalRead(increasePin) == HIGH) {
    alarmMinute = alarmMinute + 5;
    if (alarmMinute >= 60) {
      alarmMinute = 0;
      alarmHour = alarmHour + 1;
    }
  }
  if (alarmHour == -1) {
    alarmHour = 23;
  }
  if (alarmHour == 24) {
    alarmHour = 0;
  }
}
