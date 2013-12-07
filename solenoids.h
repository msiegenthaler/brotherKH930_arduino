#ifndef SOLENOIDS_H_
#define SOLENOIDS_H_

#include <arduino.h>

#define SOLENIOD_COUNT  16
#define NEEDLE_COUNT   200

/**
 * Solenoids can pull down a needle so it gets moved into D position.
 */
class Solenoids {
public:
  Solenoids(int pinBP, const int solenoidPins[]);

  /** Call whenever the carriage passes the left or right turnmark. */
  void onTurnmark(boolean is_L_carriage, boolean left);

  /** Call whenever the carriage moves. Position is zero based. */
  void onMove(unsigned int position, boolean toTheLeft);

  /**
   * Set the value of a needle. True means move to position B, false to position D.
   * Needles: Leftmost = 0.
   */
  void needle(unsigned int needle, boolean value);

private:
  int needleToSoleniod(unsigned int needle);
  boolean patternAt(unsigned int needle); //needle does not need to be range checked.
private:
  int pinBP;
  int pin[SOLENIOD_COUNT]; //0 until F
  boolean mode2; //mode 2 = right column in support manual
  boolean pattern[NEEDLE_COUNT];
};

#endif
