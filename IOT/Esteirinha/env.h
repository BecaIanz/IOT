#ifndef ENV_H
#define ENV_H
#define WIFI_SSID "iPhone de Patrick"
#define WIFI_PASS "quadrado1"                                                       

const char* mqtt_server    = "broker.hivemq.com";
const char* mqtt_client_id = "esp_esteira";                                   
const char* topico_esteira = "dta/esteira";
// const char* topico_status  = "dta/status";
const char* topico_temp    = "dta/temp";
const int   mqtt_port      =  1883;

#endif