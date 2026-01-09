
#define RELE 12
int elevator;
int currentFloor = 0;
String floorr;
int tempo;

void setup() {
  pinMode(RELE, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // int leitura = analogRead(RELE);
  // float volt = (leitura*5.0)/1024;
  if(Serial.available() > 0){

    floorr = Serial.readStringUntil('\n');
    Serial.println(floorr);
    if(floorr.toInt() != currentFloor && floorr.toInt() <=10 && floorr.toInt() >= 0){
      if(floorr.toInt() > currentFloor){
        for(int i= currentFloor; i <= floorr.toInt();i++){
          Serial.println(i);
          digitalWrite(RELE, 1);
          delay(2000);
        }
      }
      else{
        for(int i= currentFloor; i >= floorr.toInt();i--){
          Serial.println(i);
          digitalWrite(RELE, 1);
          delay(2000);
        }
      }
      currentFloor = floorr.toInt();
      digitalWrite(RELE, 0);

      Serial.print("Você esta no andar: ");
      Serial.println(currentFloor);
    }
    else{
    Serial.println("NÃO TEM ESSE ANDAR CABEÇÃO");
    }
  }
} 