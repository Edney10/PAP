/*
*  Programador.....: (c) Edney Silva
*  Data...........:  30/01/2025
*  Observação.....:  
*/
#include <Keypad.h>

// Configuração do teclado 4x4
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Definição de pinos e variáveis
int pirPin = 10;
int ledPin = 11;
int buzzer = 12;
const String senhaCorreta = "4321";
String senhaDigitada = "";
bool movimentoDetectado = false;

// Definindo os estados da máquina de estados
enum Estado { ESPERANDO, ALARME_ATIVO, SENHA_CORRETA, SENHA_INCORRETA };
Estado estadoAtual = ESPERANDO;

// Configuração inicial
void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(pirPin, LOW);

  Serial.print("Calibrando sensor");
  for (int i = 0; i < 30; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ATIVO");
  delay(50);
}

// Loop principal
void loop() {
  char tecla = keypad.getKey();
  movimentoDetectado = digitalRead(pirPin) == HIGH;

  switch (estadoAtual) {
    case ESPERANDO:
      // Aguardar até que movimento seja detectado
      if (movimentoDetectado) {
        estadoAtual = ALARME_ATIVO;
        digitalWrite(ledPin, HIGH);
        tone(buzzer, 1000);
        Serial.println("Movimento detectado! Alarme ativado.");
      }
      break;

    case ALARME_ATIVO:
      // Se o alarme estiver ativo, aguarda o input do teclado
      if (tecla) {
        Serial.print("Tecla pressionada: ");
        Serial.println(tecla);

        if (tecla == '#') {
          if (senhaDigitada == senhaCorreta) {
            estadoAtual = SENHA_CORRETA;
            Serial.println("Senha correta! Alarme desativado.");
            noTone(buzzer);
            digitalWrite(ledPin, LOW);
          } else {
            estadoAtual = SENHA_INCORRETA;
            Serial.println("Senha incorreta! Tente novamente.");
          }
          senhaDigitada = ""; // Reseta a senha digitada
        } else {
          senhaDigitada += tecla;
        }
      }
      break;

    case SENHA_CORRETA:
      // Alarme desativado, o sistema volta a esperar
      estadoAtual = ESPERANDO;
      break;

    case SENHA_INCORRETA:
      // Senha incorreta, aguarda nova tentativa
      estadoAtual = ALARME_ATIVO;
      senhaDigitada = ""; // Limpa a senha para nova tentativa
      break;
  }
}
