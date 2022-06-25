/*
Blink the RED LED 5 times fast
Blink the GREEN LED 10 slow
BLINK the BLUE 15 real slow
No numbers allowed in the loop()
*/

int RED = 23;
int redBlink = 5;
int redSpeed = 500;

int GREEN = 22;
int greenBlink = 10;
int greenSpeed = 1000;

int BLUE = 21;
int blueBlink = 15;
int blueSpeed = 1500;

void blinkLED(int led, int blink, int speed){
  for(int i = blink; i > 0; i--){
    digitalWrite(led, HIGH);
    delay(speed);
    digitalWrite(led, LOW);
    delay(speed);
  } // END for loop
} // END blinkLED()

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
} // END setup()

void loop() {
  blinkLED(RED, redBlink, redSpeed);
  blinkLED(GREEN, greenBlink, greenSpeed);
  blinkLED(BLUE, blueBlink, blueSpeed);
} // END loop()
