#include <DHT.h>
#include <TFT_eSPI.h>

#define DHTPIN 17
#define DHTTYPE DHT22

#define BUTTON_PIN 26
int button_state;       // the current state of button
int last_button_state;  // the previous state of button
bool showTemp = true;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
DHT dht(DHTPIN, DHTTYPE);

// Setup for dial
int centerX = 135/2;
int centerY = 240/2;
int r = 60;

// Variables for data
float temp = 0.0;
float rh = 0.0;

// Millis timer delay
int waitPeriod = 5000;
unsigned long start = 0;

int ball = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  tft.begin();
  tft.fillScreen(TFT_BLACK);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  button_state = digitalRead(BUTTON_PIN);
}

void loop(void) {
  if(millis() - start >= waitPeriod){
    temp = dht.readTemperature(true);
    rh = dht.readHumidity();
    start = millis();
  } // END millis timer

  // GET THE BUTTON STATE
  last_button_state = button_state;
  button_state = digitalRead(BUTTON_PIN);
  
  // IF IT CHANGED THEN DO SOMETHING
  if (last_button_state == HIGH && button_state == LOW) {
    showTemp = !showTemp;
    //toggleSwitch(104, 215, showVolts);
  } // END IF
  
  drawDial(temp, rh);
}

void drawDial(float temp, float rh){
  spr.createSprite(135, 240);
  spr.fillSprite(TFT_BLACK);
  // Draw the tick marks and numbers
  for (float ddeg = -180.0; ddeg < 360.0; ddeg += 15.0) {
    float drad = ddeg * 2.0 * 3.142 / 360.0;
    float x1 = centerX + r * cos(drad);
    float y1 = centerY + r * sin(drad);
    float x2 = centerX + (r-5) * cos(drad);
    float y2 = centerY + (r-5) * sin(drad);
    spr.drawLine(x1, y1, x2, y2, TFT_WHITE);
    spr.setTextColor(TFT_WHITE);
    switch(int(ddeg)){
      case -180:
        spr.drawString("0", x2+7, y2, 2);
        break;
      case -135:
        spr.drawString("45", x2+6, y2+6, 2);
        break;
      case -90:
        spr.drawString("90", x2, y2+7, 2);
        break;
      case -45:
        spr.drawString("135", x2-14, y2+6, 2);
        break;
      case 0:
        spr.drawString("180", x2-16, y2, 2);
        break;
      default:
        break;
    } // END Switch
  } // END loop for tick marks

  // Draw two rings for outer circles
  spr.drawCircle(centerX,centerY,r,TFT_WHITE);
  spr.drawCircle(centerX,centerY,r+1,TFT_WHITE);

  // Draw the temp needle
  float ddeg = temp -180.0;
  float drad = ddeg * 2.0 * 3.142 / 360.0;
  float x3 = centerX + (r-10) * cos(drad);
  float y3 = centerY + (r-10) * sin(drad);
  spr.drawLine(centerX, centerY, x3, y3, TFT_RED);

  // Draw the temp needle
  ddeg = rh -180.0;
  drad = ddeg * 2.0 * 3.142 / 360.0;
  x3 = centerX + (r-10) * cos(drad);
  y3 = centerY + (r-10) * sin(drad);
  spr.drawLine(centerX, centerY, x3, y3, TFT_BLUE);
  
  
  // Draw dot in the middle
  spr.fillCircle(centerX,centerY,2,TFT_WHITE);

  // Write the temp centered in the screen
  spr.setTextDatum(MC_DATUM);
  if(showTemp){
    spr.setTextColor(TFT_RED);
    spr.drawNumber(int(temp), centerX, centerY + 90, 4);
  }else{
    spr.setTextColor(TFT_BLUE);
    spr.drawNumber(int(rh), centerX, centerY + 90, 4);
  }

  //move the ball
  ddeg = ball;
  drad = ddeg * 2.0 * 3.142 / 360.0;
  float x5 = centerX + (r-10) * cos(drad);
  float y5 = centerY + (r-10) * sin(drad);
  spr.fillCircle(x5, y5, 2, TFT_BLUE);
  
  // Now push the sprite to the TFT at position 0,0 on screen
  spr.pushSprite(0,-40);
  
  spr.deleteSprite();
  ball ++;
}
