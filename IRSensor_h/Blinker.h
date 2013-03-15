#ifndef Blinker_h
#define Blinker_h

#include "Arduino.h"
class Blinker{
  public:
    Blinker(int port_pins[], int array_size);
    void _blink(void);
};

#endif
