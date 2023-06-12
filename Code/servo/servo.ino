#include <ESP32_Servo.h>

Servo myservo;
int pos1 = 180; // ada halangan
int pos2 = 30; // tidak ada halangan
int input = A0;


void setup() {
  myservo.attach(15);
 // myservo.write(pos);

}

void loop() {
 myservo.write(pos1);
 delay(2000);
 myservo.write(pos2);
 delay(2000);


}
