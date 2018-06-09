/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

#include <SoftwareSerial.h>
#include <Bounce2.h>

#define COIN_IN 11
#define COIN_NULL 0

#define MOTOR_OUT 1
#define MOTOR_IN 0

#define ledPin 13

#define UNDETERMINED_PHASE -1

// coin phase will listen to the coin collector and button presses
#define COIN_PHASE 0

// motor phase will talk and listen to the motor controller
#define MOTOR_PHASE 1

#define EOL 255
#define TEST_VAL 222
#define HANDSHAKE 233
#define NO_DATA 999

#define PRETEST_INIT 0
#define PRETEST_PASSED 1
#define PRETEST_FAILED 2
#define PRETEST_LISTEN 3

SoftwareSerial coinSerial = SoftwareSerial(COIN_IN, COIN_NULL);
SoftwareSerial motorSerial = SoftwareSerial(MOTOR_IN,MOTOR_OUT);

int sendData = NO_DATA;

int length = 0;
char response[20];

int commPhase = UNDETERMINED_PHASE;

int testState = PRETEST_INIT;
int escape = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:

  pinMode(ledPin, OUTPUT);

  pinMode(COIN_IN, INPUT);
//  pinMode(MOTOR_IN, INPUT);
//  pinMode(MOTOR_OUT, OUTPUT);

  Serial.begin(4800);
  //Serial.println("fish thing ready ++");
  coinSerial.begin(4800);
  //motorSerial.begin(4800);

  //setCoinPhase();
}




// the loop routine runs over and over again forever:
void loop() {

  //testControllersConnection();

  testState = PRETEST_PASSED;

  if ( testState == PRETEST_PASSED ) {
    sendData = NO_DATA;
    //readButtons();
    readCoinMachineDIRECT();
    readMotorControllerDIRECT();
  }
}



void readCoinMachine(){
  if ( coinPhase() ) {
    if (coinSerial.available()) {
      int c=coinSerial.read();
      if ( c != EOL ) {
        sendData = c;
        debugChar(c);
        setMotorPhase();
      }
    }
  }
}

void readCoinMachineDIRECT(){
  if (coinSerial.available()) {
    int c=coinSerial.read();
    if ( c != EOL ) {
      sendData = c;
      //debugChar(c);
      fastBlink();
      //setMotorPhase();
    }
  }
}

void readMotorController(){
  if ( motorPhase() ) {
    if ( sendData != NO_DATA ) {
      motorSerial.print(sendData);
      sendData = NO_DATA;
    }

    if (motorSerial.available()) {
      int m = motorSerial.read();
      if ( m != EOL ) {
        debugChar(m);
        setCoinPhase();
      }
    }
  }
}

void tryWriteDIRECT(){
  if ( sendData != NO_DATA ) {
    Serial.print(sendData);
  }
}

void readMotorControllerDIRECT(){
  if (Serial.available()) {
    int m = Serial.read();
    if ( m != EOL ) {
      slowBlink();
      //debugChar(m);
      //setCoinPhase();
    }
  }
}


void readButtons(){

}

void debugChar( char c ){
  Serial.print(c);
}


void setCoinPhase(){
  commPhase = COIN_PHASE;
  coinSerial.listen();
}

void setMotorPhase(){
  commPhase = MOTOR_PHASE;
  motorSerial.listen();
}

bool coinPhase(){
  return ( commPhase == COIN_PHASE );
}

bool motorPhase(){
  return ( commPhase == MOTOR_PHASE );
}

void fastBlink(){
  blink( 9, 300 );
  tryWriteDIRECT();
}

void slowBlink(){
  blink(3, 900);
}

void blink( int count, int delayTime ){
  for ( int i=0; i<count; i++) {
    digitalWrite(ledPin, HIGH);   // sets the LED on
    delay(delayTime);                  // waits for a third second
    digitalWrite(ledPin, LOW);    // sets the LED off
    delay(delayTime);
  }
}

bool testControllersConnection(){
    if ( testState == PRETEST_INIT ) {
      Serial.println("Testing Connection SEND");
      motorSerial.listen();
      motorSerial.print( TEST_VAL );
      testState = PRETEST_LISTEN;

    } else if ( testState = PRETEST_LISTEN ) {
      Serial.println("Testing Connection LISTEN");
      motorSerial.listen();
      if (motorSerial.available()) {
        Serial.println("Testing Connection AVAILABLE");
        int m = motorSerial.read();
        debugChar(m);
        if ( m != EOL && m == HANDSHAKE ) {
          debugChar('7');
          debugChar(m);
          return true;
          testState = PRETEST_PASSED;
        }
      } else {
        testState = PRETEST_INIT;
      }
      escape++;
      if ( escape > 10000 ) { testState = PRETEST_FAILED; }
    }
}
