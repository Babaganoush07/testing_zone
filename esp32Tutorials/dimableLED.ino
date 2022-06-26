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
}

void loop() {
  potValue = analogRead(potPIN);
  brightness = (255. / 4095.) * potValue;

  ledcWrite(channel, brightness);
}
