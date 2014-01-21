Brother KH930 Arduino
=====================

Interface to a Brother KH930 knitting machine via an Arduino Due and using [Knitic](http://knitic.com) pcb shield.

Features
--------
* Get the position of carriage over the needles (which needle is at the center of the carriage).
* Detection of carriage type (K, L or G).
* Access the needles and control whether they move to B or to D position (pattern knitting).


Getting Started
---------------
* Install
    * Checkout this project.

    * Create a new Folder BrotherKH930 in ~/Documents/Ardunio/libraries (on a Mac, adapt for other OS).

    * Copy all files from the checkout into the folder

* Study the brotherKH930.h file for an overview about the provided functionality.
  Short summary:
    * _CarriagePosition carriagePosition()_  
      Where the carriage is: LEFT_OUTSIDE, RIGHT_OUTSIDE or OVER_NEEDLES.
    * _CarriageType carriageType()_  
      Type of the carriage: K_CARRIAGE, G_CARRIAGE, L_CARRIAGE.
    * _unsigned int needle()_  
      Needle number at the middle of the carriage (where the thread is).
    * _int position()_  
      Position of the carriage, 0 is the leftmost needle. In contrast to needle() this value
      may become negative or bigger than 199 (because the carriage was a nonzero width).
    * _Direction direction()_  
      Direction of the carriage (LEFT or RIGHT).

    * _void setPattern(boolean value[])_  
      Set the stiching pattern (array of 200 elements). True means move to position B, false to position D.
    * _void needle(unsigned int needle, boolean value)_  
      Set the value of a single needle.

* To initialize use

        PinSetup pins = kniticV2Pins();
        BrotherKH930 brother(pins, onChange, 0);

        void setup() {
          brother.start();
        }

        boolean changed = true;
        void onChange(void*) {
          //is called whenever the state of the knitting machine changes
          //  i.e. when the carriage is moved.
          // WARNING: is called from inside an interrupt handler, so you
          //  will not be able to use Serial. and should not do expensive
          //  stuff. Just set a flag.
          changed = true;
        }

        void loop() {
          if (changed) {
            changed = false;
            //do something with the data, i.e. write to Serial
          }
        }

* For more example code see the [brotherKH930_arduino.ino](brotherKH930_arduino.ino) file in the library

References
----------
Based on the work by [knitic.com](http://knitic.com). Technical information is from the
[Brother Service Manual](https://github.com/msiegenthaler/knitting/blob/master/Manuals/Technical/Service%20Manual%20KH930%20incl.%20KG89II.pdf).
