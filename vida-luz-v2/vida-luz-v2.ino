/*
  Projeto Vida Luz - Segunda Fase (Primeiros Passos)
  Hardware Utilizado: Nodemcu v1.0, LDR, Sensor PIR
  Autores: Yhan Silva  e Lucas Barros - versão 1.0
*/

// -- Definição de Hardware --

#define pinoLDR A0
#define pinoPIR D4
#define saidaLED D5


// -- Variáveis e constantes --

const int tempoCalibracaoPIR = 30, iluminacaoBoa = 600, iluminacaoMedia = 400, iluminacaoRuim = 200, semIluminacao = 50;
unsigned long ultimoMillis = 0;
const long intervaloLeitura = 3000;


// -- Escopo de funções Auxiliares --

int leituraSensorLDR();
boolean leituraPIR();
void saidLEDPWM();

// -- Setup e inicialização do sistema --

void setup() {
  Serial.begin(9600);
  pinMode(saidaLED, OUTPUT);
  pinMode(pinoPIR, INPUT);
  Serial.println("Calibrando sensor PIR - AGUARDE");
  for (uint8_t i = 0; i < tempoCalibracaoPIR; i++) {
    Serial.print(".");
    delay(1000);
  }
}

// -- Loop --

void loop() {
  if (millis() - ultimoMillis >= intervaloLeitura) {
    leituraSensorLDR();
    leituraPIR();
    saidLEDPWM();
    ultimoMillis = millis();
  }
}

// -- Funções Auxiliares --

int leituraSensorLDR() {
  int leituraSensor = analogRead(pinoLDR);
  Serial.print("Leitura LDR: ");
  Serial.println(leituraSensor);
  return leituraSensor;
}

boolean leituraPIR() {
  boolean estadoPIR = false;
  estadoPIR = digitalRead(pinoPIR);
  Serial.print("Leitura PIR: ");
  Serial.println(estadoPIR);
  return estadoPIR;
}
void saidLEDPWM() {
  boolean verificaSensorPIR = leituraPIR();
  int verificaSensorLDR = leituraSensorLDR();

  // identificou presença e há baixa iluminação LED ligará em 100%

  if (verificaSensorLDR < iluminacaoMedia && verificaSensorPIR) {
    analogWrite(saidaLED, 1023);
    Serial.println("Há pedestre e baixa luminosidade - LED 100%");
  }

  //rua iluminada, iluminação desligada

  else if (verificaSensorLDR >= iluminacaoBoa) {
    analogWrite(saidaLED, 0);
    Serial.println("Rua esta iluminada - LED 0%");
  }

  // led liga em 25%

  else if (verificaSensorLDR >= iluminacaoMedia && verificaSensorLDR < iluminacaoBoa) {
    analogWrite(saidaLED, 255);
    Serial.println("Não há pedestre e a rua parcialmente iluminada - LED 25%");
  }

  // led liga em 50%

  else if (verificaSensorLDR >= iluminacaoRuim && verificaSensorLDR < iluminacaoMedia) {
    analogWrite(saidaLED, 512);
    Serial.println("Não há pedestre e a rua pouco iluminada - LED 50%");
  }

  // led liga em 75%

  else if (verificaSensorLDR >= semIluminacao && verificaSensorLDR < iluminacaoRuim)  {
    analogWrite(saidaLED, 768);
    Serial.println("Não há pedestre e a rua mal iluminada - LED 75%");
  }


  // led liga em 100% mesmo sem identificar presença "rua muito escura"

  else {
    analogWrite(saidaLED, 1023);
    Serial.println("Não há pedestre e a rua não esta iluminada - LED 100%");
  }
}

