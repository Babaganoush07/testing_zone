#define potPIN 15
#define GREEN 23
#define YELLOW 22
#define RED 21

int potValue;
float voltage;

void setup() {
  for(int i = 21; i <= 23; i++){
    pinMode(i, OUTPUT);
  } // END for pinMode
} // END setup()

void loop() {
  potValue = analogRead(potPIN);
  voltage = (5. / 4095.) * potValue;

  if(voltage <= 0.0){
    for(int i = 21; i <= 23; i++){
      digitalWrite(i, LOW);
    } // END for ALL OFF
  }else if(voltage > 0.0 && voltage <=3.0){
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
  }else if(voltage > 3.0 && voltage <=4.0){
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(RED, LOW);
  }else if(voltage > 4.0 && voltage <= 4.9){
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, HIGH);
  }else if(voltage >= 5.0){
    digitalWrite(RED, LOW);
    delay(200);
    digitalWrite(RED, HIGH);
    delay(200);
  } // END if else voltage ranges
} // END loop()
