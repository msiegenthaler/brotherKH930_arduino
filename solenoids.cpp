#include "solenoids.h"

Solenoids::Solenoids(int pinBP, const int solenoidPins[]) {
  this->pinBP = pinBP;
  pinMode(pinBP, INPUT);
  for (int i=0; i<SOLENIOD_COUNT; i++) {
    this->pin[i] = solenoidPins[i];
    pinMode(solenoidPins[i], OUTPUT);
  }
  for (int i=0; i<NEEDLE_COUNT; i++) pattern[i] = false;
}

void Solenoids::onTurnmark(boolean is_L_carriage, boolean left) {
  // See the table on page 7 in the support manual
  boolean bp = digitalRead(pinBP) == HIGH;
  if (is_L_carriage) mode2 = !bp; //L and anywhere
  else if (left) mode2 = bp;      //K and left
  else mode2 = !bp;               //K and right
}

void Solenoids::onMove(int position, boolean toTheLeft) {
  //Window of relevant needles
  int windowMax, windowMin;
  if (toTheLeft) {
    windowMin = position + 8;
    windowMax = position + 8 + SOLENIOD_COUNT;
  } else {
    windowMin = position - 8 - SOLENIOD_COUNT;
    windowMax = position - 8;
  }

  //it's ok to go over the max/under the min of needles, patternAt will take care of that
  for (int needle=windowMin; needle<=windowMax; needle++) {
    int soleniod = needleToSoleniod(needle);
    boolean value = patternAt(needle);
    digitalWrite(pin[soleniod], value);
  }
}

int Solenoids::needleToSoleniod(unsigned int needle) {
  // See the table on page 7 in the support manual
  // we number needles from 0 to 200, so left 100 in the manual is zero here
  int result = needle % SOLENIOD_COUNT;
  if (mode2) result = (result + (SOLENIOD_COUNT/2)) % SOLENIOD_COUNT;
  return result;
}

boolean Solenoids::patternAt(unsigned int needle) {
  if (needle < 0 || needle >= NEEDLE_COUNT) return false;
  return pattern[needle];
}

void Solenoids::needle(unsigned int needle, boolean value) {
  pattern[needle] = value;
}
