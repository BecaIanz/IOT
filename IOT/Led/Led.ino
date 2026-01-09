#include <time.h>
#include <WiFi.h>

const char *SSID = "M52 de Rebeca";
const char *password = "81925350";
hw_timer_t *timer = NULL;
int ledVermelho = 2;
int ledVerde = 4;

void IRAM_ATTR timerVerde(){
    digitalWrite(ledVerde,!digitalRead(ledVerde));
}

void WiFiEvent(WiFiEvent_t event){
  switch(event){
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
    //aqui agente coloca oq vai acontecer quando conectar no wifi
      Serial.println("conectadinho");
      timer = timerBegin(1000000);
      timerAttachInterrupt(timer, &timerVerde);
      timerAlarm(timer, 0.0000001, true, 0);
      break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.print("Desconectado");
      WiFi.reconnect();
      digitalWrite(ledVermelho,1);
      digitalWrite(ledVerde,0);
      break;
  }
}
void setup() {
  Serial.begin(9600);

  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(SSID, password);
}

void loop() {
}
