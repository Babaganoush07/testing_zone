/*
Using a TTTGO T-Display
Followed this YouTube video
https://youtu.be/spkWTnRe6KU
*/
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

String numbers[3] = {"","",""};  // First, Second, Result
String functions[2] = {"C", "OK"};

int fase = 0;

int startX = 118;
int startY = 6;

int chosen = 0;

int debounce = 0;
int debounce2 = 0;

void setup() {
  pinMode(0, INPUT_PULLUP); // LEFT BUTTON
  pinMode(35, INPUT_PULLUP); // RIGHT BUTTON
  
  tft.init();
  tft.fillScreen(TFT_BLACK);

  // Add numbers to screen
  for(int i=0; i<10; i++){
    tft.drawString(String(i), startX, startY, 2);
    startY += 19;
  }

  // Add funtione to screen
  for(int i=0; i<2; i++){
    tft.drawString(functions[i], startX, startY, 2);
    startY += 19;
  }
  
  startY = 6;
  tft.drawRect(startX-4, startY-1+(19*chosen),20,18, TFT_BLUE);
  
}

void loop() {
  
  if(digitalRead(35)==0){
    if(debounce==0){
      debounce = 1;
      tft.drawRect(startX-4, startY-1+(19*chosen),20,18, TFT_BLACK);
      chosen += 1;
      if(chosen>11){
        chosen = 0;
      } // END chosen>11 IF
      tft.drawRect(startX-4, startY-1+(19*chosen),20,18, TFT_BLUE);
      delay(400);
    } // END DEBOUNCE IF
  }else debounce = 0; // END digitalRead(35) IF

  if(digitalRead(0)==0){
    if(debounce2==0){
      debounce2 = 1;
      
      if(chosen<10)
      numbers[fase] = numbers[fase] + String(chosen);

      if(chosen == 10){
        numbers[fase]="";
        tft.drawString("      ", 22, 50+(46*fase), 4);
      } // END CHOSEN IF

      if(chosen == 11){
        fase+=1;
        tft.drawLine(4, 130, 100, 130, TFT_BLUE);
        tft.drawString("+", 0, 98, 6);
      } // END CHOSEN IF
      
      if(fase == 2){
        int result = numbers[0].toInt() + numbers[1].toInt();
        numbers[fase] = String(result);
        //tft.drawLine(4, 138, 100, 138, TFT_WHITE);
        //tft.drawString("+", 0, 98, 4);
      } // END FASE IF

      tft.drawString(numbers[fase], 22, 50+(46*fase), 4);
      delay(400);
    } // END DEBOUNCE2
  }else debounce2 = 0; // END digitalRead(35) IF

} // END LOOP()
