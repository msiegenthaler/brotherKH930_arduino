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

  this->pos = -100; //carriage always starts at the left

  attachInterrupt(pinV1, isr_v1, CHANGE);
}

void Position::onV1() { // called by ISR
  updateDirection();
  if (digitalRead(pinV2) == HIGH) moveOneNeedle();
}

void Position::updateDirection() {
  if (digitalRead(pinV1) == digitalRead(pinV2)) direction = Left;
  else direction = Right;
}

void Position::moveOneNeedle() { // in direction, so call updateDirection first
  if (direction == Left) pos = max(-100, pos-1);
  else pos = min(100, pos + 1);
}
