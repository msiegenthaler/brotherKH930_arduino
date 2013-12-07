#ifndef SOLENOIDS_H_
#define SOLENOIDS_H_

#include <arduino.h>

#define SOLENIOD_COUNT  16
#define NEEDLE_COUNT   200
#define NEEDLE_FROM   -100
#define NEEDLE_UNTIL    99


/**
 * Solenoids can pull down a needle so it gets moved into D position.
 */
class Solenoids {
public:
  Solenoids(int pinBP, const int solenoidPins[]);

  /** Call whenever the carriage passes the left or right turnmark. */
  void onTurnmark(boolean is_L_carriage, boolean left);

  /** Call whenever the carriage moves. */
  void onMove(int position, boolean toTheLeft);

  /**
   * Set the value of a needle. True means move to position B, false to position D.
   * Needles: Left = -100 until -1; Right = 0 until 99.
   */
  void needle(int needle, boolean value);

private:
  int needleToSoleniod(int needle);
  boolean patternAt(int needle); //needle does not need to be range checked.
private:
  int pinBP;
  int pin[SOLENIOD_COUNT]; //0 until F
  boolean mode2; //mode 2 = right column in support manual
  boolean pattern[NEEDLE_COUNT];
};

#endif
