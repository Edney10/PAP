/*
*  Teste do Buzzer
*/

#define BUZZER_PIN 12

void setup() {
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
    tone(BUZZER_PIN, 1000);  // Emite um som de 1000Hz
    delay(1000);
    noTone(BUZZER_PIN);       // Para o som
    delay(1000);
}
