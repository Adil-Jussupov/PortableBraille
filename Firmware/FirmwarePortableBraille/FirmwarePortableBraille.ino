// TreeHacks 2025
// PortableBraille by Adil Jussupov
// Jussupov@stanford.edu

// Define constants for pins for buttons
// mini-ESP32
#define BTN1 33
#define BTN2 19
#define BTN3 5

#define BTN4 21
#define BTN5 17
#define BTN6 16

#define BTN7 23
#define BTN8 26
#define BTN9 18

#define POWERON 4


#include <BleKeyboard.h>.  // library to conver device to BLE HID (Bluetooth keyboard)
#include "brailleconst.h"  // arrays for conversion to Braille

BleKeyboard blePortableBraille ("PortableBraille", "TreeHacks2025", 69);;

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
  Serial.begin(115200);
  Serial.println("Starting BLE connection");
  blePortableBraille.begin();

  pinMode(POWERON, OUTPUT);  // pin for turning DC-DC converter on
  digitalWrite(POWERON, HIGH); // turn off DC-DC
  while (!blePortableBraille.isConnected()) {} // wait untill bluetooth connected
  Serial.println("BLE Connected");
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
  }
  if (butt2.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 1))) {
      number += 1 << 1;
    }
  }

  if (butt3.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 2))) {
      number += 1 << 2;
    }
  }

  if (butt4.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 3))) {
      number += 1 << 3;
    }
  }

  if (butt5.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 4))) {
      number += 1 << 4;
    }
  }

  if (butt6.isClick()) {
    if (!number) previousTime = millis();
    if (!(number & (1 << 5))) {
      number += 1 << 5;
    }
  }

  if (buttSpace.isClick()) {
    blePortableBraille.print(" ");
    Serial.print(" ");  // WhiteSpace
    hasKeyPressed = true;
  }
  if (buttEnter.isClick()) {
    blePortableBraille.write(KEY_RETURN);
    Serial.print("Enter");
    hasKeyPressed = true;
  }
  if (buttBSpace.isClick()) {
    blePortableBraille.print(" ");
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
        blePortableBraille.print((char)asciiCodes[number]);
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
}
