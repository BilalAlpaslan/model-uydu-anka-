#include "Adafruit_BMP085.h"
#include "MPU6050.h" 
#include "Wire.h"
#include "SoftwareSerial.h"
#include <SD.h>
#include <SPI.h>
#include <Adafruit_GPS.h>

#define mySerial Serial3 
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  true
File myFile;
const int chipSelect = BUILTIN_SDCARD;

int notaSayisi = 8;
int C = 262;
int D = 294;
int E = 330;
int F = 349;
int G = 392;
int A = 440;
int B = 494;
int C_ = 523;
int notalar[] = {C, D, E, F, G, A, B, C_};

Adafruit_BMP085 bmp;
MPU6050 accelgyro; 
int16_t ax, ay, az; 
int16_t gx, gy, gz;
int ty=0 ;
int paket = 1;
int led = 5;
int buzzerPin  = 6;
int takimNo = 3450;
int statu = 1;
float yerdenYukseklik = 0;


void bip(int a){
  for (int i = 0; i < notaSayisi; i++)
  {
    tone(buzzerPin, notalar[i]);
    delay(500);
    noTone(buzzerPin);
    delay(20);
  }
  noTone(buzzerPin);
}

uint32_t timer = millis();
void paketYolla(){
  char c = GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))   
      return;  
  }
  if (timer > millis())  timer = millis();
  if (millis() - timer > 1000) { 
    timer = millis(); // reset the timer  
    
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    ax = map(ax,-18000,18000,0,360);
    ay = map(ay,-18000,18000,0,360);
    az = map(az,-18000,18000,0,360);

    yerdenYukseklik = bmp.readAltitude()-ty;
    float go=analogRead(A2);
    go = map(go,0,1023,0,5);
    
    Serial.print(takimNo);Serial.print(",");
    Serial.print(paket);Serial.print(",");
    Serial.print(GPS.hour+3,DEC);Serial.print(':');Serial.print(GPS.minute,DEC);Serial.print(':');Serial.print(GPS.seconds,DEC);Serial.print(",");
    Serial.print(statu);Serial.print(",");
    Serial.print(yerdenYukseklik);Serial.print(",");
    Serial.print(bmp.readPressure());Serial.print(",");
    Serial.print(bmp.readTemperature());Serial.print(",");
    Serial.print(go);Serial.print(",");
    Serial.print(ax);Serial.print(",");
    Serial.print(ay);Serial.print(",");
    Serial.print(az);Serial.print(",");
    Serial.print(GPS.latitudeDegrees);Serial.print(",");
    Serial.print(GPS.longitudeDegrees);Serial.print(",");
    Serial.print(GPS.altitude);Serial.println("");
    
    Serial1.print(takimNo);Serial1.print(",");
    Serial1.print(paket);Serial1.print(",");
    Serial1.print(GPS.hour+3,DEC);Serial1.print(':');Serial1.print(GPS.minute,DEC);Serial1.print(':');Serial1.print(GPS.seconds,DEC);Serial1.print(",");
    Serial1.print(statu);Serial1.print(",");
    Serial1.print(yerdenYukseklik);Serial1.print(",");
    Serial1.print(bmp.readPressure());Serial1.print(",");
    Serial1.print(bmp.readTemperature());Serial1.print(",");
    Serial1.print((int)GPS.satellites);Serial1.print(",");
    Serial1.print(ax);Serial1.print(",");
    Serial1.print(ay);Serial1.print(",");
    Serial1.print(az);Serial1.print(",");
    Serial1.print(GPS.latitudeDegrees);Serial1.print(",");
    Serial1.print(GPS.longitudeDegrees);Serial1.print(",");
    Serial1.print(GPS.altitude);Serial1.println("");

    myFile = SD.open("test.csv", FILE_WRITE);
    myFile.print(takimNo);myFile.print(",");
    myFile.print(paket);myFile.print(",");
    myFile.print(GPS.hour+3,DEC);myFile.print(':');myFile.print(GPS.minute,DEC);myFile.print(':');myFile.print(GPS.seconds,DEC);myFile.print(",");
    myFile.print(statu);myFile.print(",");
    myFile.print(yerdenYukseklik);myFile.print(",");
    myFile.print(bmp.readPressure());myFile.print(",");
    myFile.print(bmp.readTemperature());myFile.print(",");
    myFile.print((int)GPS.satellites);myFile.print(",");
    myFile.print(ax);myFile.print(",");
    myFile.print(ay);myFile.print(",");
    myFile.print(az);myFile.print(",");
    myFile.print(GPS.latitudeDegrees);myFile.print(",");
    myFile.print(GPS.longitudeDegrees);myFile.print(",");
    myFile.print(GPS.altitude);myFile.println("");
    
    myFile.close();
    paket++;
  }
}


void statu1(){
  paketYolla(); 
  if (yerdenYukseklik < -13){
    statu=2;
  }
}
void statu2(){
  paketYolla();
  bip(500); 


}


void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  GPS.begin(9600);
  accelgyro.initialize();
  bmp.begin();
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //Sets output to only RMC and GGA sentences
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //Sets the output to 1/second. If you want you can go higher/lower
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(100);
  ty = bmp.readAltitude();
  mySerial.println(PMTK_Q_RELEASE);

  if (!SD.begin(chipSelect)) {
    return;
  }
}


void loop() {
  
  while(statu==1){
    statu1();
  }
  while(statu==2){
    statu2();
  }
}
