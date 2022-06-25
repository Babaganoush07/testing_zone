#define LED_PIN 23
const int channel = 0;
const int frequency = 1000;
const int resolution = 8;

int brightness[5] = {10,30,60,120,220};
byte b = 0;

int wait = 500;

void setup() {
  ledcSetup(channel,frequency,resolution);
  ledcAttachPin(LED_PIN,channel);
} // END setup()

void loop() {
  ledcWrite(channel, brightness[b]);
  
  delay(wait);

  b++;
  if(b > 4){b=0; }

} // END loop()
