#ifndef POSITION_H_
#define POSITION_H_

#import <arduino.h>

enum Direction { LEFT, RIGHT };

/**
 * Responsible to keep track of the carriage position.
 * The callback will be called on every change of position (inside a ISR).
 */
class Position {
public:
  Position(int pinV1, int pinV2, void (*callback)(void*, int), void* context);
  void start();

  /** Carriage movement direction (left = smaller needle numbers). */
  Direction direction();

  /**
   * Current needle [0, 200).
   * Refers to the needle number at the middle of the carriage (where the thread is). Needles
   * are numbered left to right (yellow 100 is 0, green 1 is 0, green 100 is 199).
   */
  unsigned int needle();

  /**
   * Position of the carriage, 0 is the leftmost needle. In contrast to needle() this value
   *  may become negative or bigger than 199 (because the carriage was a nonzero width).
   */
  int position();

private:
  static void isr_v1();
  void onV1();
private:
  void updateDirection();
  void moveOneNeedle();
private:
  int pinV1, pinV2;
  boolean lastV2;
  int pos;
  Direction dir;
private:
  void (*callback)(void*, int);
  void* callbackContext;
};

#endif
