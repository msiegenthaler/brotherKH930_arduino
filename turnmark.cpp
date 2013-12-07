#include "turnmark.h"

#define ANALOG_HIGH 400
#define ANALOG_LOW  100


Turnmark::Turnmark(int pin, void (*callback)(void*, CarriageType), void* context) {
  this->pin = pin;
  this->callback = callback;
  this->callbackContext = context;
  atTurnmark = false;
  overTurnmark = false;
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

boolean Turnmark::checkState(InputState a, InputState b, InputState c) {
  return (lastState[0] == a) && (lastState[1] == b) && (lastState[2] == c);
}

void Turnmark::update() {
  atTurnmark = false;

  int analog = analogRead(pin);
  InputState state = analogToState(analog);
  pushState(state);

  boolean overBefore = overTurnmark;
  if (checkState(INPUT_HIGH, INPUT_HIGH, INPUT_NEUTRAL) || checkState(INPUT_NEUTRAL, INPUT_HIGH, INPUT_HIGH) || checkState(INPUT_HIGH, INPUT_HIGH, INPUT_HIGH)) {
     lastCarriageType = K_CARRIAGE;
     overTurnmark = true;
  } else if (checkState(INPUT_LOW, INPUT_LOW, INPUT_NEUTRAL) || checkState(INPUT_NEUTRAL, INPUT_LOW, INPUT_LOW) || checkState(INPUT_LOW, INPUT_LOW, INPUT_LOW)) {
     lastCarriageType = L_CARRIAGE;
     overTurnmark = true;
  } else if (checkState(INPUT_LOW, INPUT_NEUTRAL, INPUT_HIGH) || checkState(INPUT_HIGH, INPUT_NEUTRAL, INPUT_LOW) || checkState(INPUT_HIGH, INPUT_HIGH, INPUT_LOW) || checkState(INPUT_HIGH, INPUT_LOW, INPUT_LOW)) {
     lastCarriageType = G_CARRIAGE;
     overTurnmark = true;
  } else overTurnmark = false;
  
  if (!overBefore && overTurnmark) onTurnmark();
}
