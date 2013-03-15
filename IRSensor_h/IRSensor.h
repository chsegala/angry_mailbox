#ifndef IRSensor_h
#define IRSensor_h

#include "Arduino.h"

class IRSensor{
  public:
    IRSensor(int digital_port, int analog_port);
    int read(int precision);
    
    private:
      int _digital_port;
      int _analog_port;
      void switchIR(int stat);
};

#endif
