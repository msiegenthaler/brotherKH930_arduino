#include "brotherKH930.h"

// Number of needles the turnpoint needs to detect a passing carriage
#define TP_DETECTION_DELAY_LEFT 1
#define TP_DETECTION_DELAY_RIGHT 3

PinSetup kniticV2Pins() {
  PinSetup pins;
  pins.encoderV1 = 2;
  pins.encoderV2 = 3;
  pins.beltPhase = 4;
  pins.turnmarkLeft = 0;
  pins.turnmarkRight = 1;
  int sps[] = { 23,25,27,29,31,33,35,37,36,34,32,30,28,26,24,22 };
  for (int i=0; i<SOLENIOD_COUNT; i++)
    pins.solenoids[i] = sps[i];
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

unsigned int BrotherKH930::needle() {
  return pos->needle();
}

int BrotherKH930::position() {
  return pos->position();
}

CarriageType BrotherKH930::carriageType() {
  return carriage;
}

CarriagePosition BrotherKH930::carriagePosition() {
  int p = pos->position();
  if (p < 0) return LEFT_OUTSIDE;
  else if (p >= NEEDLE_COUNT) return RIGHT_OUTSIDE;
  else return OVER_NEEDLES;
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

void BrotherKH930::setPattern(boolean value[]) {
  for (int i=0; i<200; i++) {
    solenoids->needle(i, value[i]);
  }
}

void BrotherKH930::needle(unsigned int needle, boolean value) {
  solenoids->needle(needle, value);
}

void BrotherKH930::onPositionChange() {
  tmLeft->update();
  tmRight->update();
  solenoids->onMove(pos->position(), direction() == LEFT);
  callback(callbackContext);
}

void BrotherKH930::onTurnmark(boolean left, CarriageType carriage) {
  int newPos;
  if (left) newPos = 0;
  else newPos = NEEDLE_COUNT - 1;
  if (pos->direction() == LEFT) newPos -= TP_DETECTION_DELAY_LEFT;
  else newPos += TP_DETECTION_DELAY_RIGHT;
  pos->setPosition(newPos);

  this->carriage = carriage;
  solenoids->onTurnmark(carriage == L_CARRIAGE, left);
  callback(callbackContext);
}
