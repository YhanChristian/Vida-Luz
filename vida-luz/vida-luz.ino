/*
  Projeto Vida Luz - Primeiros Passos
  Hardware Utilizado: Nodemcu v1.0, LDR, Sensor PIR
  Autor: Yhan Christian Souza Silva - versão 0.2
*/

// -- Definições de Hardware --

#define ldrPin 0
#define ledPin 5
#define pirPin 4

// -- Variáveis --

unsigned long previousMillis01  = 0;
unsigned long previousMillis02  = 0;
const long interval01 = 1000;
const long interval02 = 20000;
const int calibrationTime = 30;

// -- Protótipo de funções auxiliares --

int readLdr();
boolean readPir();
boolean turnOn();
void turnOff();

// -- Setup --

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.println("Calibrando - Aguarde");
  for (unsigned int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(1000);
  }
}

// -- Loop --
void loop() {
  if (millis() - previousMillis01 >= interval01) {
    readLdr();
    readPir();
    turnOn();
    previousMillis01 = millis();
  }
  if (millis() - previousMillis02 >= interval02) {
    turnOff();
    previousMillis02 = millis();
  }
}

// -- Funções Auxiliares --

int readLdr() {
  unsigned int ldrValue = 0;
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);
  return ldrValue;
}

boolean readPir() {
  boolean pirState = false;
  pirState = digitalRead(pirPin);
  Serial.println(pirState);
  return pirState;
}

boolean turnOn() {
  int lowLight = readLdr();
  boolean ledState;
  boolean detectMotion = readPir();
  if (lowLight < 300 && detectMotion)
  {
    digitalWrite(ledPin, HIGH);
    ledState = true;
    previousMillis02 = millis();
  }
  else ledState = false;
  return ledState;
}

void turnOff() {
  if (!turnOn()) digitalWrite(ledPin, LOW);
}


