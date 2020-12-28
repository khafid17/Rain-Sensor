#include "DHT.h"

// konfigurasi
#include <ESP8266WiFi.h>
String apiKey = "HNM5WU4OXI6V5NLT"; //pastekan API keys thingspeak
const char *ssid =  "Mubal"; //nama wifi
const char *pass =  "golekdewe"; //password wifi
const char* server = "api.thingspeak.com";

#define DHTPIN 4
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 test! && START PROGRAM"));
  dht.begin();
  
  //  kondisi cek koneksi 
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Terkoneksi");
}

void loop() {

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check kondisi sensor.
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Gagal baca DHT sensor!"));
    return;
  }
    if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(f);
    postStr += "&field3=";
    postStr += String(h);
    postStr += "\r\n\r\n";
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  Serial.print(F("Kelembaban : "));
  Serial.print(h);
  Serial.print(F("%  Suhu : "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.println(F("°F "));
  }

    client.stop();
  Serial.println("Tunggu...");
  delay(1000);

}
