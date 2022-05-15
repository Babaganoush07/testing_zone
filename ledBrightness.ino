/*
Hardware that I used:
TTGO T-Display that has a built in TFT display
Photo Transister through a 10K Ω Resistor
Red LED through a 220Ω Resistor
Tactile Button switch (6mm)
22 awg wire
*/

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

#define LIGHT_SENSOR_PIN 15

#define BUTTON_PIN 26
int button_state;       // the current state of button
int last_button_state;  // the previous state of button
bool showVolts = false;

#define LED_PIN 22
const int channel = 0;
const int frequency = 1000;
const int resolution = 8;

int r = 0;
int g = 0;
int b = 255;

// DRAW A TOGGLE SWITCH
// NEEDS AN X AND A Y AND THE STATE
void toggleSwitch(int x=0, int y=0, bool b=false){
  tft.fillRoundRect(x, y, 25, 15, 7, TFT_LIGHTGREY);
  tft.drawRoundRect(x, y, 25, 15, 7, TFT_WHITE);
  tft.drawString("   ", x-28, y, 2);
  if(b == false){
    tft.fillCircle(x+7, y+7, 6, TFT_RED);
    tft.drawString("OFF", x-28, y, 2);
  }else{
    tft.fillCircle(x+17, y+7, 6, TFT_GREEN);
    tft.drawString(" ON", x-28, y, 2);
  } // END IF ELSE
} // END toggleSwitch()

void setup() {
  Serial.begin(9600);
  // SET PINMODES
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  button_state = digitalRead(BUTTON_PIN);

  ledcSetup(channel,frequency,resolution);
  ledcAttachPin(LED_PIN,channel);

  // SETUP THE DISPLAY
  tft.init();
  tft.fillScreen(TFT_BLACK);

  // DRAW THE FIRST DISPLAY STUFF
  tft.drawString("LIGHT SENSOR", 0, 0, 2);
  tft.drawString("Analog Value", 0, 15, 2);
  tft.drawString("Voltage", 80, 200, 2);
  toggleSwitch(104, 215, showVolts);
}

void loop() {
  // GET THE BUTTON STATE
  last_button_state = button_state;
  button_state = digitalRead(BUTTON_PIN);
  
  // IF IT CHANGED THEN DO SOMETHING
  if (last_button_state == HIGH && button_state == LOW) {
    Serial.println("The button is pressed");
    showVolts = !showVolts;
    toggleSwitch(104, 215, showVolts);
  } // END IF

  // READ THE PHOTO TRANSISTOR AND SET ALL THE VARIABLES BASED ON THE READING
  int analogValue = analogRead(LIGHT_SENSOR_PIN);    // reads the input on analog pin (value between 0 and 4095)
  float lightVoltage = (3.3/4095.0) * analogValue;
  int brightness = (analogValue / -16) + 255;
  ledcWrite(channel, brightness);

  // BLANK OUT AND REWRITE THE ANALOG VALUE
  tft.drawString("      ", 0, 30, 2);
  tft.drawNumber(analogValue, 0, 30, 2);

  // BLANK OUT AND REWRITE THE VOLTS IF showVolts IS TRUE
  if(showVolts == true){
    tft.drawString("Voltage", 0, 45, 2);
    tft.drawString("       ", 0, 60, 2);
    tft.drawFloat(lightVoltage, 1, 0, 60, 2);
  }else{
    tft.drawString("         ", 0, 45, 2);
    tft.drawString("       ", 0, 60, 2);
  } // END IF ELSE

  // DRAW METER BOX, BLANK OUT THE BAR, SET THE COLOR AND REDRAW IT
  tft.drawRect(1, 75, 133, 19, TFT_WHITE);
  tft.fillRect(3, 77, 129, 15, TFT_BLACK);
  r = analogValue / 16;
  g = analogValue / 16;
  tft.fillRect(3, 77, analogValue / 31.7 , 15, tft.color565(r,g,b));  // 129 max

  delay(30);
}
