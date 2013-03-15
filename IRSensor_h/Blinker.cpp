#include "Arduino.h"
#include "Blinker.h"

int *values;
int *_port_pins;
int _array_size;

int _program = 0;
int _program_count = 0;

void program0();
void program1();
void program2();

Blinker::Blinker(int port_pins[], int array_size){
 
  _port_pins = port_pins;
  _array_size = array_size;
  
  values = (int*) malloc(array_size);
  
  for(int i = 0; i < array_size; i++){
    pinMode(port_pins[i], OUTPUT);
    values[i] = 0;
  }
};

void Blinker::_blink(void){  
  int maximumCount = 10;
  switch(_program){
    case 0:
      program0(); break;
    case 1:
      maximumCount = 30;
      program1(); break;
    case 2:
      maximumCount = 90;
      program2(); break;
  }
  
  _program_count++;
  if(_program_count > maximumCount){
    _program++;
    _program_count = 0;
    
    for(int i = 0; i < _array_size; i++)
      values[i] = 0;
    
  }
  
  if(_program > 2)
    _program = 0;
}

void program0(void){
  for(int i = 0; i < _array_size; i++){
    values[i] = !values[i];
    digitalWrite(_port_pins[i], !values[i]);
  }
  delay(300);
}

int _current_pointer = 0;
int dir = 1;
void program1(){
  values[_current_pointer] = 1;
  for(int i = 0; i < _array_size; i++){
    if(i != _current_pointer)
      values[i] = 0;
    digitalWrite(_port_pins[i], values[i]);
  }
  
  if(dir){
    _current_pointer++;
    if(_current_pointer >= _array_size - 1)
      dir = 0;
  }else{
    _current_pointer--;
    if(_current_pointer == 0)
      dir = 1;
  }
  
  delay(300);
}

int odds = 1;
void program2(){
  for(int i = 0; i < _array_size; i++){
    values[i] = (i % 2) == 0;
    if(odds){
      values[i] = !values[i];
    }
    
    digitalWrite(_port_pins[i], values[i]);
  }
  odds = !odds;
  delay(100);
}
