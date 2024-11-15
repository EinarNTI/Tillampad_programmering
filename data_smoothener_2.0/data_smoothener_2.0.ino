#include "U8glib.h"

const int sensorPin = A0;
const int lightArrayLength = 10;
const int meansArrayLength = 128;

int lightArray[lightArrayLength];
int meansArray[meansArrayLength];
int lightArrayPos = 0;
int sum;
int read;
int screenXPos = 1;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  u8g.setFont(u8g_font_unifont);
}

void loop() {
  // put your main code here, to run repeatedly:
  oledGraph(readMean());
}


int readMean() {
  
  sum = 0;

  read = analogRead(sensorPin);
  lightArray[lightArrayPos] = read;

  lightArrayPos++;
  if (lightArrayPos > lightArrayLength - 1) {
    lightArrayPos = 0;
  }

  for (int i = 0; i < lightArrayLength; i++) {
    sum = sum + lightArray[i];
  }

  sum = sum / lightArrayLength;

  Serial.print(sum);
  Serial.print(", ");
  Serial.println(read);
  return sum;
}

void oledGraph(int meanData) {
  int max = 0;
  int min = 1023;

  for (int i = 1; i < meansArrayLength; i++) {
    meansArray[i-1] = meansArray[i];
  }
  meansArray[meansArrayLength - 1] = meanData;

  for (int i = 0; i < meansArrayLength; i++) {
    if (meansArray[i] < min) {
      min = meansArray[i];
    }
    if (meansArray[i] > max) {
      max = meansArray[i];
    }
  }

  u8g.firstPage();  
  do {
    for (int i = 1; i < meansArrayLength; i++) {
      u8g.drawPixel(i, map(meansArray[i-1], min, max, 0, 63));
    }
  } while( u8g.nextPage() );
}