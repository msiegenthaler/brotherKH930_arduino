Brother KH930 Arduino
=====================

Interface to a Brother KH930 knitting machine via an Arduino Due.

Features
--------
* Get the position of carriage over the needles (which needle is at the center of the carriage).
* Detection of carriage type (K, L or G).
* Access the needles and control whether they move to B or to D position (pattern knitting).


Getting Started
---------------
* Study the brotherKH930.h file.
* To initialize use

        PinSetup pins = kniticV2Pins();
        BrotherKH930 brother(pins, onChange, 0);

        void setup() {
          brother.start();
        }

        void onChange(void*) {
          //is called whenever the state of the knitting machine changes
          //  i.e. when the carriage is moved.
        }


References
----------
Based on the work by knitic.com. Technical information is from the
[Brother Service Manual](https://github.com/msiegenthaler/knitting/blob/master/Manuals/Technical/Service%20Manual%20KH930%20incl.%20KG89II.pdf).
