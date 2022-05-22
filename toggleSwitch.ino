#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

#define BUTTON_PIN 26
int button_state;       // the current state of button
int last_button_state;  // the previous state of button
bool toggleState = false;

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

  // SETUP THE DISPLAY
  tft.init();
  tft.fillScreen(TFT_BLACK);

   // DRAW THE FIRST DISPLAY STUFF
  toggleSwitch(104, 215, toggleState);
} // END SETUP

void loop() {
  // GET THE BUTTON STATE
  last_button_state = button_state;
  button_state = digitalRead(BUTTON_PIN);

  // IF IT CHANGED THEN DO SOMETHING
  if (last_button_state == HIGH && button_state == LOW) {
    Serial.println("The button is pressed");
    toggleState = !toggleState;
    toggleSwitch(104, 215, toggleState);
  } // END IF
} // END LOOP
