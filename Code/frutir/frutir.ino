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
  pinMode(buzzer, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("     FRUTIR     ");
  lcd.setCursor(1,0);
  lcd.print("  Fruit Sortir  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("     FRUTIR     ");
  lcd.setCursor(1,0);
  lcd.print("  System Ready  ");
  digitalWrite(buzzer, HIGH);
  delay(1500);
  digitalWrite(buzzer, LOW);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
 
   // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);

  myservo.attach(19); // pin servo
 
  Serial.begin(9600);
}

void bacaWarna(){
digitalWrite(S2,LOW);
digitalWrite(S3,LOW);
R = pulseIn(sensorOut, LOW);
// Printing the value on the serial monitor
Serial.print("R= ");//printing name
Serial.print(R);//printing RED color frequency
Serial.print(" ");
delay(100);
// Setting Green filtered photodiodes to be read
digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);
// Reading the output frequency
G = pulseIn(sensorOut, LOW);
// Printing the value on the serial monitor
Serial.print("G= ");//printing name
Serial.print(G);//printing RED color frequency
Serial.print(" ");
delay(100);
// Setting Blue filtered photodiodes to be read
digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);
// Reading the output frequency
B = pulseIn(sensorOut, LOW);
// Printing the value on the serial monitor
Serial.print("B= ");//printing name
Serial.print(B);//printing RED color frequency
Serial.println(" ");
delay(100); 
}



void loop()
{
 bacaWarna();
 if (G < 100){
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
