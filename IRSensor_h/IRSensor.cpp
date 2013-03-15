#include "Arduino.h"
#include "IRSensor.h"

IRSensor::IRSensor(int digital_port, int analog_port){
  _digital_port = digital_port;
  _analog_port = analog_port;
  
  pinMode(digital_port, OUTPUT);
  pinMode(analog_port, INPUT);
}

int IRSensor::read(int precision){
  int values[precision];
  int ambient = 0;
  int sensor = 0;
  
  for(int i = 0; i < precision; i++){
    switchIR(0);
    delay(5);
    ambient = analogRead(_analog_port);
    switchIR(1);
    delay(5);
    sensor = analogRead(_analog_port);
    delay(5);
    values[i] = ambient - sensor;    
  }
  
  int d = 0;
  for(int i = 0; i < precision; i++)
    d += values[i];
    
  return (d/precision);
}

void IRSensor::switchIR(int stat){
  if(stat)
    digitalWrite(_digital_port, HIGH);
  else
    digitalWrite(_digital_port, LOW);
}
