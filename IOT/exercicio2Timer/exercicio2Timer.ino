#define LED 2

hw_timer_t *timer = NULL;
int tempo = 0;
int freq = 0;

void IRAM_ATTR onTimer(){
  tempo++;
  freq++;
}
void setup() {
  pinMode(LED, OUTPUT);
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000 , true, 0);
}

void loop() {
  if(freq >= 200 && tempo <= 5000){
    digitalWrite(LED, !digitalRead(LED));
    freq = 0;
  }
  if(freq >= 1000 && tempo >= 5000){
    digitalWrite(LED, !digitalRead(LED));
    freq = 0;
  }
  if(tempo >= 10000){
    freq = 0;
    tempo = 0;
  }
}
