unsigned long delayLed;
unsigned long timeLed;
byte estado = 1;
void setup(){
	pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop(){
  delayLed = millis();
  if((delayLed - timeLed) > 1000){
    digitalWrite(13, estado);
  }
    if((delayLed - timeLed) > 2000){
    digitalWrite(12, estado);
  }
    if((delayLed - timeLed) > 3000){
    digitalWrite(11, estado);
  }
  if((delayLed - timeLed) > 4000){
	estado = 0;
        delayLed = millis();
  if((delayLed - timeLed) > 5000){
    digitalWrite(13, estado);
  }
    if((delayLed - timeLed) > 6000){
    digitalWrite(12, estado);
  }
    if((delayLed - timeLed) > 7000){
    digitalWrite(11, estado);
  }
    timeLed = delayLed;
  }
  
}
