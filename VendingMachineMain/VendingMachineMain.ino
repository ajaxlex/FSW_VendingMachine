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


#define button_1 2
#define button_2 3
#define button_3 4
#define button_4 5
#define button_5 6
#define button_6 7
#define button_7 8
#define button_8 9





#define COIN_IN 11
#define COIN_NULL 0

#define MOTOR_OUT 1
#define MOTOR_IN 0

#define ledPin 13

#define TEST_PIN 14

#define EOL 255
#define TEST_VAL 222
#define HANDSHAKE 233
#define NO_DATA 999

SoftwareSerial coinSerial = SoftwareSerial(COIN_IN, COIN_NULL);

Bounce deb_1 = Bounce();
Bounce deb_2 = Bounce();
Bounce deb_3 = Bounce();
Bounce deb_4 = Bounce();
Bounce deb_5 = Bounce();
Bounce deb_6 = Bounce();
Bounce deb_7 = Bounce();
Bounce deb_8 = Bounce();

bool enoughCoins = false;




// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:

  pinMode(ledPin, OUTPUT);
  pinMode(TEST_PIN, INPUT_PULLUP );
  pinMode(COIN_IN, INPUT);

  Serial.begin(4800);
  coinSerial.begin(4800);

  setupButtons();
}


void setupButtons(){
  pinMode( button_1, INPUT_PULLUP );
  pinMode( button_2, INPUT_PULLUP );
  pinMode( button_3, INPUT_PULLUP );
  pinMode( button_4, INPUT_PULLUP );
  pinMode( button_5, INPUT_PULLUP );
  pinMode( button_6, INPUT_PULLUP );
  pinMode( button_7, INPUT_PULLUP );
  pinMode( button_8, INPUT_PULLUP );

  deb_1.attach( button_1 );
  deb_1.interval(5);
  deb_2.attach( button_2 );
  deb_2.interval(5);
  deb_3.attach( button_3 );
  deb_3.interval(5);
  deb_4.attach( button_4 );
  deb_4.interval(5);
  deb_5.attach( button_5 );
  deb_5.interval(5);
  deb_6.attach( button_6 );
  deb_6.interval(5);
  deb_7.attach( button_7 );
  deb_7.interval(5);
  deb_8.attach( button_8 );
  deb_8.interval(5);
}



// the loop routine runs over and over again forever:
void loop() {
    checkTest();
    readButtons();
    readCoinMachineDIRECT();
    //readMotorControllerDIRECT();
}

void checkTest(){
  if ( digitalRead( TEST_PIN ) == LOW ) {
    tryWriteDIRECT('4');
  }
}

void readCoinMachineDIRECT(){
  if (coinSerial.available()) {   
    int c=coinSerial.read();
    if ( c != EOL ) {
      blink(2,80); // blocking
      enoughCoins = true;
    }
  }
}

void tryWriteDIRECT( char target ){
  //if ( target != NO_DATA ) {
    Serial.print(target);
  //}
}

void readMotorControllerDIRECT(){
  if (Serial.available()) {
    int m = Serial.read();
    if ( m != EOL ) {
      slowBlink();
    }
  }
}


void readButtons(){
  deb_1.update();
  deb_2.update();
  deb_3.update();
  deb_4.update();
  deb_5.update();
  deb_6.update();
  deb_7.update();
  deb_8.update();


  int val_1 = deb_1.read();
  int val_2 = deb_2.read();
  int val_3 = deb_3.read();
  int val_4 = deb_4.read();
  int val_5 = deb_5.read();
  int val_6 = deb_6.read();
  int val_7 = deb_7.read();
  int val_8 = deb_8.read();

  testButton( val_1, 1, '1' );
  testButton( val_2, 2, '2' );
  testButton( val_3, 3, '3' );
  testButton( val_4, 4, '4' );
  testButton( val_5, 5, '5' );
  testButton( val_6, 6, '6' );
  testButton( val_7, 7, '7' );
  testButton( val_8, 8, '8' );


}

void testButton( int state, int val, char cval ){
  if ( state == LOW ) {    
    if ( enoughCoins == true ) {
      enoughCoins = false;
      blink( val, 70 );
      tryWriteDIRECT( cval );
    } else {
      delay(500);
      //blink( val, 150 );
    }
  }  
}




void fastBlink(){
  blink( 9, 300 );
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
