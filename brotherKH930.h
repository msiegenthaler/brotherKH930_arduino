#ifndef BROTHERKH930_H_
#define BROTHERKH930_H_

#import "position.h"
#import "turnmark.h"
#import "solenoids.h"

/** Pins used to interface with the BrotherKH930. */
struct PinSetup {
  int encoderV1;
  int encoderV2;
  int beltPhase;
  int turnmarkLeft;  //analog
  int turnmarkRight; //analog
  int solenoids[16]; //0 until F
};

/** Pin setup as used by the KniticV2 PCB. */
PinSetup kniticV2Pins();

/**
 * Interfact to a brother knitting machine KH930/940.
 * The callback will be called on every event (position/direction change). The
 * callback might be called in a ISR.
 * Needles are numbered left to right (yellow 100 is 0, green 1 is 0, green 100 is 199).
 */
class BrotherKH930 {
public:
  BrotherKH930(const PinSetup pins, void (*callback)(void*), void* context);
  void start();

  /** Needle number at the middle of the carriage (where the thread is). */
  unsigned int needle();
  Direction direction();
  boolean isAtLeftMark();
  boolean isAtRightMark();
  CarriageType carriageType();

  /**
   * Set the stiching pattern (array of 200 elements).
   * True means move to position B, false to position D.
   */
  void setPattern(boolean value[]);
  /** Set the value of a needle. True means move to position B, false to position D. */
  void needle(unsigned int needle, boolean value);

private:
  static void positionCallback(void* context, int pos);
  static void turnmarkLCallback(void* context, CarriageType carriage);
  static void turnmarkRCallback(void* context, CarriageType carriage);
  void onPositionChange();
  void onTurnmark(boolean left, CarriageType carriage);
private:
  Position *pos;
  Turnmark *tmLeft;
  Turnmark *tmRight;
  Solenoids *solenoids;
private:
  CarriageType carriage;
private:
  void (*callback)(void*);
  void* callbackContext;
};

#endif
