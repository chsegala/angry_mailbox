int IRLedPort = 2; // digital led out
int IRReadPort = A0; //analog led in
int PRECISION = 5; // precision of reading

void setup(){
  Serial.begin(9600);
  pinMode(IRLedPort, OUTPUT);
  digitalWrite(IRLedPort, LOW);
  
  pinMode(IRReadPort, INPUT);
}

void loop(){
  int dist = readDistance();
  //int dist = analogRead(IRReadPort);
  //delay(500);
  graphPrint(dist);
}

int readDistance(){
  int values[PRECISION];
  int ambient = 0;
  int sensor = 0;
  
  for(int i = 0; i < PRECISION; i++){
    switchIR(0);
    delay(1);
    ambient = analogRead(IRReadPort);
    switchIR(1);
    delay(5);
    sensor = analogRead(IRReadPort);
    delay(1);
    switchIR(0);
    values[i] = ambient - sensor;    
  }
  
  int d = 0;
  for(int i = 0; i < PRECISION; i++)
    d += values[i];
    
  return (d/PRECISION);
}

void switchIR(int stat){
  if(stat)
    digitalWrite(IRLedPort, HIGH);
  else
    digitalWrite(IRLedPort, LOW);
}

void graphPrint(int n){
  for(int i = 0; i < n; i++)
    Serial.write('|');
  Serial.write('\n');
}
