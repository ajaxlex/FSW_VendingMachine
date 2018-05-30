/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/


#define COIN_IN 11

#define MOTOR_IN 13
#define MOTOR_OUT 12


#include <SoftwareSerial.h>
SoftwareSerial mySerial = SoftwareSerial(COIN_IN,13);
SoftwareSerial motorSerial = SoftwareSerial(MOTOR_IN,MOTOR_OUT);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
 
  pinMode(COIN_IN, INPUT);
  pinMode(MOTOR_IN, INPUT);
  pinMode(MOTOR_OUT, OUTPUT);

  Serial.begin(9600);
  Serial.println("fish thing ready");          
  mySerial.begin(4800);
  //motorSerial.begin(4800);
}

// the loop routine runs over and over again forever:
void loop() {
  if (mySerial.available()) {
    int i=mySerial.read();
    if (i != 255) {
      Serial.print(i);  
      motorSerial.begin(4800);
      motorSerial.print(i);

    }
  }
  
  if (motorSerial.available()) {
    int m = motorSerial.read();
    if ( m != 255 ) {
      int m = motorSerial.read();  
      Serial.print(m);      
    }
  }
  
}
