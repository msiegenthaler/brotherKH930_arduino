#ifndef BROTHERKH930_H_
#define BROTHERKH930_H_

#import "position.h"
#import "turnmark.h"

/** Pins unsed for interfacing with the BrotherKH930. */
struct PinSetup {
  int encoderV1;
  int encoderV2;
  int encoderBP; // belt-phase
  int turnmarkLeft;  //analog
  int turnmarkRight; //analog
};

/** Pin setup as used by the KniticV2 PCB. */
PinSetup kniticV2Pins();

/**
 * Interfact to a brother knitting machine KH930/940.
 * The callback will be called on every event (position/direction change). The
 * callback might be called in a ISR.
 */
class BrotherKH930 {
public:
  BrotherKH930(const PinSetup pins, void (*callback)(void*), void* context);
  void start();

  int position();
  Direction direction();
  boolean isAtLeftMark();
  boolean isAtRightMark();
  CarriageType carriageType();

private:
  static void positionCallback(void* context, int pos);
  static void turnmarkCallback(void* context, CarriageType carriage);
  void onChange();
private:
  Position *pos;
private:
  Turnmark *tmLeft;
  Turnmark *tmRight;
  CarriageType carriage;
private:
  void (*callback)(void*);
  void* callbackContext;
};

#endif
