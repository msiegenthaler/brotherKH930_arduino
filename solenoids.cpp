#include "solenoids.h"

Solenoids::Solenoids(int pinBP, const int solenoidPins[]) {
  this->pinBP = pinBP;
  pinMode(pinBP, INPUT);
  for (int i=0; i<SOLENIOD_COUNT; i++) {
    this->pin[i] = solenoidPins[i];
    pinMode(solenoidPins[i], INPUT);
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
    windowMin = position;
    windowMax = position + SOLENIOD_COUNT;
  } else {
    windowMin = position - SOLENIOD_COUNT;
    windowMax = position;
  }

  //it's ok to go over the max/under the min of needles, patternAt will take care of that
  for (int needle=windowMin; needle<=windowMax; needle++) {
    int soleniod = needleToSoleniod(needle);
    boolean value = patternAt(needle);
    digitalWrite(pin[soleniod], value);
  }
}

int Solenoids::needleToSoleniod(int needle) {
  // See the table on page 7 in the support manual
  int result = (needle + NEEDLE_FROM) % SOLENIOD_COUNT;
  if (mode2) result = (result + (SOLENIOD_COUNT/2)) % SOLENIOD_COUNT;
  return result;
}

boolean Solenoids::patternAt(int needle) {
  int i = needle - NEEDLE_FROM;
  if (i < 0 || i >= NEEDLE_COUNT) return false;
  return pattern[i];
}

void Solenoids::needle(int needle, boolean value) {
  pattern[needle] = value;
}
