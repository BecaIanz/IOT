#include <PubSubClient.h>

extern unsigned long tempo;
extern const char* topico_status;
extern hw_timer_t *timer

;
int intensityNum;
String status = "LIGADO";

void callback(char* topic, byte* payload, unsigned int length) {
  bool isColor = true;

  Serial.print("MSG recebida no tópico: ");
  Serial.println(topic);

  analogWrite(LED_RED, 255);
  analogWrite(LED_GREEN, 255);
  analogWrite(LED_BLUE, 255);

  String msg = "";
  String color = "";
  String intensity = "";

  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  Serial.println("Mensagem de comando: " + msg);

  if (msg == "LIGA") {
    client.publish(topico_status, "LIGADO", true);
    status = "LIGADO";
    return;
  }
  else if (msg == "DESLIGA") {
    client.publish(topico_status, "DESLIGADO", true);
    status = "DESLIGADO";
    return;
  }

  if (String(topic) == topico_texto) {

    if (status == "DESLIGADO") {
      Serial.println("Esta desligado, nao e possivel ligar o LED!");
      return;
    }

    for (int i = 0; i < msg.length(); i++) {
      if (msg[i] == ':') {
        isColor = false;
      } else {
        if (isColor) {
          color += msg[i];
        } else {
          intensity += msg[i];
        }
      }
    }

    Serial.println("Cor: " + color);
    Serial.println("Intensidade: " + intensity);

    int intensityNum = intensity.toInt();

    intensityNum = 255 - (intensityNum * 255 / 1000);

    color.toLowerCase();
    Serial.println("Intensidade transformada: " + String(intensityNum));

    if (color == "red") {
      analogWrite(LED_RED, intensityNum);
    }
    else if (color == "green") {
      analogWrite(LED_GREEN, intensityNum);
    }
    else if (color == "blue") {
      analogWrite(LED_BLUE, intensityNum);
    }
    else if (color[color.length - 1] == "b"){
      timerAttachInterrupt(timer, &timerLED);
      timerAlarm(timer, 100000, true, 0);
    }
    else {
      Serial.println("Essa cor não tem não!");
    }
  }
}


boolean attemptMqttConnection() {
  String clientId = String(mqtt_client_id) + "_" + String(WiFi.macAddress());
  Serial.print("Tentando MQTT como: " + clientId + "... ");
  if (client.connect(clientId.c_str(), NULL, NULL, topico_status, 0, true, "OFFLINE")){
    Serial.println("CONECTADO!");
    client.publish(topico_status, "ONLINE", true);
    client.subscribe(topico_comando);
    client.subscribe(topico_texto);
    return true;
  } else {
    Serial.print("Falha. rc=");
    Serial.print(client.state());
    return false;
  }
}

void taConectado(){
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