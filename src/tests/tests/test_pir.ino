int pirPin = 10;
int ledPin = 11;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(pirPin) == HIGH) {
    Serial.println("Movimento detetado!");
    digitalWrite(ledPin, HIGH);
  } else {
    Serial.println("Sem movimento.");
    digitalWrite(ledPin, LOW);
  }
  delay(500);
}
