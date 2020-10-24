#include "Adafruit_BMP085.h"
#include "I2Cdev.h" 
#include "MPU6050.h" 
#include "Wire.h"


Adafruit_BMP085 bmp;
MPU6050 accelgyro; 
int16_t ax, ay, az; 
int16_t gx, gy, gz;
int ilk=0 ;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  accelgyro.initialize();
  bmp.begin();
  ilk = bmp.readAltitude();
}


void loop() {  
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.println();
  Serial.print(bmp.readTemperature());
  Serial.println(" C");
  
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  
  Serial.print(bmp.readAltitude());
  Serial.println(" m");
  
  Serial.print(bmp.readAltitude()-ilk);
  Serial.println(" m");
  
  if (Serial2.available() > 0){
    Serial.print("gps:");
    Serial.println(Serial2.read());
  }
  else {
    Serial.println("gps bağlanmadı");
  }
  
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.println(az);
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);

  
  Serial.println();
  



  
  Serial1.println();
  Serial1.print(bmp.readTemperature());
  Serial1.println(" *C");
  
  Serial1.print(bmp.readPressure());
  Serial1.println(" Pa");
  
  Serial1.print(bmp.readAltitude());
  Serial1.println(" m");
  
  Serial1.print(bmp.readAltitude()-160);
  Serial1.println(" m");
  
  if (Serial2.available() > 0){
    Serial1.print("gps:");
    Serial1.println(Serial2.read());
  }
  else {
    Serial1.println("gps bağlanmadı");
  }
  
  Serial1.print(ax); Serial.print("\t");
  Serial1.print(ay); Serial.print("\t");
  Serial1.println(az);
  Serial1.print(gx); Serial.print("\t");
  Serial1.print(gy); Serial.print("\t");
  Serial1.println(gz);

   Serial1.println();

  
  delay(1000);
}
