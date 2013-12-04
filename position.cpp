#include <arduino.h>
#include "position.h"

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

  pos = -100; //carriage always starts at the left
  dir = RIGHT;

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
  updateDirection();
  if (digitalRead(pinV2) == HIGH) moveOneNeedle();
}

void Position::updateDirection() {
  if (digitalRead(pinV1) == digitalRead(pinV2)) dir = LEFT;
  else dir = RIGHT;
}

void Position::moveOneNeedle() { // in direction, so call updateDirection first
  if (dir == LEFT) pos = max(-100, pos-1);
  else pos = min(100, pos + 1);
}
