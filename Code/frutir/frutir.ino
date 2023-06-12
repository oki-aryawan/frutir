#include <WiFi.h>
#include <WebServer.h>
#include "html.h"
WebServer server(80);  // port 80
const char* ssid = "okinawa";
const char* password = "1234567890";

//========servo=====
#include <ESP32_Servo.h>

Servo myservo;
int pos1 = 180;  // buah tdk sesuai grade
int pos2 = 30;   // buah normal

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

int rv;
int gv;
int bv;

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
  String data = "[\"" + String(rv) + "\",\"" + String(gv) + "\",\"" + String(bv) + "\"]";
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
/*
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  // Configure the timer for PWM on the enA pin
  ledcSetup(0, 5000, 8); // Channel 0, 5000 Hz, 8-bit resolution
  ledcAttachPin(enA, 0); // Attach enA pin to Channel 0
*/

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
    //server.handleClient();
    //delay(500);
    if (rv > 160 && rv < 200) {
      myservo.write(pos1);  // Hitam
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(0, 0);
      lcd.print("Hitam, BUANG!!");
      //delay(500);
    }
    else if (rv > 210 && rv < 220) {
      myservo.write(pos2);  // merah diterima
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(0, 0);
      lcd.print("Merah, OKE!");
      //delay(500);
    }
    else if (rv > 235) {
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(0, 0);
      lcd.print("Gak Ada");
      myservo.write(pos2);
    }
  }
}
void directionControl() {
  // Set the motor speed using PWM
  ledcWrite(0, 100); // Channel 0, 100 (duty cycle)
  
  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
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
  //eksekusi();
  //directionControl();
  bacaWarna();

}
