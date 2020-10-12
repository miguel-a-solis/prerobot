// further details on pinout for color sensor TCS3200 can be found on the conference article
// which can be obtained on PDF at https://github.com/miguel-a-solis/prerobot

// Arduino Mega is used for including 9 color sensors
// SO for all 9 color sensors are connected to 5V
// S1 for all 9 color sensors are connected to GND
// pins 2-10 are used for S2
// pins 11-19 are used for S3
// pins 20-28 are used for each sensor output

#include <Servo.h>

int R = 0, G = 0, B = 0;
Servo lwheel, rwheel;

void setup() {
  for(int i=0; i<=28; i++){
    pinMode(i, OUTPUT);
  }
  lwheel.attach(29);
  rwheel.attach(30);
}

void loop() {
  for(int token=0; token <= 8; token++){
    digitalWrite(2 + token,LOW);
    digitalWrite(11 + token,LOW);
    R = pulseIn(20 + token, LOW);
    R = map(R,25,72,255,0);
    delay(100);

    digitalWrite(2 + token,HIGH);
    digitalWrite(11 + token,HIGH);
    G = pulseIn(20 + token, LOW);
    G = map(G,30,90,255,0);
    delay(100);

    digitalWrite(2 + token,LOW);
    digitalWrite(11 + token,HIGH);
    B = pulseIn(20 + token, LOW);
    B = map(B,25,70,255,0);
    delay(100);

    if(max(R,G,B) == R){ // counter-clockwise turn
      lwheel.writeMicroseconds(1500); 
      rwheel.writeMicroseconds(2000);
    }else if(max(R,G,B) == B){ // clockwise turn
      lwheel.writeMicroseconds(2000);
      rwheel.writeMicroseconds(1500);
    }else if(max(R,G,B) == G){ // straightforward movement
      lwheel.writeMicroseconds(2000);
      rwheel.writeMicroseconds(2000);
    }else{ // 1-second delay due to token absence
      delay(1000);
    }
  }

}