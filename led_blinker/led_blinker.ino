const int ledarrayLength = 4;
int ledArray[ledarrayLength] = {4, 5, 6, 7};
const int randomArrayLength = 40;
int randomArray[randomArrayLength] = {23, 176, 302, 45, 498, 150, 289, 76, 231, 411, 32, 149, 199, 87, 320, 4, 467, 215, 12, 380, 98, 410, 295, 153, 64, 342, 420, 238, 59, 17, 306, 471, 270, 83, 134, 204, 456, 68, 310, 255};
int randomPicker = 0;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < ledarrayLength; i++) {
    pinMode(ledArray[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < ledarrayLength; i++) {
    digitalWrite(ledArray[i], HIGH);
    delay(randomArray[randomPicker]);

    randomPicker++;
    if (randomPicker > randomArrayLength - 1) {
      randomPicker = 0;
    }

    digitalWrite(ledArray[i], LOW);
    delay(randomArray[randomPicker]);

    randomPicker++;
    if (randomPicker > randomArrayLength - 1) {
      randomPicker = 0;
    }
  }
}