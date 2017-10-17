/*
  Projeto Vida Luz - Primeiros Passos
  Hardware Utilizado: Nodemcu v1.0, LDR
  Autor: Yhan Christian Souza Silva - versão 0.1
*/

// -- Definições de Hardware --

#define ldrPin 0
#define ledPin 5

// -- Variáveis -- 

unsigned long previousMillis  = 0;
const long interval = 1000;

// -- Protótipo de funções auxiliares --

int readSensor();
void turnOn();

// -- Setup -- 

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  Serial.println("Calibrando - Aguarde");
  Serial.println("......................................");
  delay(2000); 
}

// -- Loop --
void loop() {
  if(millis() - previousMillis >= interval) {
    readSensor();
    TurnOn();
    previousMillis = millis(); 
  } 
}

// -- Funções Auxiliares --

int readSensor() {
    unsigned int sensorValue = 0;
    sensorValue = analogRead(ldrPin);
    Serial.println(sensorValue);
    return sensorValue;
}

void TurnOn() {
       int lowLight = readSensor();
       if(lowLight < 150) digitalWrite(ledPin, HIGH);
       else digitalWrite(ledPin, LOW); 
}


