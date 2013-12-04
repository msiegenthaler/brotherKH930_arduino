#ifndef POSITION_H_
#define POSITION_H_

#import <arduino.h>

enum Direction { LEFT, RIGHT };

/** Responsible to keep track of the carriage position. */
class Position {
public:
  Position(int pinV1, int pinV2, int pinBP);

  /** Carriage movement direction (left = smaller needle numbers). */
  Direction direction();
  /** Current needle (-100 until +151, refers to the needle number at the 'r' in the brother label on the carriage). */
  int position();

public: //pseudo-public (because of ISR), do not use.
  void onV1();
private:
  void updateDirection();
  void moveOneNeedle();
private:
  int pinV1, pinV2, pinBP;
  boolean lastV2;
  int pos;
  Direction dir;
};

#endif
