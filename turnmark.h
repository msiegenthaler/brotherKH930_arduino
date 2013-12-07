#ifndef TURNMARK_H_
#define TURNMARK_H_

#include <arduino.h>

enum CarriageType { K_CARRIAGE, G_CARRIAGE, L_CARRIAGE };

enum InputState { INPUT_LOW, INPUT_NEUTRAL, INPUT_HIGH  };

/**
 * Handles turnmarks (left or right) signals and detects the type of carriage
 * passing the turnmark.
 * Calls the callback every time the turnmark is passed.
 */
class Turnmark {
public:
  Turnmark(int pin, void (*callback)(void*, CarriageType), void* context);
  
  /** Must be called every time the carriage moves. */
  void update();

  /** Type of carriage detected last. */
  CarriageType carriageType();
  
  /** True if the carriage is currently positioned is at this turnmark. */
  boolean isAtMark();

private:
  InputState analogToState(int value);
  void onTurnmark();
  void pushState(InputState state);
  /** Count of the state within lastState. */
  int countStates(InputState state);
private:
  int pin;
  InputState lastState[3]; // 3 last changes, newest first
  boolean atTurnmark;
  CarriageType lastCarriageType;
private:
  void (*callback)(void*, CarriageType);
  void* callbackContext;
};

#endif
