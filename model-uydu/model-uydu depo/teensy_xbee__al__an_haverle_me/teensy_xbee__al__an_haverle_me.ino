void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    Serial1.println(Serial.read());
  }
}
