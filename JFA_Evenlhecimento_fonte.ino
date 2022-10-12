//ler sensores
#include "EmonLib.h"  //INCLUSÃO DE BIBLIOTECA

#define VOLT_CAL 127.0  //160.0 para 220

EnergyMonitor emon1;
//portas entradas
#define pinBotao 23
//seletora
#define fonte40S 25
#define fonte60S 27
#define fonte70S 29
#define fonte120S 31
#define fonte150S 33
#define fonte200S 35
//leds
#define ledBotao 24
#define ledTeste 30
#define ledSensor 22
#define ledOk 32
#define ledDefeito 34
#define ledCurto 26
#define ledTensaoFinal 28
//portas entradas sensores
#define sensor A0
#define sensorSaida A1
#define sensorCorrenteSaida A2
//disjuntores
#define rele1 36
#define rele2 38
#define rele3 40
#define rele4 42
#define rele5 44
#define rele6 46
#define rele7 48
#define rele8 50
#define rele9 52
#define rele10 37
#define rele11 39
#define rele12 41
#define rele13 43
//reles
//varaiveis de tempo
unsigned long timeTeste;
unsigned long tempo;
unsigned long delayPiscaCurto;
unsigned long delayPiscaCurtos;
unsigned long delayRele;
unsigned long timeRele;
unsigned long delayLigaRele;
unsigned long timeLigaRele;
unsigned long delayTensaoMedida;
unsigned long timeTensaoMedida;
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
byte x = 0;
byte y = 0;
byte estado = 1;
byte varificar = 0;
//variaveis sensores
float tensaoEntrada = 0.0;
float tensaoMedida = 0.0;

float valorR1 = 30000.0;
float valorR2 = 7500.0;
int leituraSensor = 0;
byte verificaLed = 0;
void setup() {
  Serial.begin(9600);  //inicia a porta serial na 9600
  //define leds
  pinMode(ledBotao, OUTPUT);
  pinMode(ledOk, OUTPUT);
  pinMode(ledDefeito, OUTPUT);
  pinMode(ledTensaoFinal, OUTPUT);
  pinMode(ledSensor, OUTPUT);
  pinMode(ledTeste, OUTPUT);
  pinMode(ledCurto, OUTPUT);
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
  pinMode(sensor, INPUT);
  pinMode(sensorSaida, INPUT);
  pinMode(sensorCorrenteSaida, INPUT);
  //disjuntores

  //fontes 40
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);
  pinMode(rele5, OUTPUT);
  pinMode(rele6, OUTPUT);
  pinMode(rele7, OUTPUT);
  pinMode(rele8, OUTPUT);
  pinMode(rele9, OUTPUT);
  pinMode(rele10, OUTPUT);
  pinMode(rele11, OUTPUT);
  pinMode(rele12, OUTPUT);
  pinMode(rele13, OUTPUT);
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
  //sensores
  emon1.voltage(sensor, VOLT_CAL, 1.7);
  acendeTodosLeds();
  delay(1000);
  desliga_todos_leds();
}

void loop() {
  controla_led();
  static unsigned long delayPisca;
  if ((millis() - delayPisca) < 3000) {
    leituraSensor = analogRead(sensorSaida);
    tensaoEntrada = (leituraSensor * 5.0) / 1024.0;
    tensaoMedida = tensaoEntrada / (valorR2 / (valorR1 + valorR2));
  }
  if ((millis() - delayPisca) >= 6000) {
    delayPisca = millis();
  }

  if (!digitalRead(pinBotao) && x == 0) {
    delay(400);
    if (tensaoMedida > 11) {
      x = 1;
      estado = 0;
    }
    desliga_fontes();
    digitalWrite(ledBotao, HIGH);
    digitalWrite(ledOk, LOW);
    digitalWrite(ledDefeito, LOW);
    delayPiscaCurtos = millis();
    delayPiscaCurto = delayPiscaCurtos;
    digitalWrite(ledTensaoFinal, LOW);
  }

  if (x == 0) {
    digitalWrite(ledTensaoFinal, LOW);
    digitalWrite(ledCurto, LOW);

  }
  if (x == 1) {
    x = 3;
  }
  if (!digitalRead(fonte40S) && x == 0) {
    y = 1;
  }

  if (!digitalRead(fonte60S) && x == 0) {
    y = 2;
  }

  if (!digitalRead(fonte70S) && x == 0) {
    y = 3;
  }

  if (!digitalRead(fonte120S) && x == 0) {
    y = 4;
  }
  if (!digitalRead(fonte150S) && x == 0) {
    y = 5;
  }
  if (!digitalRead(fonte200S) && x == 0) {
    y = 6;
  }
  if(estado == 1){
    desliga_fontes_devagar();
  }
if(x == 5){
  switch (y){
    case 1:
      fonte40();
    case 2:
      fonte60();
    case 3:
      fonte70();
    case 4: 
      fonte120();
    case 5:
      fonte150();
    case 6:
      fonte200();
  }
}

  emon1.calcVI(17, 100);
  float supplyVoltage = emon1.Vrms;
  if (supplyVoltage > 110) {
    digitalWrite(ledSensor, HIGH);
  } else {
    controla_led_sensor();
    if (x > 1) {
      tempo = timeTeste;
      x = 0;
      digitalWrite(ledDefeito, HIGH);
      desliga_todos_leds();
      desliga_fontes();
    }
  }
  if (tensaoMedida > 12 && x == 3) {
    x = 4;
  } else {
    controla_led_tensao();
  }
  if (tensaoMedida > 14 && x == 4) {
    timeTeste = millis();
    tempo = timeTeste;
    verificaLed = 0;
    delayLigaRele = millis();
    timeLigaRele = delayLigaRele;
    delayRele = millis();
    timeRele = delayRele;
    delayTensaoMedida = millis();
    timeTensaoMedida = delayTensaoMedida;
    x = 5;
    digitalWrite(ledTensaoFinal, HIGH);
  } else {
    controla_led_tensao();
  }
  if (tensaoMedida < 10 && x == 5) {
    digitalWrite(ledDefeito, HIGH);
    desligaLed();
    digitalWrite(ledTensaoFinal, LOW);
    x = 0;
    desliga_fontes();
  }
  if (x == 4) {
    verificaLed = 0;
    timeTeste = millis();
    tempo = timeTeste;
    delayLigaRele = millis();
    timeLigaRele = delayLigaRele;
    delayRele = millis();
    timeRele = delayRele;
  }
  if (x == 5) {
    timeTeste = millis();
    if (timeTeste - tempo > 23000) {  //3:30 minutos
      tempo = timeTeste;
      digitalWrite(ledDefeito, LOW);
      digitalWrite(ledTeste, LOW);
      digitalWrite(ledCurto, LOW);
      estado = 1;
      x = 0;
      if (x == 0) {
        digitalWrite(ledOk, HIGH);
      }
    }
    byte sinal = digitalRead(rele1);
    timeTeste = millis();
    if ((timeTeste - tempo) > 13000 && (timeTeste - tempo) < 23000) {
      delayRele = millis();
      timeRele = delayRele;
      verificaLed =  1;
      digitalWrite(ledTeste, HIGH);
    }
  }
  controla_led_teste();
}

void fonte40() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele9, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele10, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele2, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele3, HIGH);
  }
  
}
void fonte60() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele9, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele10, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele2, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele3, HIGH);
  }
}
void fonte70() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele9, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele10, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele2, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele3, HIGH);
  }
}
void fonte120() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele9, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele10, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele2, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele3, HIGH);
  }
}
void fonte150() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele9, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele10, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele2, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele3, HIGH);
  }
}
void fonte200() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele1, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele11, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele12, HIGH);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele13, HIGH);
  }
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
void desliga_fontes_devagar() {
  delayRele = millis();
  if((delayRele - timeRele) > 500){
  digitalWrite(rele1, LOW);
  }
    if((delayRele - timeRele) > 1000){
  digitalWrite(rele2, LOW);
  }
    if((delayRele - timeRele) > 1500){
  digitalWrite(rele3, LOW);
  }
    if((delayRele - timeRele) > 2000){
  digitalWrite(rele4, LOW);
  }
    if((delayRele - timeRele) > 2500){
  digitalWrite(rele5, LOW);
  }
    if((delayRele - timeRele) > 3000){
  digitalWrite(rele6, LOW);
  }
    if((delayRele - timeRele) > 3500){
  digitalWrite(rele7, LOW);
  }
    if((delayRele - timeRele) > 4000){
  digitalWrite(rele8, LOW);
  }
    if((delayRele - timeRele) > 4500){
  digitalWrite(rele9, LOW);
  }
    if((delayRele - timeRele) > 5000){
  digitalWrite(rele10, LOW);
  }
    if((delayRele - timeRele) > 5500){
  digitalWrite(rele11, LOW);
  }
    if((delayRele - timeRele) > 6000){
  digitalWrite(rele12, LOW);
  }
   if((delayRele - timeRele) > 6500){
  digitalWrite(rele13, LOW);
  }
    if((delayRele - timeRele) > 7000){
    timeRele = delayRele;
  }
}
void controla_led() {

  static unsigned long delayPisca;
  if (x == 0) {
    if ((millis() - delayPisca) < 300) {
      digitalWrite(ledBotao, HIGH);
    } else {
      digitalWrite(ledBotao, LOW);
    }
    if ((millis() - delayPisca) >= 600) {
      delayPisca = millis();
    }
  }
}
void controla_led_tensao() {
  static unsigned long delayPisca;
  if (x >= 3 && x <= 4) {
    if ((millis() - delayPisca) < 300) {
      digitalWrite(ledTensaoFinal, HIGH);
    } else {
      digitalWrite(ledTensaoFinal, LOW);
    }

    if ((millis() - delayPisca) >= 600) {
      delayPisca = millis();
    }
  }
}
void controla_led_teste() {
  static unsigned long delayPisca;
  if (x == 5 && verificaLed == 0) {
    if ((millis() - delayPisca) < 300) {
      digitalWrite(ledTeste, HIGH);
    } else {
      digitalWrite(ledTeste, LOW);
    }

    if ((millis() - delayPisca) >= 600) {
      delayPisca = millis();
    }
  }
}
void controla_led_sensor() {
  static unsigned long delayPisca;
  if ((millis() - delayPisca) < 300) {
    digitalWrite(ledSensor, HIGH);
  } else {
    digitalWrite(ledSensor, LOW);
  }

  if ((millis() - delayPisca) >= 600) {
    delayPisca = millis();
  }
}
void controla_led_curto() {
  static unsigned long delayPisca;
  if ((millis() - delayPisca) < 300) {
    digitalWrite(ledCurto, HIGH);
  } else {
    digitalWrite(ledCurto, LOW);
  }

  if ((millis() - delayPisca) >= 600) {
    delayPisca = millis();
  }
}
void acende_led_OK() {
  digitalWrite(ledOk, HIGH);
}
void desligaTodosLeds() {
  digitalWrite(ledTeste, LOW);
  digitalWrite(ledCurto, LOW);
  digitalWrite(ledSensor, LOW);
  digitalWrite(ledDefeito, LOW);
  digitalWrite(ledOk, LOW);
  digitalWrite(ledTensaoFinal, LOW);
}
void desligaLed() {
  digitalWrite(ledTeste, LOW);
  digitalWrite(ledCurto, LOW);
  digitalWrite(ledTensaoFinal, LOW);
}
void acendeTodosLeds() {
  digitalWrite(ledTeste, HIGH);
  digitalWrite(ledCurto, HIGH);
  digitalWrite(ledSensor, HIGH);
  digitalWrite(ledDefeito, HIGH);
  digitalWrite(ledOk, HIGH);
  digitalWrite(ledTensaoFinal, HIGH);
  digitalWrite(ledBotao, HIGH);
}

void desliga_todos_leds() {
  digitalWrite(ledTeste, LOW);
  digitalWrite(ledCurto, LOW);
  digitalWrite(ledSensor, LOW);
  digitalWrite(ledDefeito, LOW);
  digitalWrite(ledOk, LOW);
  digitalWrite(ledTensaoFinal, LOW);
  digitalWrite(ledBotao, LOW);
}
