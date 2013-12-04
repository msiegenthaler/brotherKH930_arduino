#include "brotherKH930.h"

PinSetup kniticV2Pins() {
  PinSetup pins;
  pins.encoderV1 = 2;
  pins.encoderV2 = 3;
  pins.encoderBP = 4;
  return pins;
}


BrotherKH930::BrotherKH930(const PinSetup pins) {
  pos = new Position(pins.encoderV1, pins.encoderV2, pins.encoderBP);
}

int BrotherKH930::position() {
  return pos->position();
}

Direction BrotherKH930::direction() {
  return pos->direction();
}
