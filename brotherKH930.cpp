#include "brotherKH930.h"

PinSetup kniticV2Pins() {
  PinSetup pins;
  pins.encoderV1 = 2;
  pins.encoderV2 = 3;
  pins.encoderBP = 4;
  return pins;
}


void BrotherKH930::positionCallback(void* context, int pos) {
  ((BrotherKH930*)context)->onChange();
}

BrotherKH930::BrotherKH930(const PinSetup pins, void (*callback)(void*), void* context) {
  this->callback = callback;
  this->callbackContext = context;
  pos = new Position(pins.encoderV1, pins.encoderV2, pins.encoderBP, positionCallback, this);
}


int BrotherKH930::position() {
  return pos->position();
}

Direction BrotherKH930::direction() {
  return pos->direction();
}

void BrotherKH930::onChange() {
  callback(callbackContext);
}
