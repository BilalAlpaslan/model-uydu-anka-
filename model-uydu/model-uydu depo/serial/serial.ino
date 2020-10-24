void setup() {
Serial.begin(9600);  
}
void loop() {
int x=1;
while (true){
 Serial.println("<1>,<1>,<1>,<1>,<1>,<1>");
 delay(1000);
 Serial.println("<2>,<2>,<2>,<2>,<2>,<2>");
 delay(1000);
 Serial.println("<3>,<4>,<6>,<8>,<10>,<2>");
 delay(1000);
 Serial.println("<4>,<8>,<1>,<16>,<15>,<4>");
 delay(1000);
 Serial.println("<3>,<4>,<6>,<8>,<10>,<2>");
 delay(1000);
 Serial.println("<2>,<2>,<2>,<2>,<2>,<2>");
 delay(1000);
 x++;
 }
  


}
