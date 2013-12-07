#include "brotherKH930.h"

PinSetup kniticV2Pins() {
  PinSetup pins;
  pins.encoderV1 = 2;
  pins.encoderV2 = 3;
  pins.encoderBP = 4;
  pins.turnmarkLeft = 0;
  pins.turnmarkRight = 1;
  return pins;
}


void BrotherKH930::positionCallback(void* context, int pos) {
  ((BrotherKH930*)context)->onChange();
  ((BrotherKH930*)context)->tmLeft->update();
  ((BrotherKH930*)context)->tmRight->update();
}

void BrotherKH930::turnmarkCallback(void* context, CarriageType carriage) {
  ((BrotherKH930*)context)->carriage = carriage;
  ((BrotherKH930*)context)->onChange();
}

BrotherKH930::BrotherKH930(const PinSetup pins, void (*callback)(void*), void* context) {
  this->callback = callback;
  this->callbackContext = context;
  noInterrupts();
  tmLeft = new Turnmark(pins.turnmarkLeft, turnmarkCallback, this);
  tmRight = new Turnmark(pins.turnmarkRight, turnmarkCallback, this);
  pos = new Position(pins.encoderV1, pins.encoderV2, pins.encoderBP, positionCallback, this);
  interrupts();
}


int BrotherKH930::position() {
  return pos->position();
}

CarriageType BrotherKH930::carriageType() {
  return carriage;
}

Direction BrotherKH930::direction() {
  return pos->direction();
}

boolean BrotherKH930::isAtLeftMark() {
  return tmLeft->isAtMark();
}

boolean BrotherKH930::isAtRightMark() {
  return tmRight->isAtMark();
}

void BrotherKH930::onChange() {
  callback(callbackContext);
}
