/**
 * @author    patrosque
 * @brief     Cliente MQTT Industrial para IoT (ESP32).
 * Implementa protocolo Pub/Sub com LWT (Last Will),
 * reconexão não-bloqueante e identidade única via MAC.
 * @version   2.1.1 
 * @date      2026-01-19
 * @history
 * v1.0.0 - 2026-01-10 - Implementação básica do conexão MQTT
 * v1.1.0 - 2026-01-12 - Adição comunicação string unidirecional
 * v1.2.1 - 2026-01-19 - Organização em pastas
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "env.h"

unsigned long tempo = 0;
bool isConnected = false;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  analogWrite(LED_RED, 255);
  digitalWrite(LED_GREEN, 255);
  digitalWrite(LED_BLUE, 255);
0,

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  configWifi();      
  configuraTimer(); 
}

void loop() {
  taConectado();
}