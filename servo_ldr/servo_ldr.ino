#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup(){
    myServo.attach(PIN_SERVO);
    myServo.write(MIN_ANG);
    ang=MIN_ANG;

    lcd.begin(20,4);
}

void loop(){
    ldrLft = analogRead(PIN_LDR_LFT);
    ldrRght = analogRead(PIN_LDR_RGHT);
    ldr_diff = ldrRght-ldrLft;

    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("ldr1:");
    lcd.setCursor(5,1);
    lcd.print(ldrLft);

    lcd.setCursor(0,2);
    lcd.print("ldr2:");
    lcd.setCursor(5,2);
    lcd.print(ldrRght);
    

    if(ldr_diff > DIFF_OFFSET) ang+=INC_VALUE;
    if(ang>MAX_ANG) ang=MAX_ANG;
                
    if(ldr_diff <-DIFF_OFFSET) ang-=INC_VALUE;
    if(ang<MIN_ANG) ang=MIN_ANG;
    
    myServo.write(ang);
    
    delay(DELAY);
}
