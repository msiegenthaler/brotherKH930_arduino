#include "turnmark.h"

#define ANALOG_HIGH 400
#define ANALOG_LOW  100


Turnmark::Turnmark(int pin, void (*callback)(void*, CarriageType), void* context) {
  this->pin = pin;
  this->callback = callback;
  this->callbackContext = context;
  atTurnmark = false;
  for (int i=0; i<3; i++) lastState[i] = INPUT_NEUTRAL;
}

InputState Turnmark::analogToState(int value) {
  if (value >= ANALOG_HIGH) return INPUT_HIGH;
  else if (value >= ANALOG_LOW) return INPUT_NEUTRAL;
  else return INPUT_LOW;
}

void Turnmark::onTurnmark() {
  atTurnmark = true;
  callback(callbackContext, lastCarriageType);
}

void Turnmark::pushState(InputState state) {
  lastState[2] = lastState[1];
  lastState[1] = lastState[0];
  lastState[0] = state;
}

CarriageType Turnmark::carriageType() {
  return lastCarriageType;
}

boolean Turnmark::isAtMark() {
  return atTurnmark;
}

int Turnmark::countStates(InputState state) {
  int count = 0;
  for (int i=0; i<3; i++) {
    if (lastState[i] == state) count++;
  }
  return count;
}

void Turnmark::update() {
  atTurnmark = false;

  int analog = analogRead(pin);
  InputState state = analogToState(analog);

  if (state == INPUT_NEUTRAL && lastState[0] != INPUT_NEUTRAL) {
    int highCount = countStates(INPUT_HIGH);
    int lowCount = countStates(INPUT_LOW);
    if (highCount > 0 && lowCount > 0) {
      lastCarriageType = G_CARRIAGE;
      onTurnmark();
    } else if (highCount > 1) {
      lastCarriageType = K_CARRIAGE;
      onTurnmark();
    } else if (lowCount > 1) {
      lastCarriageType = L_CARRIAGE;
      onTurnmark();
    }
  }

  pushState(state);
}
