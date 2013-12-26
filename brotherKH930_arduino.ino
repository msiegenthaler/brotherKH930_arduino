#include "brotherKH930.h"

PinSetup pins = kniticV2Pins();
BrotherKH930 brother(pins, onChange, 0);

void setup() {
  Serial.begin(115200);
  brother.start();
  Serial.println("Ready.");

  for (int i=0; i<200; i++)
    brother.needle(0, false);
}

boolean changed = true;

void onChange(void* c) {
  changed = true;
}

void loop() {
  if (changed) {
    changed = false;

    Serial.print("@");
    Serial.print("\t");

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
    Serial.print("\t");

    if (brother.carriagePosition() == LEFT_OUTSIDE) Serial.print("<");
    else if (brother.carriagePosition() == RIGHT_OUTSIDE) Serial.print(">");
    else Serial.print("_");
    Serial.print("\t");

    if (brother.isAtLeftMark()) Serial.print(" at L");
    else if (brother.isAtRightMark()) Serial.print(" at R");
    else Serial.print("     ");
    Serial.println();
  }

  readInput();
}


#define MAX_LENGTH 255
byte buffer[MAX_LENGTH];
int pos = 0;

void readInput() {
  int in = Serial.read();
  if (in >= 0) {
    if (in == '\n') {
      if (pos > 0) {
        handleLine(buffer, pos);
        pos = 0;
      } // else ignore (empty line)
    } else if (in == '\r') {
      //skip \r
    } else {
      buffer[pos++] = in;
    }
    if (pos >= MAX_LENGTH) {
      //Throw away the buffer if line length is exceeded
      pos = 0;
    }
  }
}

void handleLine(byte* buffer, int len) {
  if (len == 0) return;

  if (len > 4 && buffer[0] == '$' && buffer[1] == '\t' && buffer[2] == '>' && buffer[3] == '\t') {
    for (int i=4,n=0; i<len; i++, n++) {
      if (buffer[i] == '1') brother.needle(n, true);
      else if (buffer[i] == '0') brother.needle(n, false);
    }
    Serial.print("$\t<\t");
    Serial.write(&buffer[4], len-4);
    Serial.println('\n');
  } else {
    Serial.print("*\tInvalid input");
    Serial.write(buffer, len);
    Serial.println();
  }
}
