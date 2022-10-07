//ler sensores
#include "EmonLib.h"  //INCLUSÃO DE BIBLIOTECA

#define VOLT_CAL 127.0  //160.0 para 220

EnergyMonitor emon1;
//portas entradas
#define pinBotao 33
//seletora
#define fonte40S 31
#define fonte60S 27
#define fonte70S 29
#define fonte120S 41
#define fonte150S 43
#define fonte200S 45  
//leds
#define ledBotao 22
#define ledTeste 28
#define ledSensor 23
#define ledOk 30
#define ledDefeito 32
#define ledCurto 24
#define ledTensaoFinal 26
//portas entradas sensores
#define sensor A0
#define sensorSaida A1
#define sensorCorrenteSaida A2
//disjuntores
#define rele1 50
#define rele2 51
#define rele3 53
#define rele4 47
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
unsigned long delayRele;
unsigned long timeRele;
unsigned long delayLigaRele;
unsigned long timeLigaRele;
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
int varificar = 0;
//variaveis sensores
float tensaoEntrada = 0.0;
float tensaoMedida = 0.0;

float valorR1 = 30000.0;
float valorR2 = 7500.0;
int leituraSensor = 0;
int verificaLed = 0;
void setup() {
  digitalWrite(rele1, 0);
  digitalWrite(rele2, 0);
  digitalWrite(rele3, 0);
  digitalWrite(rele4, 0);
  digitalWrite(rele5, 0);
  digitalWrite(rele6, 0);
  digitalWrite(rele7, 0);
  digitalWrite(rele8, 0);
  digitalWrite(rele9, 0);
  digitalWrite(rele10, 0);
  digitalWrite(rele11, 0);
  digitalWrite(rele12, 0);
  digitalWrite(rele13, 0);
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
  //rele rede
  pinMode(releCurto, OUTPUT);
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
  //sensores
  emon1.voltage(sensor, VOLT_CAL, 1.7);
  acendeTodosLeds();
  delay(1000);
  desligaTodosLeds();
}

void loop() {
  leituraSensor = analogRead(sensorSaida);
  tensaoEntrada = (leituraSensor * 5.0) / 1024.0;
  tensaoMedida = tensaoEntrada / (valorR2 / (valorR1 + valorR2));
  if (!digitalRead(pinBotao) && x == 0) {
    delay(400);
    if(tensaoMedida > 11){
    x = 1;
    }
    desliga_fontes();
    digitalWrite(ledBotao, 1);
    digitalWrite(ledOk, 0);
    digitalWrite(ledDefeito, 0);
    delayPiscaCurtos = millis();
    delayPiscaCurto = delayPiscaCurtos;
    digitalWrite(ledTensaoFinal, 0);
  }

  if (x == 0) {
    delayPiscaCurtos = millis();
    delayPiscaCurto = delayPiscaCurtos;
    delayCurto = millis();
    timeCurto = delayCurto;
    digitalWrite(ledTensaoFinal, 0);
    digitalWrite(ledCurto, 0);

  }
  if(y < 4){
    if(x == 1){
      x = 3;
    }
  }
if(y == 4){
  if (tensaoMedida < 10 && x == 1) {
    digitalWrite(ledCurto, 0);
    x = 3;
  } else {
    delayCurto = millis();
    if ((delayCurto - timeCurto) > 5000 && x == 1) {
      digitalWrite(ledCurto, 0);
      digitalWrite(ledDefeito, 1);
      desliga_fontes();
      x = 0;
      timeCurto = delayCurto;
    }
    if (x == 1) {
      controla_led_curto();
      digitalWrite(releCurto, 1);
    }
  }
}
if(y == 5){
  if (tensaoMedida < 10 && x == 1) {
    digitalWrite(ledCurto, 0);
    x = 3;
  } else {
    delayCurto = millis();
    if ((delayCurto - timeCurto) > 5000 && x == 1) {
      digitalWrite(ledCurto, 0);
      digitalWrite(ledDefeito, 1);
      desliga_fontes();
      x = 0;
      timeCurto = delayCurto;
    }
    if (x == 1) {
      controla_led_curto();
      digitalWrite(releCurto, 1);
    }
  }
}
if(y == 6){
  if (tensaoMedida < 10 && x == 1) {
    digitalWrite(ledCurto, 0);
    x = 3;
  } else {
    delayCurto = millis();
    if ((delayCurto - timeCurto) > 5000 && x == 1) {
      digitalWrite(ledCurto, 0);
      digitalWrite(ledDefeito, 1);
      desliga_fontes();
      x = 0;
      timeCurto = delayCurto;
    }
    if (x == 1) {
      controla_led_curto();
      digitalWrite(releCurto, 1);
    }
  }
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
  if (y == 1 && x == 5) {
    fonte40();
  }
  if (y == 2 && x == 5) {
    fonte60();
  }
  if (y == 3 && x == 5) {
    fonte70();
  }
  if (y == 4 && x == 5) {
    fonte120();
  }
  if (y == 5 && x == 5) {
    fonte150();
  }
  if (y == 6 && x == 5) {
    fonte200();
  }

  emon1.calcVI(17, 100);
  float supplyVoltage = emon1.Vrms;
  if (y == 1) {
    if (x == 5 && supplyVoltage < 0) {
      digitalWrite(ledDefeito, 1);
      desligaLed();
      x = 0;
      y = 0;
      desliga_fontes();
    }
  }
  if (y == 2) {
    if (x == 5 && supplyVoltage < 0) {
      digitalWrite(ledDefeito, 1);
      desligaLed();
      x = 0;
      y = 0;
      desliga_fontes();
    }
  }
  if (y == 3) {
    if (x == 5 && supplyVoltage < 0) {
      digitalWrite(ledDefeito, 1);
      desligaLed();
      x = 0;
      y = 0;
      desliga_fontes();
    }
  }
  if (y == 4) {
    if (x == 5 && supplyVoltage < 120) {
      digitalWrite(ledDefeito, 1);
      desligaLed();
      x = 0;
      y = 0;
      desliga_fontes();
    }
  }
  if (y == 5) {
    if (x == 5 && supplyVoltage < 120) {
      digitalWrite(ledDefeito, 1);
      desligaLed();
      x = 0;
      y = 0;
      desliga_fontes();
    }
  }
  if (y == 6) {
    if (x == 5 && supplyVoltage < 120) {
      digitalWrite(ledDefeito, 1);
      desligaLed();
      x = 0;
      y = 0;
      desliga_fontes();
    }
  }
  if (supplyVoltage > 0) {
    digitalWrite(ledSensor, 1);
  } else {
    controla_led_sensor();
    if (x > 1) {
      tempo = timeTeste;
      x = 0;
      digitalWrite(ledDefeito, 1);
      desliga_todos_leds();
    }
  }
  Serial.println(tensaoMedida);
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
    x = 5;
    digitalWrite(ledTensaoFinal, 1);
  } else {
    controla_led_tensao();
  }

  if (tensaoMedida < 10 && x == 5) {
    digitalWrite(ledDefeito, 1);
    desligaLed();
    digitalWrite(ledTensaoFinal, 0);
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
    if (timeTeste - tempo > 20000) {  //3:30 minutos
      tempo = timeTeste;
      digitalWrite(ledDefeito, 0);
      digitalWrite(ledTeste, 0);
      digitalWrite(ledCurto, 0);
      desliga_fontes();
      x = 0;
      if (x == 0) {
        digitalWrite(ledOk, 1);
      }
    }
    timeTeste = millis();
    if ((timeTeste - tempo) > 10000 && (timeTeste - tempo) < 20000) {
          delayRele = millis();
    timeRele = delayRele;
      verificaLed =  1;
      digitalWrite(ledTeste, 1);
    }
  }
  controla_led();
  controla_led_teste();
}

void fonte40() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele13, 1);
  }
}
void fonte60() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele13, 1);
  }
}
void fonte70() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele13, 1);
  }
}
void fonte120() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele13, 1);
  }
}
void fonte150() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele13, 1);
  }
}
void fonte200() {
  delayLigaRele = millis();
  if (delayLigaRele - timeLigaRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayLigaRele - timeLigaRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayLigaRele - timeLigaRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayLigaRele - timeLigaRele > 4000) {
    digitalWrite(rele13, 1);
  }
}
void desligaFonte200(){
  varificar = 1;
    delayRele = millis();
  if (delayRele - timeRele > 1000) {
    digitalWrite(rele10, 0);
  }
  if (delayRele - timeRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayRele - timeRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayRele - timeRele > 4000) {
    digitalWrite(rele13, 1);
  }
  varificar = 0;
}
void desligaFonte150(){
    varificar = 1;
    delayRele = millis();
  if (delayRele - timeRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayRele - timeRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayRele - timeRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayRele - timeRele > 4000) {
    digitalWrite(rele13, 1);
  }
  varificar = 0;
}
void desligaFonte120(){
    varificar = 1;
        if (varificar == 0) {
    delayRele = millis();
    timeRele = delayRele;
  }
    delayRele = millis();
  if (delayRele - timeRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayRele - timeRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayRele - timeRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayRele - timeRele > 4000) {
    digitalWrite(rele13, 1);
  }
  varificar = 0;
}
void desligaFonte70(){
    delayRele = millis();
  if (delayRele - timeRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayRele - timeRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayRele - timeRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayRele - timeRele > 4000) {
    digitalWrite(rele13, 1);
  }
  varificar = 0;
}
void desligaFonte60(){
    varificar = 1;
    delayRele = millis();
  if (delayRele - timeRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayRele - timeRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayRele - timeRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayRele - timeRele > 4000) {
    digitalWrite(rele13, 1);
  }
  varificar = 0;
}
void desligaFonte40(){
    varificar = 1;
    delayRele = millis();
  if (delayRele - timeRele > 1000) {
    digitalWrite(rele10, 1);
  }
  if (delayRele - timeRele > 2000) {
    digitalWrite(rele11, 1);
  }
  if (delayRele - timeRele > 3000) {
    digitalWrite(rele12, 1);
  }
  if (delayRele - timeRele > 4000) {
    digitalWrite(rele13, 1);
  }
  varificar = 0;
}
void desliga_fontes_devagar() {
  if(y == 1){
    desligaFonte40();
  }
    if(y == 2){
    desligaFonte60();
  }
    if(y == 3){
    desligaFonte70();
  }
    if(y == 4){
    desligaFonte120();
  }
    if(y == 5){
    desligaFonte150();
  }
    if(y == 6){
    desligaFonte200();
     }
} 
void desliga_fontes() {
  digitalWrite(rele1, 1);
  digitalWrite(rele2, 1);
  digitalWrite(rele3, 1);
  digitalWrite(rele4, 1);
  digitalWrite(rele5, 1);
  digitalWrite(rele6, 1);
  digitalWrite(rele7, 1);
  digitalWrite(rele8, 1);
  digitalWrite(rele9, 1);
  digitalWrite(rele10, 1);
  digitalWrite(rele11, 1);
  digitalWrite(rele12, 1);
  digitalWrite(rele13, 1);
}
void controla_led() {

  static unsigned long delayPisca;
  if (x == 0) {
    if ((millis() - delayPisca) < 300) {
      digitalWrite(ledBotao, 1);
    } else {
      digitalWrite(ledBotao, 0);
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
      digitalWrite(ledTensaoFinal, 1);
    } else {
      digitalWrite(ledTensaoFinal, 0);
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
      digitalWrite(ledTeste, 1);
    } else {
      digitalWrite(ledTeste, 0);
    }

    if ((millis() - delayPisca) >= 600) {
      delayPisca = millis();
    }
  }
}
void controla_led_sensor() {
  static unsigned long delayPisca;
  if ((millis() - delayPisca) < 300) {
    digitalWrite(ledSensor, 1);
  } else {
    digitalWrite(ledSensor, 0);
  }

  if ((millis() - delayPisca) >= 600) {
    delayPisca = millis();
  }
}
void controla_led_curto() {
  static unsigned long delayPisca;
  if ((millis() - delayPisca) < 300) {
    digitalWrite(ledCurto, 1);
  } else {
    digitalWrite(ledCurto, 0);
  }

  if ((millis() - delayPisca) >= 600) {
    delayPisca = millis();
  }
}
void acende_led_OK() {
  digitalWrite(ledOk, 1);
}
void desligaTodosLeds() {
  digitalWrite(ledTeste, 0);
  digitalWrite(ledCurto, 0);
  digitalWrite(ledSensor, 0);
  digitalWrite(ledDefeito, 0);
  digitalWrite(ledOk, 0);
  digitalWrite(ledTensaoFinal, 0);
}
void desligaLed() {
  digitalWrite(ledTeste, 0);
  digitalWrite(ledCurto, 0);
  digitalWrite(ledTensaoFinal, 0);
}
void acendeTodosLeds() {
  digitalWrite(ledTeste, 1);
  digitalWrite(ledCurto, 1);
  digitalWrite(ledSensor, 1);
  digitalWrite(ledDefeito, 1);
  digitalWrite(ledOk, 1);
  digitalWrite(ledTensaoFinal, 1);
  digitalWrite(ledBotao, 1);
}

void desliga_todos_leds() {
  digitalWrite(ledTeste, 0);
  digitalWrite(ledCurto, 0);
  digitalWrite(ledSensor, 0);
  digitalWrite(ledDefeito, 0);
  digitalWrite(ledOk, 0);
  digitalWrite(ledTensaoFinal, 0);
  digitalWrite(ledBotao, 0);
}
