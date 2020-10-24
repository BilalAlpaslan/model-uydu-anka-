/**   18,19 bmp mpu   0,1 xbee serial 1    9,10 gps serial 3  **/
#include "Adafruit_BMP085.h"
#include "I2Cdev.h" 
#include "MPU6050.h" 
#include "Wire.h"
#include "SoftwareSerial.h"
#include <Adafruit_GPS.h>

#define mySerial Serial3 
#define GPSECHO  true
Adafruit_GPS GPS(&mySerial);

Adafruit_BMP085 bmp;
MPU6050 accelgyro; 
int16_t ax, ay, az; 
int16_t gx, gy, gz;
int ilk=0 ;
double liste[14];
int paket = 1;
int statu = 1;
int led = 5;
int buzzer = 6;

uint32_t timer = millis();

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  GPS.begin(9600);
  accelgyro.initialize();
  bmp.begin();
  ilk = bmp.readAltitude();
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //Sets output to only RMC and GGA sentences
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //Sets the output to 1/second. If you want you can go higher/lower
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(100);
  mySerial.println(PMTK_Q_RELEASE);
}


void loop() { 
  char c = GPS.read(); 
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  if (GPS.newNMEAreceived()) {
  if (!GPS.parse(GPS.lastNMEA()))   
    return;  
  }
  if (timer > millis())  timer = millis();

  if (millis() - timer > 1000) { 
    timer = millis(); // reset the timer
                      
    liste[0] = 3450;                                  //takım no              ++
    liste[1] = paket;                                 //paket no              ++
    liste[2] = GPS.hour+3;                            //gönderme zamanı       +-
    liste[3] = GPS.minute;                                 //uydu statüsü          --
    liste[4] = GPS.seconds;                //yükseklik             ++
    liste[5] = bmp.readPressure();                    //basınç                ++
    liste[6] = bmp.readTemperature();                 //sıcaklık              ++
    liste[7] = (int)GPS.satellites;                   //pil gerilimi          --
    liste[8] = ax;                                    //yunuslama             +-
    liste[9] = ay;                                    //yalpalanma            +-
    liste[10] = az;                                   //yuvarlanma            +-
    liste[11] = GPS.latitudeDegrees;//GPS.latitude;   //gps boylam            +-
    liste[12] = GPS.longitudeDegrees;//GPS.longitude; //gps enlem             +-
    liste[13] = GPS.altitude;                         //gps yükseklik         +-
  

  

  


    for (int i = 0 ; i < 13 ; i++) {
      Serial.print(liste[i]);
      Serial.print(",");
    }
    Serial.print(liste[13]);
    Serial.println();
    
    for (int i = 0 ; i < 13 ; i++) {
      Serial1.print(liste[i]);
      Serial1.print(",");
    }
    Serial1.print(liste[13]);
    Serial1.println();
  
  /**   **/
    if(paket%5==0){
      digitalWrite(led,1);
    }
    else{
      digitalWrite(led,0);
    }
    
    paket++;
    delay(1000);
  }
}  
