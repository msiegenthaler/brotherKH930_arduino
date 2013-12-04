#include <arduino.h>
#include "position.h"

#define START -123
#define END   128

// Redirects the ISR to the class method.
Position *isr_pos;
void isr_v1() { isr_pos->onV1(); }

Position::Position(int pinV1, int pinV2, int pinBP) {
  this->pinV1 = pinV1;
  pinMode(pinV1, INPUT);
  this->pinV2 = pinV2;
  pinMode(pinV2, INPUT);
  this->pinBP = pinBP;
  pinMode(pinBP, INPUT);

  pos = START; //carriage always starts at the left
  dir = RIGHT;
  lastV2 = LOW;

  isr_pos = this;
  attachInterrupt(pinV1, isr_v1, CHANGE);
}

Direction Position::direction() {
  return dir;
}

int Position::position() {
  return pos;
}

void Position::onV1() { // called by ISR
  //make sure that v2 changed its value as well. Otherwise it might just be an unstable state.
  boolean v2value = digitalRead(pinV2);
  if (lastV2 == v2value)
    return;
  lastV2 = v2value;

  updateDirection();
  if (v2value == HIGH) moveOneNeedle();
}

void Position::updateDirection() {
  if (digitalRead(pinV1) == digitalRead(pinV2)) dir = LEFT;
  else dir = RIGHT;
}

void Position::moveOneNeedle() { // in direction, so call updateDirection first
  if (dir == LEFT) pos = max(START, pos-1);
  else pos = min(END, pos + 1);
}
