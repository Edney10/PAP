/*
*  Teste do Sensor PIR
*/

#define PIR_SENSOR_PIN 10

void setup() {
    Serial.begin(9600);
    pinMode(PIR_SENSOR_PIN, INPUT);
}

void loop() {
    if (digitalRead(PIR_SENSOR_PIN) == HIGH) {
        Serial.println("Movimento detectado!");
        delay(1000);
    }
}
