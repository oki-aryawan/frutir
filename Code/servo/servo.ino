#include <Servo.h>

Servo myservo;
int pos1 = 180; // ada halangan
int pos2 = 110; // tidak ada halangan
int input = A0;


void setup() {
  myservo.attach(6);
 // myservo.write(pos);

}

void loop() {
 int nilai = analogRead(input);
  if (nilai > 500){
    myservo.write(pos1);
  } else myservo.write(pos2);
  
  
  // put your main code here, to run repeatedly:

}
