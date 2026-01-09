
float duracao;
float distancia;

int trig = 2;
int echo = 4;
int buzzerPin = 5;

void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);
  duracao = pulseIn(echo,1);

  distancia = (duracao/2)*0.0343;

  if(distancia < 10.00){
    tone(buzzerPin, 1000);

  }
  else{
    
    noTone(buzzerPin); 
  }

  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println("cm");
  delay(50);

}
