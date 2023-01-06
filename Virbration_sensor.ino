#include <SoftwareSerial.h>

SoftwareSerial BT_device(2, 3); //-->Tx: 2    Rx:3

const int ledG = 4;
const int ledR = 5;
const int ledB = 6;

const int Virbration_sensor = 9;

void blink(){
  digitalWrite(ledR, 0);
  delay(15);
  digitalWrite(ledR, 1);
  digitalWrite(ledB, 0);
  delay(15);
  digitalWrite(ledB, 1);
  digitalWrite(ledR, 0);
  delay(15);
  digitalWrite(ledR, 1);
  digitalWrite(ledB, 0);
  delay(15);
  digitalWrite(ledB, 1);
  digitalWrite(ledR, 0);
  delay(15);
  digitalWrite(ledR, 1);
}
void setup(){

  BT_device.begin(38400);
  while(!BT_device){}
  for (int i = 4; i <= 6; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(Virbration_sensor, INPUT);
  digitalWrite(ledG, 0);
  digitalWrite(ledB, 1);
  digitalWrite(ledR, 1);
}
void loop(){
  if (digitalRead(Virbration_sensor) == 1){
    BT_device.println("W");
    digitalWrite(ledG, 1);
    blink();
  }
  if (digitalRead(Virbration_sensor) == 0){
    digitalWrite(ledG, 0);
    digitalWrite(ledR, 1);
    digitalWrite(ledB, 1);
    
  }
}
