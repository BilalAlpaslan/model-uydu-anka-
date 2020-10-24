// Arduino IDE code for standalone ESP8266 to update a twitter account using the thingspeak.com API


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

// create an account at thingspeak.com and link your twitter account to get your API key, replace the x's
String API = "014ARPDCMOHH8UZ1";
             

// enter your ssid and password
const char* ssid = "irtifa";
const char* password = "1223334444";

// your message
String tweet = "#ApisArgeCansatYarismasindayereindim";

// open client
WiFiClient client;


void setup() {
 
// connect to wifi
WiFi.begin(ssid, password);

// allow time to make connection
while (WiFi.status() != WL_CONNECTED)
    delay(500);

// if connection to thingspeak.com is successful, send your tweet!
if (client.connect("184.106.153.149", 80))
{
  client.print("GET /apps/thingtweet/1/statuses/update?key=" + API + "&status=" + tweet + " HTTP/1.1\r\n");
  client.print("Host: api.thingspeak.com\r\n");
  client.print("Accept: /\r\n");
  client.print("User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n");
  client.print("\r\n");
}

}// setup


void loop()
{
}
