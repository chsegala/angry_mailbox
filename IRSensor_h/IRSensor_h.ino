#include "IRSensor.h"
#include "Blinker.h"
#include "TMRpcm.h"

#include <SD.h>
#define SD_ChipSelectPin 10  //using digital pin 10 on arduino nano 328

int is_start_up = 1;
int blinkerPorts[] = {5, 6, 7};
int is_blinking = 0;
char* fileNames[] = {"blue.wav"};

IRSensor sensor(2,A0);
Blinker blinker(blinkerPorts, 3);

void setup(){
  //Serial.begin(9600);
}

void loop(){
  if(is_start_up){
    delay(5000);   // if it's starting, wait a while, until the door is closed;
    is_start_up = 0;
  }
  
  if(!is_blinking){
    int dist = sensor.read(5);
    //graph(dist);
    
    if(dist > 30){
      is_blinking = 1;
      playSound();
    }
  }else{
    blinker._blink();  
  }
}

void playSound(){
  if(!SD.begin(SD_ChipSelectPin))
    return; // no sd card found
  
  TMRpcm tmrpcm;  
  File root = SD.open("/");
  tmrpcm.play("blue.wav");
}

void graph(int value){
  for(int i = 0; i < value; i++)
    Serial.write('|');
    
  Serial.print(" --- "+String(value)+"\n");
}
