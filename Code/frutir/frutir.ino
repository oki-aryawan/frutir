//========servo=====
#include <ESP32_Servo.h>

Servo myservo;
int pos1 = 180; // ada halangan
int pos2 = 110; // tidak ada halangan

//============== TCS 3200 =============
#define S0 15
#define S1 2
#define S2 5
#define S3 4
#define sensorOut 18
int R = 0; // inisiasi variabel warna RGB
int G = 0;
int B = 0;

//=======L298N======
int enA = 11;
int in1 = 10;
int in2 = 8;

//=======LCD=====
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#define buzzer 34 //buzzer

void setup()
{
  Serial.begin(9600);
  lcd.init(); lcd.backlight();
  lcd.setCursor(0,0); lcd.print("     FRUTIR     ");
  lcd.setCursor(0,1); lcd.print("  Fruit Sortir  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("     FRUTIR     ");
  lcd.setCursor(0,1); lcd.print("  System Ready  ");
  digitalWrite(buzzer, HIGH);
  delay(1500);
  digitalWrite(buzzer, LOW);
  lcd.clear();
  //set pinmode TCS3200
  pinMode(S0, OUTPUT); pinMode(S1, OUTPUT); pinMode(S2, OUTPUT); 
  pinMode(S3, OUTPUT); pinMode(sensorOut, INPUT); pinMode(buzzer, OUTPUT);
   // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);digitalWrite(S1,HIGH);
  myservo.attach(19); // pin servo
}

void bacaWarna(){
digitalWrite(S2,LOW); digitalWrite(S3,LOW);
R = pulseIn(sensorOut, LOW);
// Printing the value on the serial monitor
lcd.setCursor(0,1); lcd.print("R="); lcd.print(R);
Serial.print("R= ");Serial.print(R); Serial.print(" ");
delay(100);


digitalWrite(S2,HIGH); digitalWrite(S3,HIGH);
G = pulseIn(sensorOut, LOW);
lcd.setCursor(6,1); lcd.print("G="); lcd.print(G);
Serial.print("G= "); Serial.print(G); Serial.print(" ");
delay(100);

digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);
B = pulseIn(sensorOut, LOW);
lcd.setCursor(12,1); lcd.print("B="); lcd.print(B);
Serial.print("B= "); Serial.print(B); Serial.println(" ");
delay(100);
lcd.clear();
}

void eksekusi(){
  // kondisi steady R10 G16-17 B15
  bacaWarna();
 if (G < 100 ){
  myservo.write(pos1);
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Kurang Matang");
 } else {myservo.write(pos2); 
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Sudah Matang"); }
}

void loop()
{
 bacaWarna();
 }

 