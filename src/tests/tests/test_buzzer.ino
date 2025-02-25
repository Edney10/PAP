int buzzer = 12;

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  tone(buzzer, 1000);  // Som de 1000 Hz
  delay(1000);
  noTone(buzzer);
  delay(1000);
}
