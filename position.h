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
  /** Current needle (-128 until +123, refers to the needle number at the middle of the carriage [where the thread is]). */
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
