/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

//#include <NeoSWSerial.h>
#include <SoftwareSerial.h>
#include <Bounce2.h>

#define COIN_IN 11
#define COIN_NULL 10

#define MOTOR_OUT 12
#define MOTOR_IN 13


//NeoSWSerial coinSerial(COIN_IN,13);
//NeoSWSerial motorSerial(MOTOR_IN,MOTOR_OUT);
SoftwareSerial coinSerial = SoftwareSerial(COIN_IN, COIN_NULL);
SoftwareSerial motorSerial = SoftwareSerial(MOTOR_IN,MOTOR_OUT);

int sendData = 999;

int length = 0;
char response[20];

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:

  pinMode(COIN_IN, INPUT);
  pinMode(MOTOR_IN, INPUT);
  pinMode(MOTOR_OUT, OUTPUT);

  Serial.begin(9600);
  Serial.println("fish thing ready ++");
  coinSerial.begin(4800);
  motorSerial.begin(4800);

  coinSerial.listen();
}




// the loop routine runs over and over again forever:
void loop() {
  sendData = 999;
  //readButtons();
  readCoinMachine();
  readMotorController();  
}



void readCoinMachine(){
  if (coinSerial.available()) {
    int i=coinSerial.read();
    if (i != 255) {
      Serial.print(i);
      sendData = i;
      motorSerial.listen();
    }
  }
}

void readMotorController(){

  if ( sendData != 999 ) {
    motorSerial.print(sendData);
  }
  
  if (motorSerial.available()) {
    int m = motorSerial.read();
    if ( m != 255 ) {
      int m = motorSerial.read();
      //if ( sendData != 999 ) {
      //  motorSerial.print(m);
      //}
      Serial.print(m);
      coinSerial.listen();
    }
  }  
}

void readButtons(){
  
}

