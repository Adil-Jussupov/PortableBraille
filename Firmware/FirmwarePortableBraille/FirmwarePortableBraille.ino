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

#include "GyverButton.h" // buttons library
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
  Serial.begin(9600);
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
  if (butt1.isClick()) Serial.println("1");
  if (butt2.isClick()) Serial.println("2");
  if (butt3.isClick()) Serial.println("3");
  if (butt4.isClick()) Serial.println("4");
  if (butt5.isClick()) Serial.println("5");
  if (butt6.isClick()) Serial.println("6");
  if (buttSpace.isClick()) Serial.println("Space");
  if (buttBSpace.isClick()) Serial.println("BackSpace");
  if (buttEnter.isClick()) Serial.println("Enter");
}
