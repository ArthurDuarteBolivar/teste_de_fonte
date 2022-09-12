//bibilhotecas



//portas 16
//6 portas de selecao de modelo de fonte

//1 porta de botao
button = 5;
fonteA = 6;
fonteB = 7;
fonteC = 8;

//6 leds verificação de status 
led_entrada = 2;
led_inicio = 3;
led_fonte = 4;
//13 reles

//3 sensores
sensor_entrada = A0;

//variaveis
unsigned long time; //variável do tipo long
int x = 0
void setup() {
  
  #define SDADO 2
  #define SCLK 4
  #define LATCH 3
  
  pinMode(SDADO, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(LATCH, OUTPUT);
  
  pinMode(sensor_entrada, INPUT);
  pinMode(led_entrada, OUTPUT);
  pinMode(led_inicio, OUTPUT);
  pinMode(led_fonte, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(button), botao_inicio, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor_entrada), verifica_tensao_entrada, CHANGE);
  attachInterrupt(digitalPinToInterrupt(fonteA), selecionar_fonteA, FALLING);
  attachInterrupt(digitalPinToInterrupt(fonteB), selecionar_fonteB, FALLING);
  attachInterrupt(digitalPinToInterrupt(fonteC), selecionar_fonteC, FALLING);

}

void loop() {
  pisca_led_entrada();
  pisca_led_inicio();
  pisca_led_fonte();
  }

void pisca_led_entrada(){
  digitalWrite(led_entrada, HIGH);
  delay(500);
  digitalWrite(led_entrada, LOW);
  delay(500);
  
}
void pisca_led_inicio(){
if(x == 1){
  digitalWrite(led_inicio, HIGH);
  delay(500);
  digitalWrite(led_inicio, LOW);
  delay(500);
}

}
void pisca_led_fonte(){
if(x == 2){
  digitalWrite(led_fonte, HIGH);
  delay(500);
  digitalWrite(led_fonte, LOW);
  delay(500);
  }
}

void clockOUT()
{
  digitalWrite(SCLK, true);
  //delay(10);
  digitalWrite(SCLK, false);
}

