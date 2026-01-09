hw_timer_t *timer = NULL;
int tempo = 0;


void IRAM_ATTR onTimer(){
  tempo++;
}
void setup() {
  Serial.begin(9600);

  WiFi.onEvent(WiFiEvent);
  WiFi.begin(SSID, password);
  Serial.println("Iniciando conexão Wifi");

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 10000000, true, 0);
}

void loop() {
  Serial.println("Variavel: " + String(tempo));
}
