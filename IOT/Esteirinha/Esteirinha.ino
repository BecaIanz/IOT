 #include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "env.h"

unsigned long tempo = 0;
bool isConnected = false;

WiFiClient espClient;
PubSubClient client(espClient);

#define ligarEsteira 33
#define desligarEsteira 32

#define DHTPIN 13
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

float temp;
float tempAnterior = 0.00;

void setup() {
  pinMode(ligarEsteira, OUTPUT);
  pinMode(desligarEsteira, OUTPUT);
  Serial.begin(9600);
  //digitalWrite(desligarEsteira, 0);
  dht.begin();
  // digitalWrite(esteira, 0);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  configWifi();
  configuraTimer();  
}

void loop() {
  taConectado();
  temp = dht.readTemperature();

  if(temp != tempAnterior)
  {
    client.publish(topico_temp, String(temp).c_str());
    Serial.println(String(temp).c_str());
    tempAnterior = temp;
  }
  // Serial.print("Temperatura: ");
  // Serial.println(temp);
}
