#include "brotherKH930.h"

PinSetup pins = kniticV2Pins();
BrotherKH930 brother(pins);

void setup() {
  Serial.begin(115200);
  Serial.println("Ready.");
}

void loop() {
  Direction dir = brother.direction();
  int pos = brother.position();

  Serial.print("@");
  Serial.print(pos);
  Serial.print("  ");
  if (dir == LEFT) Serial.print("<-");
  else Serial.print("->");
  Serial.println();
}
