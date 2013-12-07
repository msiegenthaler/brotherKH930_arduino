#include "solenoids.h"

Solenoids::Solenoids(int pinBP, const int solenoidPins[]) {
  this->pinBP = pinBP;
  pinMode(pinBP, INPUT);
  for (int i=0; i<16; i++) {
    this->pin[i] = solenoidPins[i];
    pinMode(solenoidPins[i], INPUT);
  }
  for (int i=0; i<200; i++) pattern[i] = false;
}

void Solenoids::onTurnmark(boolean is_L_carriage, boolean left) {
  // See the table on page 7 in the support manual
  boolean bp = digitalRead(pinBP) == HIGH;
  if (is_L_carriage) mode2 = !bp; //L and anywhere
  else if (left) mode2 = bp;      //K and left
  else mode2 = !bp;               //K and right
}

int Solenoids::needleToSoleniod(int needle) {
  // See the table on page 7 in the support manual
  int result = (needle + 100) % 16;
  if (mode2) result = (result + 8) % 16;
  return result;
}

void Solenoids::needle(int needle, boolean value) {
  pattern[needle] = value;
}