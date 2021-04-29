#include <Servo.h>

#define PIN_LDR_LFT 1
#define PIN_LDR_RGHT 0
#define PIN_SERVO 12

#define MIN_ANG 0
#define MAX_ANG 180

#define DIFF_OFFSET 75
#define INC_VALUE 10
#define DELAY 20

Servo myServo;
int ldrLft;
int ldrRght;
int ldr_diff;
int ang;

void setup(){
    myServo.attach(PIN_SERVO);
    myServo.write(MIN_ANG);
    ang=MIN_ANG;
}

void loop(){
    ldrLft = analogRead(PIN_LDR_LFT);
    ldrRght = analogRead(PIN_LDR_RGHT);
    ldr_diff = ldrRght-ldrLft;

    if(ldr_diff > DIFF_OFFSET) ang+=INC_VALUE;
    if(ang>MAX_ANG) ang=MAX_ANG;
                
    if(ldr_diff <-DIFF_OFFSET) ang-=INC_VALUE;
    if(ang<MIN_ANG) ang=MIN_ANG;
    
    myServo.write(ang);
    
    delay(DELAY);
}
