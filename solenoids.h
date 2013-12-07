#ifndef SOLENOIDS_H_
#define SOLENOIDS_H_

#include <arduino.h>

/**
 * Solenoids can pull down a needle so it gets moved into D position.
 */
class Solenoids {
public:
  Solenoids(int pinBP, const int solenoidPins[]);

  /** Call whenever the carriage passes the left or right turnmark. */
  void onTurnmark(boolean is_L_carriage, boolean left);

  /**
   * Set the value of a needle. True means move to position B, false to position D.
   * Needles: Left = -100 until -1; Right = 0 until 99.
   */
  void needle(int needle, boolean value);

private:
  int needleToSoleniod(int needle);
private:
  int pinBP;
  int pin[16]; //0 until F
  boolean mode2; //mode 2 = right column in support manual
  boolean pattern[200];
};

#endif
