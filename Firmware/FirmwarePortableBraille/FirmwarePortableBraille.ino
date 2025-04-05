// TreeHacks 2025
// PortableBraille by Adil Jussupov
// Jussupov@stanford.edu

// Define constants for pins for buttons
// mini-ESP32
#define BTN1 21
#define BTN2 19
#define BTN3 18

#define BTN4 16
#define BTN5 5
#define BTN6 23

#define BTN7 33
#define BTN8 17
#define BTN9 26

#define POWERON 4

int datainPin = 32;  //to cell, 'in' from perspective braille cell
int strobePin = 25;  //to cell
int clockPin = 27;   //to cell

unsigned int i;
float delaytime = 0.25;

#include <BleKeyboard.h>.  // library to conver device to BLE HID (Bluetooth keyboard)
#include "brailleconst.h"  // arrays for conversion to Braille

BleKeyboard bleKeyboard;

// variables for multiple buttons pressing
bool hasKeyPressed = false;      // variable for tracking and releasing pressed key
long keyPreviusTime = millis();  // temp var for time
long keyReleasTime = 10;         // time have key pressed

int number = 0;
long previousTime = millis();
long updatePeriod = 50;


#include "GyverButton.h"  // buttons library
GButton butt1(BTN1);
GButton butt2(BTN2);
GButton butt3(BTN3);
GButton butt4(BTN4);
GButton butt5(BTN5);
GButton butt6(BTN6);
GButton buttSpace(BTN7);
GButton buttBSpace(BTN8);
GButton buttEnter(BTN9);

void setup() {

  //pinMode(powerPin, OUTPUT);
  // pinMode(powerPin, OUTPUT);
  // digitalWrite(powerPin, LOW);  // controlpin for DCDC converter (low is on)
  pinMode(datainPin, OUTPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  delay(50);

  Serial.begin(115200);
  Serial.println("Starting BLE connection");
  bleKeyboard.begin();

  pinMode(POWERON, OUTPUT);                     // pin for turning DC-DC converter on
  digitalWrite(POWERON, LOW);                   // turn off DC-DC
  // while (!bleKeyboard.isConnected()) {}  // wait untill bluetooth connected
  // Serial.println("BLE Connected");
}

void loop() {

  // tick every cycle to check buttons
  butt1.tick();
  butt2.tick();
  butt3.tick();
  butt4.tick();
  butt5.tick();
  butt6.tick();
  buttSpace.tick();
  buttBSpace.tick();
  buttEnter.tick();

  // check if button was pressed
  if (butt1.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 0))) {
      number += 1 << 0;
    }

    digitalWrite(strobePin, LOW);  // low for setting data, high for using data
    for (i = 0; i < 64; i++)       //we have five cells of eight pins, so amount is 40
    {
      digitalWrite(clockPin, LOW);  // set clock low before sending value for 1 braille pin
      if ((i % 2) == 0) {
        digitalWrite(datainPin, LOW);
      } else {
        digitalWrite(datainPin, HIGH);
      }
      delay(delaytime);              //delay must be very short
      digitalWrite(clockPin, HIGH);  //set clock low
      delay(delaytime);
    }
    digitalWrite(strobePin, HIGH);  //pattern is set and
  }
  if (butt2.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 1))) {
      number += 1 << 1;
    }

    digitalWrite(strobePin, LOW);  // low for setting, high for using data
    for (i = 0; i < 64; i++) {
      digitalWrite(clockPin, LOW);  // set clock low
      if ((i % 2) == 0)             //odd pins go down, even ones go up
      {
        digitalWrite(datainPin, HIGH);
      } else {
        digitalWrite(datainPin, LOW);
      }
      delay(delaytime);
      digitalWrite(clockPin, HIGH);
      delay(delaytime);
    }
    digitalWrite(strobePin, HIGH);
  }

  if (butt3.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 2))) {
      number += 1 << 2;
    }
    digitalWrite(strobePin, LOW);  // low for setting data, high for using data
    for (i = 0; i < 64; i++)       //we have five cells of eight pins, so amount is 40
    {
      digitalWrite(clockPin, LOW);  // set clock low before sending value for 1 braille pin
      if ((i % 2) == 0) {
        digitalWrite(datainPin, LOW);
      } else {
        digitalWrite(datainPin, HIGH);
      }
      delay(delaytime);              //delay must be very short
      digitalWrite(clockPin, HIGH);  //set clock low
      delay(delaytime);
    }
    digitalWrite(strobePin, HIGH);  //pattern is set and
  }

  if (butt4.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 3))) {
      number += 1 << 3;
    }

    digitalWrite(strobePin, LOW);  // low for setting, high for using data
    for (i = 0; i < 64; i++) {
      digitalWrite(clockPin, LOW);  // set clock low
      if ((i % 2) == 0)             //odd pins go down, even ones go up
      {
        digitalWrite(datainPin, HIGH);
      } else {
        digitalWrite(datainPin, LOW);
      }
      delay(delaytime);
      digitalWrite(clockPin, HIGH);
      delay(delaytime);
    }
    digitalWrite(strobePin, HIGH);
  }

  if (butt5.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 4))) {
      number += 1 << 4;
    }

    digitalWrite(strobePin, LOW);  // low for setting data, high for using data
    for (i = 0; i < 64; i++)       //we have five cells of eight pins, so amount is 40
    {
      digitalWrite(clockPin, LOW);  // set clock low before sending value for 1 braille pin
      if ((i % 2) == 0) {
        digitalWrite(datainPin, LOW);
      } else {
        digitalWrite(datainPin, HIGH);
      }
      delay(delaytime);              //delay must be very short
      digitalWrite(clockPin, HIGH);  //set clock low
      delay(delaytime);
    }
    digitalWrite(strobePin, HIGH);  //pattern is set and
  }

  if (butt6.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 5))) {
      number += 1 << 5;
    }


    digitalWrite(strobePin, LOW);  // low for setting, high for using data
    for (i = 0; i < 64; i++) {
      digitalWrite(clockPin, LOW);  // set clock low
      if ((i % 2) == 0)             //odd pins go down, even ones go up
      {
        digitalWrite(datainPin, HIGH);
      } else {
        digitalWrite(datainPin, LOW);
      }
      delay(delaytime);
      digitalWrite(clockPin, HIGH);
      delay(delaytime);
    }
    digitalWrite(strobePin, HIGH);
  }

  if (buttSpace.isClick()) {
    bleKeyboard.print(" ");
    Serial.print(" ");  // WhiteSpace
    hasKeyPressed = true;
  }
  if (buttEnter.isClick()) {
    bleKeyboard.write(KEY_RETURN);
    Serial.print("\n");
    hasKeyPressed = true;
  }
  if (buttBSpace.isClick()) {
    bleKeyboard.print(" ");
    Serial.print("BackSpace");
    hasKeyPressed = true;
  }

  if (previousTime < (millis() - updatePeriod)) {
    if (number) {
      if (number >= B1000000) {
        // Serial.println("Send text");
      } else {
        // Serial.print(number, BIN);
        // Serial.print(" - ");
        bleKeyboard.print((char)asciiCodes[number]);
        Serial.print((char)asciiCodes[number]);
        // Serial.println(";");
        hasKeyPressed = true;
      }
      number = 0;
      previousTime = millis();
    }
  }

  if (hasKeyPressed) {
    if ((millis() - keyPreviusTime) >= keyReleasTime) {
      hasKeyPressed = false;
    }
  }
  // ///////////////////////////////////////////////////////////





  // ///////////////////////////////////////////////////////////
}
