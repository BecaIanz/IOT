#include <WiFi.h>

const char *SSID = "M52 de Rebeca";
const char *password = "81925350";


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

  WiFi.onEvent(WiFiEvent);
  WiFi.begin(SSID, password);
  Serial.println("Iniciando conexão Wifi");
}

void loop(){

}