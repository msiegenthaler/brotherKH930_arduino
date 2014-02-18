#include <arduino.h>
#include "position.h"

#define NEEDLE_COUNT 200
#define BP_PHASE 16
#define BP_PHASE_HALF 8

// Redirects the ISR to the class method.
Position *isr_pos;
void Position::isr_v1() { isr_pos->onV1(); }

Position::Position(int pinV1, int pinV2, int pinBP, void (*callback)(void*, int), void* context) {
  this->pinV1 = pinV1;
  pinMode(pinV1, INPUT);
  this->pinV2 = pinV2;
  pinMode(pinV2, INPUT);
  this->pinBP = pinBP;
  pinMode(pinBP, INPUT);
  this->callback = callback;
  this->callbackContext = context;
  isr_pos = this;

  //default to left to right
  pos = -50;
  dir = RIGHT;
  lastV2 = LOW;
  distanceBP = 0;
  lastBP = false;
  bpCalibrated = false;
}

void Position::start() {
  attachInterrupt(pinV1, isr_v1, CHANGE);
}

Direction Position::direction() {
  return dir;
}

unsigned int Position::needle() {
  return min(NEEDLE_COUNT-1, max(0, pos));
}

int Position::position() {
  return pos;
}

void Position::setPosition(int p) {
  pos = p;
}

void Position::onV1() { // called by ISR
  //make sure that v2 changed its value as well. Otherwise it might just be an unstable state.
  boolean v2value = digitalRead(pinV2);
  if (lastV2 == v2value)
    return;
  lastV2 = v2value;

  updateDirection();
  if (v2value == HIGH) {
    moveOneNeedle();
    callback(callbackContext, pos);
  }
}

void Position::updateDirection() {
  if (digitalRead(pinV1) == digitalRead(pinV2)) dir = LEFT;
  else dir = RIGHT;
}

int normalize(int distance) {
  while (distance >= BP_PHASE) distance -= BP_PHASE;
  while (distance < 0) distance += BP_PHASE;
  return distance;
}

void Position::moveOneNeedle() { // in direction, so call updateDirection first
  if (dir == LEFT) {
    pos--;
    distanceBP = normalize(distanceBP - 1);
  } else {
    pos++;
    distanceBP = normalize(distanceBP + 1);
  }

  //Adjustment for skipped needles and detection errors using the
  // Belt, that is switched on/off in 8 needle intervals.
  boolean bp = digitalRead(pinBP);
  if (bp != lastBP) {
    boolean raising = (dir == LEFT) ^ bp;
    if (!raising) {
      // shift by half a phase on falling (left) edge.
      distanceBP = normalize(distanceBP + BP_PHASE_HALF);
    }

    int adjust = 0;
    if (dir == LEFT) {
      //adjust by one because detection will trigger one needle leftwards
      adjust = 1;
      distanceBP = normalize(distanceBP + adjust);
    }

    int delta;
    if (distanceBP <= BP_PHASE_HALF) delta = distanceBP;
    else delta = -16 + distanceBP;

    if (bpCalibrated) {
      //Adjust position, but only after an initial calibration phase.
      pos -= delta;
    } else {
      bpCalibrated = true;
    }

    lastBP = bp;
    distanceBP = normalize(-adjust);
    if (!raising) distanceBP = normalize(distanceBP + BP_PHASE_HALF);
  }
}
