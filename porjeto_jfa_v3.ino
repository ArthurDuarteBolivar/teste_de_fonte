
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
#define rele2 51
#define rele3 53
#define rele4 50
#define rele5 52
#define rele6 34
#define rele7 36
#define rele8 38
#define rele9 40
#define rele10 42
#define rele11 44
#define rele12 46
#define rele13 48
//reles
#define releCurto 49
//varaiveis de tempo
unsigned long timeTeste;
unsigned long tempo;
unsigned long delayPiscaCurto;
unsigned long delayPiscaCurtos;
unsigned long delayCurto;
unsigned long timeCurto;
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
//variaveis sensores
float tensaoEntrada = 0.0;
float tensaoMedida = 0.0; 

float valorR1 = 30000.0;
float valorR2 = 7500.0; 
int leituraSensor = 0; 
void setup() {
  Serial.begin(9600);//inicia a porta serial na 9600
  //define leds
  pinMode(ledBotao,OUTPUT);
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
  pinMode(releCurto, OUTPUT);
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
  desliga_fontes();
}

void loop() {
  leituraSensor = analogRead(sensorSaida); 
  tensaoEntrada = (leituraSensor * 5.0) / 1024.0; 
  tensaoMedida = tensaoEntrada / (valorR2/(valorR1+valorR2)); 
if(!digitalRead(pinBotao) && x == 0){
    Serial.print("clicou");
    Serial.print(" - ");
    delay(400);
    x = 1;
    desliga_fontes();
    digitalWrite(ledBotao, HIGH);
    digitalWrite(ledOk, LOW);
    digitalWrite(ledDefeito, LOW);
    delayPiscaCurtos = millis();
    delayPiscaCurto = delayPiscaCurtos;
}

if(x == 0){
  delayPiscaCurtos = millis();
  delayPiscaCurto = delayPiscaCurtos;
  delayCurto = millis();
  timeCurto = delayCurto;
}
if(x == 0){
  digitalWrite(releCurto, HIGH);
}
Serial.println(timeCurto);
if(tensaoMedida < 10 && x == 1){
  digitalWrite(ledCurto, HIGH);
  x = 2;
}else{
  delayCurto = millis();
  if((delayCurto - timeCurto) > 5000 && x == 1){
    digitalWrite(ledDefeito, HIGH);
    x = 0;
    timeCurto = delayCurto;
  }
  if(x == 1){
  controla_led_curto();
  }
}
    if(!digitalRead(fonte40S) && x == 0){

      y = 1;
      timeTeste = millis();
      tempo = timeTeste;
  }
      
  if(!digitalRead(fonte60S) && x == 0){
      y = 2;
            timeTeste = millis();
      tempo = timeTeste;
  }
      
  if(!digitalRead(fonte70S) && x == 0){

      y = 3;
            timeTeste = millis();
      tempo = timeTeste;
  }
      
  if(!digitalRead(fonte120S) && x == 0){

      y = 4;
            timeTeste = millis();
      tempo = timeTeste;
  }
      
      
  if(!digitalRead(fonte150S) && x == 0){

      y = 5;
      timeTeste = millis();
      tempo = timeTeste;
  }   
  if(!digitalRead(fonte200S) && x == 0){

      y = 6;
      timeTeste = millis();
      tempo = timeTeste;
  }
  if(y == 1 && x == 2){
    fonte40();
    x = 3;
  }
    if(y == 2 && x == 2){
    fonte60();
    x = 3;
  }
    if(y == 3 && x == 2){
    fonte70();
    x = 3;
  }
    if(y == 4 && x == 2){
    fonte120();
    x = 3;
  }
    if(y == 5 && x == 2){
    fonte150();
    x = 3;
  }
    if(y == 6 && x == 2){
    fonte200();
    x = 3;
  }

   emon1.calcVI(17,2);
  float supplyVoltage   = emon1.Vrms;
  if(y == 1){ 
  if(x == 3 && supplyVoltage > 10 ){
  }else{
    if(x == 2){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
    }
  }
    if(y == 2){
     
  if(x == 3 && supplyVoltage > 10){
     
  }else{
    if(x == 2){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
  }
  }
    if(y == 3){
  if(x == 3 && supplyVoltage > 10 ){
     
  }else{
    if(x == 2){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
    }
  }
    if(y == 4){
  if(x == 3 && supplyVoltage > 10 ){
     
  }else{
    if(x == 2){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
    }
  }
    if(y == 5){
  if (x == 3 && supplyVoltage > 10 ){
     
  }else{
    if(x == 2){
    digitalWrite(ledDefeito, HIGH);
    desligaLed(); 
    x = 0;
    y = 0;
    }
    }
  }  
    if(y == 6){
  if(x == 3 && supplyVoltage > 10 ){
     
  }else{
    if(x == 2){
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
  if( tensaoMedida > 10 ){
    }else{
      if(x == 3){
     tempo = timeTeste;
     digitalWrite(ledDefeito, HIGH);
     desligaLed(); 
     x = 0;
     desligaLed();
    }
    }
    if(x == 2){
      timeTeste = millis();
      tempo = timeTeste;
    }
     if(x == 3){
    timeTeste = millis();
    Serial.println(timeTeste - tempo );
    if(timeTeste - tempo > 14000){//3:30 minutos
   tempo = timeTeste;
   digitalWrite(ledDefeito, LOW);
   digitalWrite(ledTeste, LOW);
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
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, LOW);
  digitalWrite(rele4, LOW);
}
void fonte60(){
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, LOW);
  digitalWrite(rele4, LOW);
}
void fonte70(){
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, LOW);
  digitalWrite(rele4, LOW);
}void fonte120(){
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, LOW);
  digitalWrite(rele4, LOW);
}  
void fonte150(){
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, LOW);
  digitalWrite(rele4, LOW);;
}
void fonte200(){
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, LOW);
  digitalWrite(rele4, LOW);
}

void desliga_fontes(){
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);
  digitalWrite(rele4, HIGH);
  digitalWrite(rele5, HIGH);
  digitalWrite(rele6, HIGH);
  digitalWrite(rele7, HIGH);
  digitalWrite(rele8, HIGH);
  digitalWrite(rele9, HIGH);
  digitalWrite(rele10, HIGH);
  digitalWrite(rele11, HIGH);
  digitalWrite(rele12, HIGH);
  digitalWrite(rele13, HIGH);
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
  if(x == 2){
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
void acende_led_OK(){
  digitalWrite(ledOk, HIGH);
}
void desligaTodosLeds(){
  digitalWrite(ledTeste,LOW);
  digitalWrite(ledCurto, LOW);
  digitalWrite(ledSensor, LOW);
  digitalWrite(ledDefeito, LOW);
  digitalWrite(ledOk, LOW);
}
void desligaLed(){
  digitalWrite(ledTeste,LOW);
  digitalWrite(ledCurto, LOW);
  
}
void acendeTodosLeds(){
  digitalWrite(ledTeste,HIGH);
  digitalWrite(ledCurto, HIGH);
  digitalWrite(ledSensor, HIGH);
  digitalWrite(ledDefeito, HIGH);
  digitalWrite(ledOk, HIGH);
}
