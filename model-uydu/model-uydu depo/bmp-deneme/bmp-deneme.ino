#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;



void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  bmp.begin();
}


void loop() {  
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");
  
  Serial.print(bmp.readAltitude()-158);
  Serial.println(" meters");

  Serial.println();

  
  
  Serial1.print(bmp.readTemperature());
  Serial1.println(" *C");
  
  Serial1.print(bmp.readPressure());
  Serial1.println(" Pa");
  
  Serial1.print(bmp.readAltitude());
  Serial1.println(" meters");
  
  Serial1.print(bmp.readAltitude()-158);
  Serial1.println(" meters");

  Serial1.println();
  
  delay(500);
}
