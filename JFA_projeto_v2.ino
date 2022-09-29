//ler sensores
 #include "EmonLib.h" //INCLUSÃO DE BIBLIOTECA

#define VOLT_CAL 127.0 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO)

 EnergyMonitor emon1;
//portas entradas
#define pinBotao 33
//seletora
#define fonte40S 25
#define fonte60S 27
#define fonte70S 29
#define fonte120S 41
#define fonte150S  44
#define fonte200S 46
//leds
#define ledBotao 22
#define ledSeletora 26
#define ledTeste 28
#define ledSensor 23
#define ledOk 30
#define ledDefeito 32
#define ledCurto 24
//portas entradas sensores
#define sensor A0 
#define sensorSaida A1 
#define sensorCorrenteSaida A2
//disjuntores
#define rele1 50
#define rele2 52
#define rele3 50
#define rele4 48
#define rele5 46
#define rele6 44
#define rele7 42
#define rele8 30
#define rele9 38
#define rele10 36
#define rele11 34
#define rele12 32
#define rele13 20
//reles
#define releRede 45
//varaiveis de tempo
unsigned long timeTeste;
unsigned long tempo;
unsigned long delayPiscaCurto;
unsigned long delayPiscaCurtos;
//funcoes 
void fonte40();
void ligaRede();
void teste_curto();
void fonte60();
void fonte70();
void fonte120();
void fonte150();
void fonte200();
void desliga_fontes();
void controla_led_sensor();
//variavel de cont
int x = 0;
int y = 0;
void setup() {
  Serial.begin(9600);//inicia a porta serial na 9600
  //define leds
  pinMode(ledBotao,OUTPUT);
  pinMode(ledSeletora, OUTPUT);
  pinMode(ledOk, OUTPUT);
  pinMode(ledDefeito, OUTPUT);
  pinMode(ledSensor,OUTPUT);
  pinMode(ledTeste,OUTPUT);
  pinMode(ledCurto,OUTPUT);
  //define entradas
  pinMode(pinBotao, INPUT_PULLUP);
  //Seletora
  pinMode(fonte40S, INPUT_PULLUP);
  pinMode(fonte60S, INPUT_PULLUP);
  pinMode(fonte70S, INPUT_PULLUP);
  pinMode(fonte120S, INPUT_PULLUP);
  pinMode(fonte150S, INPUT_PULLUP);
  pinMode(fonte200S, INPUT_PULLUP);
  //define sensores
  pinMode(sensorSaida, INPUT);
  pinMode(sensorCorrenteSaida, INPUT);
  //disjuntores
  //rele rede
  pinMode(releRede, OUTPUT);
  //fontes 40
  pinMode(rele1,OUTPUT);
  pinMode(rele2,OUTPUT);
  pinMode(rele3,OUTPUT);
  pinMode(rele4,OUTPUT);
  pinMode(rele5,OUTPUT);
  pinMode(rele6,OUTPUT);
  pinMode(rele7,OUTPUT);
  pinMode(rele8,OUTPUT);
  pinMode(rele9,OUTPUT);
  pinMode(rele10,OUTPUT);
  pinMode(rele11,OUTPUT);
  pinMode(rele12,OUTPUT);
  pinMode(rele13,OUTPUT);
  //sensores
  emon1.voltage(2, VOLT_CAL, 1.7);
  acendeTodosLeds();
  delay(1000);
  desligaTodosLeds();
}

void loop() {
if(!digitalRead(pinBotao) && x == 0){
    Serial.print("clicou");
    Serial.print(" - ");
    delay(400);
    x = 1;
    digitalWrite(ledBotao, HIGH);
    digitalWrite(ledOk, LOW);
    digitalWrite(ledDefeito, LOW);
    delayPiscaCurtos = millis();
    delayPiscaCurto = delayPiscaCurtos;
}
if(x == 0){
  delayPiscaCurtos = millis();
  delayPiscaCurto = delayPiscaCurtos;
}
  if(x == 1){
    Serial.print("teste de curto");
    Serial.print(" - ");
  delayPiscaCurtos = millis();
    controla_led_curto();
      Serial.println(delayPiscaCurto);
      Serial.print(" - ");
    //digitalWrite(releCurto, HIGH);
  }else{
    delayPiscaCurto = delayPiscaCurtos; 
  }
    if((delayPiscaCurtos - delayPiscaCurto) > 3000){
      digitalWrite(ledCurto, HIGH);
      //digitalWrite(releCurto, LOW);
      delayPiscaCurto = delayPiscaCurtos;
      x = 2;
    }

    if(x == 2){
    Serial.print("Ligou Rede ");
    Serial.print(" - ");
    digitalWrite(releRede, HIGH);
    x = 3;
  }
    if(!digitalRead(fonte40S) && x == 3){
      fonte40();
      Serial.print("Escolheu fonte 40");
      Serial.print(" - ");
      tempo = timeTeste;
      x = 5;
      y = 1;
            timeTeste = millis();
      tempo = timeTeste;
      digitalWrite(ledSeletora, HIGH);
  }
      
  if(!digitalRead(fonte60S) && x == 3){
      fonte60();
      Serial.print("Escolheu fonte 60");
      Serial.print(" - ");
      x = 5;
      y = 2;
            timeTeste = millis();
      tempo = timeTeste;
      digitalWrite(ledSeletora, HIGH);
  }
      
  if(!digitalRead(fonte70S) && x == 3){
      fonte70();
      Serial.print("Escolheu fonte 70");
      Serial.print(" - ");
      x = 5;
      y = 3;
            timeTeste = millis();
      tempo = timeTeste;
      digitalWrite(ledSeletora, HIGH);
  }
      
  if(!digitalRead(fonte120S) && x == 4){
      fonte120();
      Serial.print("Escolheu fonte 120");
      Serial.print(" - ");
      x = 5;
      y = 4;
            timeTeste = millis();
      tempo = timeTeste;
      digitalWrite(ledSeletora, HIGH);
  }
      
      
  if(!digitalRead(fonte150S) && x == 4){
      fonte150();
      Serial.print("Escolheu fonte 150");
      Serial.print(" - ");
      x = 5;
      y = 5;
            timeTeste = millis();
      tempo = timeTeste;
      digitalWrite(ledSeletora, HIGH);
  }   
  if(!digitalRead(fonte200S) && x == 4){
      fonte200();
      Serial.print("Escolheu fonte 200");
      Serial.print(" - ");
      x = 5;
      y = 6;
            timeTeste = millis();
      tempo = timeTeste;
      digitalWrite(ledSeletora, HIGH);
  }
   emon1.calcVI(17,10);
  float supplyVoltage   = emon1.Vrms;
  if(y == 1){ 
  if(x == 5 && supplyVoltage > 10 ){
  }else{
    if(x == 5){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
    }
  }
    if(y == 2){
     
  if(x == 5 && supplyVoltage > 10){
     
  }else{
    if(x == 5){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
  }
  }
    if(y == 3){
  if(x == 5 && supplyVoltage > 10 ){
     
  }else{
    if(x == 5){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
    }
  }
    if(y == 4){
  if(x == 5 && supplyVoltage > 10 ){
     
  }else{
    if(x == 5){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
    }
  }
    if(y == 5){
  if (x == 5 && supplyVoltage > 10 ){
     
  }else{
    if(x == 5){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
    }
  }  
    if(y == 6){
  if(x == 5 && supplyVoltage > 10 ){
     
  }else{
    if(x == 5){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
    }
  }
  if(supplyVoltage > 10 ){
    digitalWrite(ledSensor, HIGH);
  }else{
    controla_led_sensor();
      if(x == 1){
    tempo = timeTeste;
        x = 0;
    }
  }

  if( supplyVoltage > 10 ){
    }else{
      if(x == 5){
     tempo = timeTeste;
     digitalWrite(ledDefeito, HIGH);
     desligaLed(); 
     x = 0;
     desligaLed();
    }
    }
    if(x == 4){
      timeTeste = millis();
      tempo = timeTeste;
    }
     if(x == 5){
    timeTeste = millis();
    Serial.println(timeTeste - tempo );
    if(timeTeste - tempo > 14000){//3:30 minutos
   tempo = timeTeste;
   digitalWrite(ledDefeito, LOW);
   digitalWrite(ledTeste, LOW);
   digitalWrite(ledSeletora, LOW);
   digitalWrite(ledCurto, LOW);
   desliga_fontes();
    x = 0;
    if(x == 0){
      digitalWrite(ledOk, HIGH);
    }
  }
    
  }
  controla_led();
  controla_led_teste();
}

void fonte40(){
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);
  digitalWrite(rele4, HIGH);
}
void fonte60(){
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);
  digitalWrite(rele4, HIGH);
}
void fonte70(){
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);
  digitalWrite(rele4, HIGH);
}void fonte120(){
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);
  digitalWrite(rele4, HIGH);
}  
void fonte150(){
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);
  digitalWrite(rele4, HIGH);;
}
void fonte200(){
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);
  digitalWrite(rele4, HIGH);
}

void desliga_fontes(){
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, LOW);
  digitalWrite(rele4, LOW);
  digitalWrite(rele5, LOW);
  digitalWrite(rele6, LOW);
  digitalWrite(rele7, LOW);
  digitalWrite(rele8, LOW);
  digitalWrite(rele9, LOW);
  digitalWrite(rele10, LOW);
  digitalWrite(rele11, LOW);
  digitalWrite(rele12, LOW);
  digitalWrite(rele13, LOW);
}
void controla_led(){

  static unsigned long delayPisca;  
  if(x == 0){
   if ( (millis() - delayPisca) < 300 ) {
      digitalWrite(ledBotao, HIGH);
  } else {
      digitalWrite(ledBotao, LOW);
  }

  if ( (millis() - delayPisca) >= 600 ) {
    delayPisca = millis(); 
  }
  }
}
void controla_led_teste(){
  static unsigned long delayPisca;  
  if(x == 5){
   if ( (millis() - delayPisca) < 300 ) {
      digitalWrite(ledTeste, HIGH);
  } else {
      digitalWrite(ledTeste, LOW);
  }

  if ( (millis() - delayPisca) >= 600 ) {
    delayPisca = millis(); 
  }
  }
}
void controla_led_sensor(){
      static unsigned long delayPisca;  
   if ( (millis() - delayPisca) < 300 ) {
      digitalWrite(ledSensor, HIGH);
  } else {
      digitalWrite(ledSensor, LOW);
  }

  if ( (millis() - delayPisca) >= 600 ) {
    delayPisca = millis(); 
  }
}
void controla_led_curto(){
        static unsigned long delayPisca;  
   if ( (millis() - delayPisca) < 300 ) {
      digitalWrite(ledCurto, HIGH);
  } else {
      digitalWrite(ledCurto, LOW);
  }

  if ( (millis() - delayPisca) >= 600 ) {
    delayPisca = millis(); 
  }
}
void controla_led_seletora(){
          static unsigned long delayPisca;  
   if ( (millis() - delayPisca) < 300 ) {
      digitalWrite(ledSeletora, HIGH);
  } else {
      digitalWrite(ledSeletora, LOW);
  }

  if ( (millis() - delayPisca) >= 600 ) {
    delayPisca = millis(); 
  }
}
void acende_led_OK(){
  digitalWrite(ledOk, HIGH);
}
void desligaTodosLeds(){
  digitalWrite(ledSeletora, LOW);
  digitalWrite(ledTeste,LOW);
  digitalWrite(ledCurto, LOW);
  digitalWrite(ledSensor, LOW);
  digitalWrite(ledDefeito, LOW);
  digitalWrite(ledOk, LOW);
}
void desligaLed(){
  digitalWrite(ledSeletora, LOW);
  digitalWrite(ledTeste,LOW);
  digitalWrite(ledCurto, LOW);
  
}
void acendeTodosLeds(){
  digitalWrite(ledSeletora, HIGH);
  digitalWrite(ledTeste,HIGH);
  digitalWrite(ledCurto, HIGH);
  digitalWrite(ledSensor, HIGH);
  digitalWrite(ledDefeito, HIGH);
  digitalWrite(ledOk, HIGH);
}
