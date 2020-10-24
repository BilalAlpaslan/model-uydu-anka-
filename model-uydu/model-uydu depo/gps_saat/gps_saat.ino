
#include <Adafruit_GPS.h>
#define mySerial Serial3 

Adafruit_GPS GPS(&mySerial);                                                                     //GPS AYARLAMALARI
#define GPSECHO  true


void setup()  
{
  Serial.begin(9600);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);                                                              //GPS
  
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);  
  GPS.sendCommand(PGCMD_ANTENNA);                     //**********************************************************
  
  
  delay(1000);
  
  mySerial.println(PMTK_Q_RELEASE);
}


uint32_t timer = millis();
void loop()                     
{
  char c = GPS.read();
 
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))   
      return;  
  }
  if (timer > millis())  timer = millis();
  if (millis() - timer > 1000) { 
    timer = millis(); // reset the timer
    
    Serial.print(GPS.hour+3, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC);
    
  }
}
