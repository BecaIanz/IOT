#include <time.h>
#include <WiFi.h>

const char *SSID = "M52 de Rebeca";
const char *password = "81925350";
const char *servidor = "pool.ntp.org";
const long fuso = -10800;
const int verao = 0;

void WiFiEvent(WiFiEvent_t event){
  switch(event){
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
    //aqui agente coloca oq vai acontecer quando conectar no wifi
      Serial.println("conectadinho");

      break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.print("Desconectado");
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

  configTime(fuso, verao, servidor);
}

void loop() {
  struct tm  timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("sem hora");
    return;
  }
  Serial.println(&timeinfo);
}
