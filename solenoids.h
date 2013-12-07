#ifndef SOLENOIDS_H_
#define SOLENOIDS_H_

#include <arduino.h>

/**
 * Solenoids can pull down a needle so it gets moved into D position.
 * Needles: Left = -100 until -1; Right = 0 until 99.
 */
class Solenoids {
  Solenoids(int pinBP, int solenoidPins[]);

  /** Call whenever the carriage passes the left or right turnmark. */
  void onTurnMark(boolean is_L_carriage, boolean left);

private:
  int needleToSoleniod(int needle);
private:
  int pinBP;
  int pin[16]; //0 until F
  boolean mode2; //mode 2 = right column in support manual
};

#endif
