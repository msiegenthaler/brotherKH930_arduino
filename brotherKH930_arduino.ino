#include "brotherKH930.h"
#include "turnmark.h"

PinSetup pins = kniticV2Pins();
BrotherKH930 brother(pins, onChange, 0);

void setup() {
  Serial.begin(115200);
  Serial.println("Ready.");
  delay(200);
}

boolean changed = true;

void onChange(void* c) {
  changed = true;
}

void loop() {
  if (changed) {
    changed = false;

    Direction dir = brother.direction();
    int pos = brother.position();

    Serial.print("@");
    Serial.print(pos);
    Serial.print("  ");
    if (dir == LEFT) Serial.print("<-");
    else Serial.print("->");
    Serial.println();
  }
}
