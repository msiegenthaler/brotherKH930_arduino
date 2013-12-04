#ifndef BROTHERKH930_H_
#define BROTHERKH930_H_

/** Pins unsed for interfacing with the BrotherKH930. */
struct PinSetup {
  int encoderV1;
  int encoderV2;
  int encoderBP; // belt-phase
};

/** Pin setup as used by the KniticV2 PCB. */
PinSetup kniticV2Pins();

/** Interfact to a brother knitting machine KH930/940. */
class BrotherKH930 {
public:
  BrotherKH930(PinSetup pins);
};

#endif
