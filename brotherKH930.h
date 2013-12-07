#ifndef BROTHERKH930_H_
#define BROTHERKH930_H_

#import "position.h"

/** Pins unsed for interfacing with the BrotherKH930. */
struct PinSetup {
  int encoderV1;
  int encoderV2;
  int encoderBP; // belt-phase
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

  int position();
  Direction direction();

private:
  static void positionCallback(void* context, int pos);
  void onChange();
private:
  Position *pos;
private:
  void (*callback)(void*);
  void* callbackContext;
};

#endif
