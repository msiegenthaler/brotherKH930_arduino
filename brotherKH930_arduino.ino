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

    Serial.print(",");
    Serial.print(227 - brother.position());

    Serial.print(",");
    if (brother.direction() == LEFT) Serial.print("1");
    else Serial.print("-1");

    Serial.println(",0@");
  }

  readInput();
}


#define MAX_LENGTH 255
byte buffer[MAX_LENGTH];
int pos = 0;

void readInput() {
  int in = Serial.read();
  if (in >= 0) {
    if (in == 126 || in == '\n') {
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

  if (buffer[0] == 1 || buffer[0] == 0) {
    for (int i=1; i<len; i++) {
      if (buffer[i] == 1) brother.needle(199-i, true);
      else if (buffer[i] == 0) brother.needle(199-i, false);
      Serial.print(String(buffer[i]));
    }
    Serial.println("@");
  } else {
    Serial.print("* Ignored input: ");
    Serial.write(buffer, len);
    Serial.println("@");
  }
}
