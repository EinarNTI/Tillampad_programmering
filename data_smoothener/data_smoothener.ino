const int sensorPin = A0;

const int arrayLength = 10;
int array[arrayLength];
int arrayPos = 0;
int sum;
int read;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  read = analogRead(sensorPin);
  array[arrayPos] = read;

  arrayPos++;
  if (arrayPos > arrayLength - 1) {
    arrayPos = 0;
  }

  for (int i = 0; i < arrayLength; i++) {
    sum = sum + array[i];
  }

  sum = sum / arrayLength;

  Serial.print(sum);
  Serial.print(", ");
  Serial.println(read);

  sum = 0;

  delay(100);
}
