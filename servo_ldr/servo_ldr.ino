/*
Dev: Álison Venâncio
Video: https://www.youtube.com/watch?v=I33AGpzh8EI
*/

#include <Servo.h>

#define __PIN_LDR_LFT 1
#define __PIN_LDR_RGHT 0
#define __PIN_SERVO 12

#define __MIN_ANG 0
#define __MAX_ANG 180

#define __DIFF_OFFSET 75
#define __INC_VALUE 10
#define __DELAY 20

Servo myServo;
int ldr_lft;
int ldr_rght;
int ldr_diff;
int ang;

void setup(){
    myServo.attach(__PIN_SERVO);
    myServo.write(__MIN_ANG);
    ang=__MIN_ANG;

    myServo.attach(__PIN_SERVO);
    myServo.write(__MIN_ANG);
    ang=__MIN_ANG;
}

void loop(){
    ldr_lft = analogRead(__PIN_LDR_LFT);
    ldr_rght = analogRead(__PIN_LDR_RGHT);
    ldr_diff = ldr_rght-ldr_lft;

    if(ldr_diff > __DIFF_OFFSET) ang+=__INC_VALUE;
    if(ang>__MAX_ANG) ang=__MAX_ANG;
                
    if(ldr_diff <-__DIFF_OFFSET) ang-=__INC_VALUE;
    if(ang<__MIN_ANG) ang=__MIN_ANG;
    
    myServo.write(ang);
    
    delay(__DELAY);
}
