#include "u8glib.h"
#include <arduino.h>
#include "oledWriteLib.h"

int sensorPin = A0;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

const int beansArrayLength = 128;
int beansArray[beansArrayLength];

void setupFunction()
{
  u8g.setFont(u8g_font_6x10);
  pinMode(sensorPin, INPUT);
}

void oledGraph(int meanData) {
  beansArray[beansArrayLength - 1] = meanData;
  int max = 0;
  int min = 1023;
  for (int i = 1; i < beansArrayLength; i++) {
    beansArray[i - 1] = beansArray[i];
  }
  beansArray[beansArrayLength - 1] = meanData;
  for (int i = 0; i < beansArrayLength; i++) {
    if (beansArray[i] < min) {
      min = beansArray[i];
    }
    if (beansArray[i] > max) {
      max = beansArray[i];
    }
  }
  u8g.firstPage();
  do {
    for (int i = 1; i < beansArrayLength; i++){
      u8g.drawLine(i - 1, map(beansArray[i - 1], min, max, 0, 63), i, map(beansArray[i], min, max, 0, 63));
    }
  } while (u8g.nextPage());
}
