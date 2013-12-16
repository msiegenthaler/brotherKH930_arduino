#include "brotherKH930.h"

void * operator new(size_t size);
void * operator new(size_t size) {
   return malloc(size);
}

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

    Serial.print("@");
    Serial.print(brother.needle());
    Serial.print("\t");

    Serial.print(brother.position());
    Serial.print("\t");

    if (brother.direction() == LEFT) Serial.print("<-");
    else Serial.print("->");
    Serial.print("\t");

    if (brother.carriageType() == K_CARRIAGE) Serial.print("K");
    else if (brother.carriageType() == G_CARRIAGE) Serial.print("G");
    else if (brother.carriageType() == L_CARRIAGE) Serial.print("L");
    else Serial.print("?");
    Serial.print(" ");

    if (brother.carriagePosition() == LEFT_OUTSIDE) Serial.print("<");
    else if (brother.carriagePosition() == RIGHT_OUTSIDE) Serial.print(">");
    else Serial.print("_");
    Serial.print("\t");

    if (brother.isAtLeftMark()) Serial.print(" at L");
    else if (brother.isAtRightMark()) Serial.print(" at R");
    else Serial.print("     ");
    Serial.println();
  }
}
