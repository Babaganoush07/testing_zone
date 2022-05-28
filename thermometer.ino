/*
Using a TTGO T-Display
a DHT22
Used the sprite class to reduce the flashing caused by updating graphics
*/

#include <DHT.h>
#include <TFT_eSPI.h>

///////////////////////// SET VARIABLES /////////////////////////

// SET THE PIN FOR THE DHT22
#define DHTPIN 17
#define DHTTYPE DHT22

int temp;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  tft.begin();
  tft.fillScreen(TFT_BLACK); 
}

void loop() {
  // GET TEMP
  temp = dht.readTemperature(true);
  drawThermometer(temp);
  delay(10000);
}

void drawThermometer(int temp){
  spr.createSprite(135, 240);
  spr.fillSprite(TFT_BLACK);
  // BUILD THE BASE OF THE THERMOMETER
  spr.fillCircle(135/2, 180, 22, TFT_WHITE);
  spr.fillRoundRect(54, 2, 26, 170, 7, TFT_WHITE);
  spr.fillCircle(135/2, 180, 20, TFT_RED);
  
  // ADD LINES TO THERMOMETER
  int lineY = 5;
  int t = 110;
  spr.setTextDatum(TL_DATUM);
  for(int i=0; i<12; i++){
    spr.drawLine(75, lineY, 83, lineY, TFT_WHITE);
    spr.drawString(String(t), 85, lineY-3, 1);
    t = t-10;
    lineY = lineY+14;
  } // END FOR LOOP FOR LINES

  // DRAW TEXT BELOW THERMOMETER
  spr.setTextDatum(TC_DATUM);
  spr.drawString(String(temp), 135/2, 208, 4);

  // ADJUST SIZE OF BAR IF IT WILL GO OFF SCREEN
  if(temp > 110) temp = 110;
  if(temp < 0) temp = 0;

  // DRAW THE FILLED THERMOMETER
  spr.fillRoundRect(56, temp/-0.71428571428571428571428571428571 + 160, 22, 170-(temp/-0.71428571428571428571428571428571 + 160), 7, TFT_RED);

  //DRAW THE SPRITE TO THE SCREEN, THEN DELETE IT TO SAVE MEMORY
  spr.pushSprite(0,0);
  spr.deleteSprite();
} // END drawThermometer()
