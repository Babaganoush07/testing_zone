#define LED_PIN 23
const int channel = 0;
const int frequency = 1000;
const int resolution = 8;

int brightness = 0;
int fadeAmount = 5;
int wait = 300;

void setup() {
  ledcSetup(channel,frequency,resolution);
  ledcAttachPin(LED_PIN,channel);
} // END setup()

void loop() {
  ledcWrite(channel, brightness);
  
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  } // END if

  delay(wait);

} // END loop()
