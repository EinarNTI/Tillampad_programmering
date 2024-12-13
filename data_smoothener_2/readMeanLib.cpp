#include <arduino.h>
#include "readMeanLib.h"

const int lightArrayLength = 10;
const int meansArrayLength = 128;

int lightArray[lightArrayLength];
int meansArray[meansArrayLength];
int lightArrayPos = 0;
int sum;
int read;
int screenXPos = 1;

int activePin = A0;

int readMean() {

  sum = 0;
  read = analogRead(activePin);
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