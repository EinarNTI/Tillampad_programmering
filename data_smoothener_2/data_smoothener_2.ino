#include "readMeanLib.h"
#include "oledWriteLib.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupFunction();
}

void loop() {
  // put your main code here, to run repeatedly:
  oledGraph(readMean());
}