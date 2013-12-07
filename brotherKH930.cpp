#include "brotherKH930.h"

PinSetup kniticV2Pins() {
  PinSetup pins;
  pins.encoderV1 = 2;
  pins.encoderV2 = 3;
  pins.beltPhase = 4;
  pins.turnmarkLeft = 0;
  pins.turnmarkRight = 1;
  pins.solenoids = { 22,24,26,28,30,32,34,36,37,35,33,31,29,27,25,23 };
  return pins;
}


void BrotherKH930::positionCallback(void* context, int pos) {
  ((BrotherKH930*)context)->onPositionChange();
}

void BrotherKH930::turnmarkLCallback(void* context, CarriageType carriage) {
  ((BrotherKH930*)context)->onTurnmark(true, carriage);
}
void BrotherKH930::turnmarkRCallback(void* context, CarriageType carriage) {
  ((BrotherKH930*)context)->onTurnmark(false, carriage);
}

BrotherKH930::BrotherKH930(const PinSetup pins, void (*callback)(void*), void* context) {
  this->callback = callback;
  this->callbackContext = context;
  tmLeft = new Turnmark(pins.turnmarkLeft, turnmarkLCallback, this);
  tmRight = new Turnmark(pins.turnmarkRight, turnmarkRCallback, this);
  pos = new Position(pins.encoderV1, pins.encoderV2, positionCallback, this);
  solenoids = new Solenoids(pins.beltPhase, pins.solenoids);
}

void BrotherKH930::start() {
  pos->start();
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

void BrotherKH930::onPositionChange() {
  tmLeft->update();
  tmRight->update();
  solenoids->onMove(position(), direction() == LEFT);
  callback(callbackContext);
}

void BrotherKH930::onTurnmark(boolean left, CarriageType carriage) {
  this->carriage = carriage;
  solenoids->onTurnmark(carriage == L_CARRIAGE, left);
  callback(callbackContext);
}
