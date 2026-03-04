#include <PubSubClient.h>
#include "env.h"

extern unsigned long tempo;
extern float temp;


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("MSG recebida no tópico: ");
  Serial.println(topic);

  String msg = "";

  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.println("Conteudo: " + msg);

  // client.publish(topico_temp, String(temp).c_str());
  // Serial.println(String(temp).c_str());

  if (topic == topico_esteira) {
    if (msg == "LIGADA") {
      // ligar esteira
      digitalWrite(ligarEsteira, 0);
      digitalWrite(desligarEsteira, 1);
      Serial.println("ligueii!!");
    } else {
      // desligar esteira
      digitalWrite(desligarEsteira, 0);
      digitalWrite(ligarEsteira, 1);
      Serial.println("desligado =(");
    }
  }
}

boolean attemptMqttConnection() {
  String clientId = String(mqtt_client_id) + "_" + String(WiFi.macAddress());
  Serial.print("Tentando MQTT como: " + clientId + "... ");
  if (client.connect(clientId.c_str(), NULL, NULL, topico_esteira, 0, true, "OFFLINE")) {
    Serial.println("CONECTADO!");
    client.subscribe(topico_esteira);
    client.subscribe(topico_temp);
    return true;
  } else {
    Serial.print("Falha. rc=");
    Serial.print(client.state());
    return false;
  }
}

void taConectado() {
  if (!client.connected()) {
    isConnected = false;
    if (tempo > 5000) {
      tempo = 0;
      if (attemptMqttConnection()) tempo = 0;
    }
  } else {
    isConnected = true;
    client.loop();
  }
}