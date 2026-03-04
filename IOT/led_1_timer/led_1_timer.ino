                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   #include <time.h>
#include <WiFi.h>

const char *SSID = "M52 de Rebeca";
const char *password = "81925350";
hw_timer_t *timer = NULL;
int ledVermelho = 2;
int ledVerde = 4;
bool isConected;
int tempo = 0;

void IRAM_ATTR timerLed(){
  if(isConected){
    digitalWrite(ledVerde,!digitalRead(ledVerde));
    digitalWrite(ledVermelho,0);
  }
  else{
    if(tempo == 5){
      digitalWrite(ledVermelho,!digitalRead(ledVermelho));
      digitalWrite(ledVerde,0);
      tempo = 0;
    }
    tempo++;
  }
}
void WiFiEvent(WiFiEvent_t event){
  switch(event){
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("conectadinho");
      isConected = true;
      break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.print("Desconectado");
      isConected = false;
      WiFi.reconnect();
      break;
  }
}
void setup() {
  Serial.begin(9600);

  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(SSID, password);
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &timerLed);
  timerAlarm(timer, 100000, true, 0);
}

void loop() {
}