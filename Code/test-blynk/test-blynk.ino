#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6Dw4jZLQI"
#define BLYNK_TEMPLATE_NAME "Frutir"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

char auth[] = "TMPL6Dw4jZLQI";
char ssid[] = "okinawa";
char pass[] = "1234567890";
BlynkTimer timer;


void setup()
{
  Serial.begin(115200);
  delay(1000);
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  timer.setInterval(1000L, kirimData);
}

void kirimData()
{
  

  Blynk.virtualWrite(V5, h); // select your virtual pins accordingly
  Blynk.virtualWrite(V6, t); // select your virtual pins accordingly
}

void loop()
{
  Blynk.run();
  timer.run();
}