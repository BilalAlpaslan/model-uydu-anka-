#include <Adafruit_GPS.h>
#define GPSSerial Serial2
Adafruit_GPS GPS(&GPSSerial);
Adafruit_GPS Boat;

uint32_t timer = millis();

void setup() {
  Serial.begin(115200);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
}

void loop() {

  static unsigned nextInterval = 2000;
  if (millis() - timer > nextInterval) {
    timer = millis(); 
    nextInterval = 1500 + random(1000);
    float s = GPS.seconds + GPS.milliseconds / 1000. + GPS.secondsSinceTime();
    int m = GPS.minute;
    int h = GPS.hour;
    int d = GPS.day;
    while (s > 60) {
      s -= 60;
      m++;
    }
    while (m > 60) {
      m -= 60;
      h++;
    }
    while (h > 24) {
      h -= 24;
      d++;
    }
    Serial.print("\nDate: ");
    Serial.print(GPS.year + 2000, DEC);
    Serial.print("-");
    Serial.print(GPS.month, DEC);
    Serial.print("-");
    Serial.print(d, DEC);
    Serial.print("   Time: ");
    Serial.print(h, DEC);
    Serial.print(':');
    Serial.print(m, DEC);
    Serial.print(':');
    Serial.println(s, 3);
    //Serial.print("Fix: ");
    //Serial.print((int)GPS.fix);
    //Serial.print(" quality: ");
    //Serial.println((int)GPS.fixquality);
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4);
      Serial.print(", ");
      Serial.println(GPS.longitude, 4);
      Serial.print("Altitude: ");
      Serial.println(GPS.altitude);
      //Serial.print("Speed (knots): ");
      //Serial.println(GPS.speed);
      //Serial.print("Angle: ");
      //Serial.println(GPS.angle);
      //Serial.print("Satellites: ");
      //Serial.println((int)GPS.satellites);
    }

    char latestBoat[200] = "";
    updateBoat();                             
    Boat.build(latestBoat, "GN", "RMC");      
    //Serial.print("\nbuild() test output -->"); 
    //Serial.print(latestBoat);                 
    GPS.resetSentTime();   
    GPS.parse(latestBoat); 
  }
}


void updateBoat() { 
  double t = millis() / 1000.;
  double theta = t / 100.;   
  double gamma = theta * 10; 
  Boat.latitude = 4400 + sin(theta) * 60;
  Boat.lat = 'N';
  Boat.longitude = 7600 + cos(theta) * 60;
  Boat.lon = 'W';
  Boat.fixquality = 2;
  Boat.speed = 3 + sin(gamma);
  Boat.hour = abs(cos(theta)) * 24;
  Boat.minute = 30 + sin(theta / 2) * 30;
  Boat.seconds = 30 + sin(gamma) * 30;
  Boat.milliseconds = 500 + sin(gamma) * 500;
  Boat.year = 1 + abs(sin(theta)) * 25;
  Boat.month = 1 + abs(sin(gamma)) * 11;
  Boat.day = 1 + abs(sin(gamma)) * 26;
  Boat.satellites = abs(cos(gamma)) * 10;
}
