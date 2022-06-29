#define potPIN 15

#define LED_PIN 23
const int channel = 0;
const int frequency = 1000;
const int resolution = 8;

int potValue;
int brightness;

void setup() {
  ledcSetup(channel,frequency,resolution);
  ledcAttachPin(LED_PIN,channel);
} // END setup()

void loop() {
  potValue = analogRead(potPIN);
  //brightness = potValue / 16;                 // What I came up with, 4095 / 255 = 16
  //brightness = (255. / 4095.) * potValue;     // The Paul McWhorter way
  brightness = map(potValue, 0, 4095, 0, 255);  // Using the map function
  ledcWrite(channel, brightness);
} // END loop()
