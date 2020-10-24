void setup() {
  Serial1.begin(9600);
}

void loop() {
  
  while (Serial1.available() > 0) {
    Serial1.print(Serial1.read());
  }
}
