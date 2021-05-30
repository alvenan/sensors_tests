#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define __LUMINOSITY_PIN 0
#define __TX_PIN 10
#define __RX_PIN 11
#define __SERVO_PIN 13

#define __ZERO 0
#define __MAX_ANG 180

#define __EMPTY_PKG ""

#define __PC_BAUD 115200
#define __BT_BAUD 9600

#define __OFFSET 10

#define __DELAY 50

SoftwareSerial myBluetoothSerial(__TX_PIN, __RX_PIN);
String btPackage;
int luminosity;
int lum_desired;
int auto_flag;
Servo myServo;

void printSerialLog() {
  Serial.print("(");
  Serial.print(luminosity);
  Serial.print(",");
  Serial.print(lum_desired);
  Serial.println(")");
}

int checkSunLight() {
  int lum;
  lum = analogRead(__LUMINOSITY_PIN);
  lum = map(lum, 0, 1023, 0, 99);
  return lum;
}

void setup() {
  Serial.begin(__PC_BAUD);
  myBluetoothSerial.begin(__BT_BAUD);
  btPackage = __EMPTY_PKG;

  myServo.attach(__SERVO_PIN);
  myServo.write(__ZERO);

  lum_desired = 0;
  luminosity = 0;
}

void loop() {
  luminosity = checkSunLight();
  myBluetoothSerial.print("*A" + String(luminosity));

  if (myBluetoothSerial.available()) {
    while (myBluetoothSerial.available()) {
      btPackage += (char)myBluetoothSerial.read();
    }
    Serial.println(btPackage);

    if (btPackage[0] == '*') {
      switch (btPackage[1]) {
        case 'B':
          if (btPackage[3] == '*') {
            if (isDigit(btPackage[2])) {
              btPackage[0] = btPackage[2];
              btPackage[1] = __ZERO;
            }
          }
          if (btPackage[4] == '*') {
            if (isDigit(btPackage[2]) && isDigit(btPackage[3])) {
              btPackage[0] = btPackage[2];
              btPackage[1] = btPackage[3];
              btPackage[2] = __ZERO;
            }
          }
          lum_desired = btPackage.toInt();
          break;
        default:
          break;
      }
    }
  }
  if (luminosity - lum_desired >= __OFFSET) {
    //Luminozidade maior então fecha a cortina
    myServo.write(__ZERO);
  } 
  if (luminosity - lum_desired <= __OFFSET) {
    //Luminozidade menor então abre a cortina
    myServo.write(__MAX_ANG);
  }

  printSerialLog();

  btPackage = __EMPTY_PKG;
  delay(__DELAY);
}