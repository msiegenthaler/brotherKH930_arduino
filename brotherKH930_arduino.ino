#include "brotherKH930.h"
#include "turnmark.h"

PinSetup pins = kniticV2Pins();
BrotherKH930 brother(pins, onChange, 0);

void setup() {
  Serial.begin(115200);
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
    int pos = brother.position();

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
    if (brother.tmLeft->isAtMark()) Serial.print(" at L");
    else if (brother.tmRight->isAtMark()) Serial.print(" at R");
    else Serial.print("     ");

    //Serial.println();

    Serial.print("              TM left states: ");
    for (int i=0; i<3; i++) {
      Serial.print(brother.tmLeft->lastState[i]);
      Serial.print(" ");
    }
    Serial.print("              TM right states: ");
    for (int i=0; i<3; i++) {
      Serial.print(brother.tmRight->lastState[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}
