#include <Keyboard.h>

//left encoder pin assigment
int leftClkPin = 3;
int leftDtPin = 5;
int leftSwPin;
int leftPinLast;

//right rotary encoder pin assigment
int rightClkPin = 2;
int rightDtPin = 4;
int rightSwPin;
int rightPinLast;

//left joystick pin assigment
int leftX = A0;
int leftY = A1;

//right joystick pin assigment
int rightX = A2;
int rightY = A3;

void setup() {
  
  //Rotary encoder pin setup
  pinMode(leftClkPin, INPUT_PULLUP);
  pinMode(leftDtPin, INPUT_PULLUP);
  pinMode(rightClkPin, INPUT_PULLUP);
  pinMode(rightDtPin, INPUT_PULLUP);

  //Joystick pin setup
  pinMode(leftX, INPUT_PULLUP);
  pinMode(leftY, INPUT_PULLUP);
  pinMode(rightX, INPUT_PULLUP);
  pinMode(rightY, INPUT_PULLUP);

  //last rotary encoder state
  leftPinLast = digitalRead(leftClkPin);
  rightPinLast = digitalRead(rightClkPin);
  
  //interupts for rotary encoders as they required it
  attachInterrupt(digitalPinToInterrupt(leftClkPin), rotatedLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightClkPin), rotatedRight, CHANGE);
}

void loop() {
  //register clicks form joysticks's axis 
  registerClick(analogRead(leftX), 'k', 'j');
  registerClick(analogRead(leftY), '[', ']');
  registerClick(analogRead(rightX), 'b', ' ');
  registerClick(analogRead(rightY), 'i', 'p');

  delay(200);
}

/*
 * rotatedLeft: executes when left rotary encoder state changes. This presses buttons dependig on direction encoder was turn in
 */
void rotatedLeft() {
  
    int clkPinCurrent = digitalRead(leftClkPin);
  
    if (clkPinCurrent != leftPinLast) {
     if (clkPinCurrent != digitalRead(leftDtPin)) {
      //clockwise
      Keyboard.press('l');
     } else {
      //counterClockwise
      Keyboard.press('o');
     }
     leftPinLast = clkPinCurrent;
     delay(10);
     Keyboard.releaseAll();
   }
}

/*
 * rotatedRight: executes when right rotary encoder state changes. This presses buttons dependig on direction encoder was turn in
 */
void rotatedRight() {
  
    int clkPinCurrent = digitalRead(rightClkPin);
  
    if (clkPinCurrent != rightPinLast) {
     if (clkPinCurrent != digitalRead(rightDtPin)) {
      //clockwise
      Keyboard.press('.');
     } else {
      //counterClockwise
      Keyboard.press(',');
     }
     rightPinLast = clkPinCurrent;
     delay(10);
     Keyboard.releaseAll();
   }
}

/*
 * registerClick: check given axis and register click if it occurs
 * int axisIn: axis that checks
 * char buttonA: button to be "pressed" 
 * char buttonB: second button to be "pressed"
 */
void registerClick(int axisIn, char buttonA, char buttonB) {

  if (axisIn > 923) {
      //register click
      Keyboard.press(buttonA);

  } else if (axisIn < 100) {
      //register click
      Keyboard.press(buttonB);
    
  } else if (axisIn > 100 && axisIn < 923) {
    
    Keyboard.release(buttonA);
    Keyboard.release(buttonB);
    
  }
  
}
