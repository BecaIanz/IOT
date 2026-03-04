#ifndef ENV_H
#define ENV_H
#define WIFI_SSID "BTIA_SON5CT"
#define WIFI_PASS "IUVr4qSh8kQe"
#define LED_RED 16
#define LED_GREEN 17
#define LED_BLUE 18


const char* mqtt_server    = "broker.hivemq.com";
const char* mqtt_client_id = "esp32_alunx";                                    // <---- Coloca o seu nomezinho aqui
const char* topico_comando = "bosch/ets/dta/rebeca/luz";
const char* topico_status  = "bosch/ets/dta/rebeca/status";
const char* topico_texto   = "bosch/ets/dta/rebeca/texto";
const int   mqtt_port      =  1883;

#endif