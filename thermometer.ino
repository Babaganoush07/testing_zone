#include <DHT.h>
#include <TFT_eSPI.h>

///////////////////////// SET VARIABLES /////////////////////////

// SET THE PIN FOR THE DHT22
#define DHTPIN 17
#define DHTTYPE DHT22

int temp;


TFT_eSPI tft = TFT_eSPI();
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  dht.begin();

  // BUILD THERMOMETER
  tft.fillCircle(135/2, 180, 22, TFT_WHITE);
  tft.fillRoundRect(54, 2, 26, 170, 7, TFT_WHITE);
  tft.fillCircle(135/2, 180, 20, TFT_RED);
  int lineY = 5;
  int t = 110;
  //tft.setTextSize(1);
  for(int i=0; i<12; i++){
    tft.drawLine(75, lineY, 83, lineY, TFT_WHITE);
    tft.drawString(String(t), 85, lineY-3, 1);
    //tft.setCursor(85, lineY-3);
    //tft.print(String(t));
    t = t-10;
    lineY = lineY+14;
  }

  temp = dht.readTemperature(true);

  // DRAW TEXT
  tft.setTextDatum(TC_DATUM);
  tft.drawString(String(temp), 135/2, 208, 4);
  //tft.setTextSize(4);
  //tft.setCursor(28, 208);
  //tft.print(String(temp));

  // ADJUST SIZE OF BAR IF IT WILL GO OFF SCREEN
  if(temp > 110) temp = 110;
  if(temp < 0) temp = 0;
  
  tft.fillRoundRect(56, temp/-0.71428571428571428571428571428571 + 160, 22, 170-(temp/-0.71428571428571428571428571428571 + 160), 7, TFT_RED);
  
}

void loop() {
  
  // BLANK OUT OLD BAR
  tft.fillRoundRect(56, temp/-0.71428571428571428571428571428571 + 160, 22, 170-(temp/-0.71428571428571428571428571428571 + 160), 7, TFT_WHITE);
  tft.fillCircle(135/2, 180, 20, TFT_RED);
 
  // BLANK OLD TEXT
  tft.fillRect(27, 207, 90, 30, TFT_BLACK);
  
  // GET TEMP
  temp = dht.readTemperature(true);
  
  // DRAW NEW TEXT
  tft.setTextDatum(TC_DATUM);
  tft.drawString(String(temp), 135/2, 208, 4);
  //tft.setTextSize(4);
  //tft.setCursor(28, 208);
  //tft.print(String(temp));

  // ADJUST SIZE OF BAR IF IT WILL GO OFF SCREEN
  if(temp > 110) temp = 110;
  if(temp < 0) temp = 0;

  // DRAW NEW BAR
  tft.fillRoundRect(56, temp/-0.71428571428571428571428571428571 + 160, 22, 170-(temp/-0.71428571428571428571428571428571 + 160), 7, TFT_RED);

  delay(10000);
}
