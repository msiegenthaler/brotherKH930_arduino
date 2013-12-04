#include "brotherKH930.h"

PinSetup pins = kniticV2Pins();
BrotherKH930 brother(pins);

void setup() {
  Serial.begin(115200);
  Serial.println("Ready.");
}

int old_pos = 0;

void loop() {
  Direction dir = brother.direction();
  int pos = brother.position();

  if (old_pos != pos) {
    old_pos = pos;
    Serial.print("@");
    Serial.print(pos);
    Serial.print("  ");
    if (dir == LEFT) Serial.print("<-");
    else Serial.print("->");
    Serial.println();
  }

  delay(30);
}
