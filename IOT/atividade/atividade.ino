#define LED1 27
#define LED2 32
#define LED3 33
#define LED4 5
#define LED5 23
#define LED6 19
#define botao 17

int listaLed[] = {27, 32, 33, 5, 23, 19};
int ledAtual = 0;
int ledAnterior = 5;

int tempoLed = 0;
bool proximo = false;

hw_timer_t *timer = NULL;
int tempo = 0;
int flagBotao = 0;
bool sentido = true;               //true é sentido horario e false é sentido anti-horario
bool mudou = false;

void piscarLed(){
  if(sentido){
    if(mudou){
      if(ledAtual == 5){
        ledAtual = 1;
        ledAnterior = 0;
      }
      else if(ledAtual == 4){
        ledAtual = 0;
        ledAnterior = 5;
      }
      else{
        ledAtual = ledAnterior + 1;
        ledAnterior-2;
      }
    }

    digitalWrite(listaLed[ledAnterior], 0);
    digitalWrite(listaLed[ledAtual], 1);

    if(ledAtual == 5){
      ledAtual = 0;
      ledAnterior = 5;
    } 
    else{
      ledAnterior = ledAtual;
      ledAtual++;
    }
  } 
  else{
    if(mudou){
      if(ledAtual == 0){
        ledAtual = 4;
        ledAnterior = 5;
      }
      else if(ledAtual == 1){
        ledAtual = 5;
        ledAnterior = 0;
      }
      else{
        ledAtual = ledAnterior - 1;
        ledAnterior+2;
      }
    }

    digitalWrite(listaLed[ledAnterior], 0);
    digitalWrite(listaLed[ledAtual], 1);

    if(ledAtual == 0){
      ledAtual = 5;
      ledAnterior = 0;
    } 
    else{
      ledAnterior = ledAtual;
      ledAtual--;
    }
  }
    
  
}

void IRAM_ATTR botaoApertado(){
  if(flagBotao != 1){
    flagBotao = 1;
    tempo = 100;
  }
}

void onTimer(){
  tempoLed++;

  if(tempoLed == 500){
    piscarLed();
    tempoLed = 0;
    mudou = false;
  }

  if(flagBotao == 1){
    if(tempo > 0){
      tempo--;
    } else{
      flagBotao = 0;
      if(!digitalRead(botao)){
        sentido = !sentido;
        mudou = true;
      }
    }
  }
}

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  
  pinMode(botao, INPUT_PULLUP);
  Serial.begin(9600);
  
  
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000, true, 0);

  attachInterrupt(
    digitalPinToInterrupt(botao),
    botaoApertado,
    FALLING
  );


}

void loop() {
  Serial.print("Sentido: ");
  Serial.println(sentido);
  Serial.println("======================================");
  Serial.print("Led: ");
  Serial.println(ledAtual);
  Serial.println("======================================");

}
