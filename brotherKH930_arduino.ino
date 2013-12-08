#include "brotherKH930.h"

PinSetup pins = kniticV2Pins();
BrotherKH930 brother(pins, onChange, 0);

void setup() {
  Serial.begin(115200);
  brother.start();
  Serial.println("Ready.");
}

boolean changed = true;

void onChange(void* c) {
  changed = true;
}

void loop() {
  if (changed) {
    changed = false;

    Direction dir = brother.direction();
    int pos = brother.needle();

    Serial.print("@");
    Serial.print(pos);
    Serial.print("  ");

    if (dir == LEFT) Serial.print("<-");
    else Serial.print("->");
    Serial.print(" ");

    if (brother.carriageType() == K_CARRIAGE) Serial.print("K");
    else if (brother.carriageType() == G_CARRIAGE) Serial.print("G");
    else if (brother.carriageType() == L_CARRIAGE) Serial.print("L");
    else Serial.print("Unknown");
    if (brother.isAtLeftMark()) Serial.print(" at L");
    else if (brother.isAtRightMark()) Serial.print(" at R");
    else Serial.print("     ");
    Serial.println();
  }
}
