#include <WiFi.h>
#include <WebServer.h>
#include "html.h"
WebServer server(80);  // port 80
const char* ssid = "ZERLAN TEAM";
const char* password = "tanayabot";
//========servo=====
#include <ESP32_Servo.h>

Servo myservo;
int pos1 = 130;  // buah tdk sesuai grade
int pos2 = 10;   // buah normal
int grade = 0;
int no_grade = 0;
String status[] = {"  Buah  Matang  ", " Buah   Mentah  ", " Tidak Ada Buah "};

//============== TCS 3200 =============
#define S2 2
#define S3 4
#define sensorOut 18
int R = 0;
int G = 0;
int B = 0;
//kalibrasi sensor
int redMin = 5;      // Red minimum value
int redMax = 71;     // Red maximum value
int greenMin = 8;    // Green minimum value
int greenMax = 113;  // Green maximum value
int blueMin = 7;     // Blue minimum value
int blueMax = 98;    // Blue maximum value

int rv; int gv; int bv;

//=======L298N======
int enA = 32;
int in1 = 33;
int in2 = 25;

//=======LCD=====
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define buzzer 34  //buzzer

void MainPage() {
  String _html_page = html_page;             /*Read The HTML Page*/
  server.send(200, "text/html", _html_page); /*Send the code to the web server*/
}

void Colors() {
  String data = "[\"" + String(rv) + "\",\"" + String(gv) + "\",\"" + String(bv) + "\", \"" + String(grade) + "\", \"" + String(no_grade) + "\"]";
  server.send(200, "text/plane", data);
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("     FRUTIR     ");
  lcd.setCursor(0, 1);
  lcd.print("  Fruit Sortir  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("     FRUTIR     ");
  lcd.setCursor(0, 1);
  lcd.print("  System Ready  ");
  digitalWrite(buzzer, HIGH);
  delay(1500);
  digitalWrite(buzzer, LOW);
  lcd.clear();
  //set pinmode TCS3200
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(buzzer, OUTPUT);
  // Setting frequency-scaling to 20%
  myservo.attach(15);  // pin servo
  // konek wifi
  WiFi.mode(WIFI_STA);        /*Set the WiFi in STA Mode*/
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  lcd.setCursor(0, 0);
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  Serial.println(ssid);
  delay(1000);                /*Wait for 1000mS*/
  lcd.clear();
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    lcd.setCursor(0, 0);
    lcd.print(".");
    delay(200);
  } /*Wait while connecting to WiFi*/
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Your Local IP address is: ");
  lcd.setCursor(0, 0);
  lcd.print(WiFi.localIP());
  Serial.println(WiFi.localIP());       /*Print the Local IP*/
  server.on("/", MainPage);             /*Display the Web/HTML Page*/
  server.on("/readColors", Colors);     /*Display the updated Distance value(CM and INCH)*/
  server.begin();                       /*Start Server*/
  delay(1000);                          /*Wait for 1000mS*/

}

void bacaWarna() {
  static unsigned long previousMillis = 0;
  const unsigned long interval = 100; // Time interval between readings (in milliseconds)

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    //lcd.clear();
    R = getRedPW();
    rv = map(R, redMin, redMax, 255, 0);

    //delay(100);

    G = getGreenPW();
    gv = map(G, greenMin, greenMax, 255, 0);

    //delay(100);

    B = getBluePW();
    bv = map(B, blueMin, blueMax, 255, 0);

    //delay(100);

    //lcd.setCursor(0, 1); lcd.print("R"); lcd.print(R);
    Serial.print("R= ");
    Serial.print(rv);
    Serial.print(" ");

    //lcd.setCursor(6, 1); lcd.print("G"); lcd.print(G);
    Serial.print("G= ");
    Serial.print(gv);
    Serial.print(" ");

    //lcd.setCursor(12, 1);lcd.print("B");lcd.print(B);
    Serial.print("B= ");
    Serial.print(bv);
    Serial.println(" ");
    server.handleClient();
    //delay(500);
    if (gv > 240) {
      //lcd.clear();
      //lcd.backlight();
      lcd.setCursor(0, 1);
      lcd.print(status[1]);
      delay(500);
      myservo.write(pos1);  // mentah hijau
      no_grade ++;
      delay(800);
      //delay(500);
    }
    else if (rv > 240) {
      myservo.write(pos2);  // merah diterima
      //lcd.clear();
      //lcd.backlight();
      lcd.setCursor(0, 1);
      lcd.print(status[0]);
      grade ++;
      delay(500);
    }
    else {
      //lcd.clear();;
      //lcd.backlight();
      lcd.setCursor(0, 1);
      lcd.print(status[2]);
      myservo.write(pos2);
    }
  }
}


int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

void loop() {
  bacaWarna();
}