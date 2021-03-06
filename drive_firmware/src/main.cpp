#include <Arduino.h>
#include <Servo.h>

// Pins to Left Wheels
#define pinL1 13
#define pinL2 12

// Pins to Right Wheels
#define pinR1 9
#define pinR2 8


// PWM specs of the Spark motor controller. Spark manual:
//      http://www.revrobotics.com/content/docs/LK-ATFF-SXAO-UM.pdf
#define sparkMax 1000 // Default full-reverse input pulse
#define sparkMin 2000 // Default full-forward input pulse


Servo leftOne;
Servo leftTwo;

Servo rightOne;
Servo rightTwo;


struct DATA {
    float linear;
    float rotation;
    float servo;
} received;

void setWheelVelocity(int left, int right) {
    leftOne.writeMicroseconds(map(left, -100, 100, sparkMin, sparkMax));
    leftTwo.writeMicroseconds(map(left, -100, 100, sparkMin, sparkMax));
    
    rightOne.writeMicroseconds(map(right, -100, 100, sparkMin, sparkMax));
    rightTwo.writeMicroseconds(map(right, -100, 100, sparkMin, sparkMax));
    
}

void setup() {
    Serial.begin(9600);
    leftOne.attach(pinL1);
    leftTwo.attach(pinL2);
   
    rightOne.attach(pinR1);
    rightTwo.attach(pinR2);
    
}

void loop() {
   if (Serial.available() >= sizeof(uint8_t)) {
       delayMicroseconds(10);
       uint8_t cmd = (uint8_t) Serial.read();
       // Serial.print("GOT a cmd");
       // Serial.println(cmd);
       // TWIST MOTOR COMMAND
       if (cmd == 0) {
           Serial.readBytes((char *) &received.linear, sizeof(float));
           Serial.readBytes((char *) &received.rotation, sizeof(float));
           // Serial.print("GOT TWIST");
           // Serial.println((int) received.linear);
           // Serial.println((int) received.rotation);
           setWheelVelocity((int) ((received.linear + received.rotation) * 100), (int) ((received.linear - received.rotation) * 100));
       }
       
       
   }
}

