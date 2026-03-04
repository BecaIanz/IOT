#define led1 18
#define led2 19
#define led3 21
#define led4 22
#define led5 23
#define pot 34

int binarios[5];
int aux = 0;

hw_timer_t *timer = NULL;
volatile long tempo = 0;
int i = 0;

int leituraPot;
void IRAM_ATTR onTimer(){
  leituraPot = analogRead(pot);
  Serial.print("Leitura : ");
  Serial.println(leituraPot);
  tempo++;
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(pot, INPUT);

  Serial.begin(9600);
  
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000 , true, 0);    //entra no timer a cada 1 milisegundo
}

void decimal_binario(int num) {

  for(int i = 0; i < 5; i++){
    binarios[i] = 0;
  }
  int h = 0;

  while(num > 0 && h < 5){
    binarios[h] = num % 2;
    num = num / 2;
    h++;
  }

  for(int i = 0; i < 5/2; i++){
    aux = binarios[i];
    binarios[i] = binarios[4 - i];
    binarios[4 - i] = aux;
  }
}
void loop() {

  if (tempo > 100) {
    Serial.println(i);
    decimal_binario(i);

    digitalWrite(led1, binarios[0]);
    digitalWrite(led2, binarios[1]);
    digitalWrite(led3, binarios[2]);
    digitalWrite(led4, binarios[3]);
    digitalWrite(led5, binarios[4]);
    for(int i = 0; i < 5; i++){
      Serial.print(binarios[i]);
    }
    Serial.println(" ");
    i++;
    tempo = 0;
  } 
}

