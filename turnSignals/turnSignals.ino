#include <Keyboard.h>

//Rotary encoder 0 pin assigment
int clkPin0 = 2;
int dtPin0 = 4;
int swPin0;
int pinLast0;

//rotary encoder 1 pin assigment
int clkPin1 = 3;
int dtPin1 = 5;
int swPin1;
int pinLast1;

//joystick 0 pin assigment
int leftX = A0;
int leftY = A1;

//joystick 1 pin assigment
int rightX = A2;
int rightY = A3;

void setup() {
  
  //Rotary encoder pin setup
  pinMode(clkPin0, INPUT_PULLUP);
  pinMode(dtPin0, INPUT_PULLUP);
  pinMode(clkPin1, INPUT_PULLUP);
  pinMode(dtPin1, INPUT_PULLUP);

  //Joystick pin setup
  pinMode(leftX, INPUT_PULLUP);
  pinMode(leftY, INPUT_PULLUP);
  pinMode(rightX, INPUT_PULLUP);
  pinMode(rightY, INPUT_PULLUP);

  //last rotary encoder state
  pinLast0 = digitalRead(clkPin0);
  pinLast1 = digitalRead(clkPin1);
  
  //interupts for rotary encoders as they required it
  attachInterrupt(digitalPinToInterrupt(clkPin0), rotated0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(clkPin1), rotated1, CHANGE);
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
 * rotated0: executes when rotary encoder state changes. This presses buttons dependig on direction encoder was turn in
 */
void rotated0() {
  
    int clkPinCurrent = digitalRead(clkPin0);
  
    if (clkPinCurrent != pinLast0) {
     if (clkPinCurrent != digitalRead(dtPin0)) {
      //clockwise
      Keyboard.press('.');
     } else {
      //counterClockwise
      Keyboard.press(',');
     }
     pinLast0 = clkPinCurrent;
     delay(10);
     Keyboard.releaseAll();
   }
}

/*
 * rotated1: executes when rotary encoder state changes. This presses buttons dependig on direction encoder was turn in
 */
void rotated1() {
  
    int clkPinCurrent = digitalRead(clkPin1);
  
    if (clkPinCurrent != pinLast1) {
     if (clkPinCurrent != digitalRead(dtPin1)) {
      //clockwise
      Keyboard.press('l');
     } else {
      //counterClockwise
      Keyboard.press('o');
     }
     pinLast1 = clkPinCurrent;
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
