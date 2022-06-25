int pin1=19;
int pin2=21;
int pin3=22;
int pin4=23;
int timr=1000;
int i=0;

void setup() {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
} // END setup()

void loop() {
  i++;
  
  if((i % 2) > 0) { digitalWrite(pin1, HIGH); } else { digitalWrite(pin1, LOW); }
  if((i % 4) > 1) { digitalWrite(pin2, HIGH); } else { digitalWrite(pin2, LOW); }
  if((i % 8) > 3) { digitalWrite(pin3, HIGH); } else { digitalWrite(pin3, LOW); }
  if((i % 16) > 7) { digitalWrite(pin4, HIGH); } else { digitalWrite(pin4, LOW); }
  
  delay(timr);
} // END loop()
