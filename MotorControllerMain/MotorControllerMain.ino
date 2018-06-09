#define COIN_IN 0
#define COIN_OUT 1

#include <SoftwareSerial.h>
SoftwareSerial coinSerial = SoftwareSerial(COIN_IN,COIN_OUT);

#define TEST_VAL 222
#define HANDSHAKE 233

#define VENDING 9

#define ledPin 13

#define EOL 255

void setup() {

  pinMode(ledPin, OUTPUT);
  
  // put your setup code here, to run once:
  //pinMode(COIN_IN, INPUT);
  //pinMode(COIN_OUT, OUTPUT);

  Serial.begin(4800);
  //Serial.println("motor spirals ready");
  //coinSerial.begin(4800);
}

void loop() {
  //coinSerial.listen();
  //coinSerial.write(HANDSHAKE);
  responseDIRECT();
}

void responseDIRECT(){
  if (Serial.available()) {
    int c = Serial.read();
    //debugChar(c);
    if ( c != EOL ) {
      //if ( c == TEST_VAL ) {
        slowBlink();
      //} else if ( c == 1 ) {
      //  coinSerial.write(VENDING);
      //  Serial.print(c);
      //}
    }
  }    
}

void ssResponse(){
  if (coinSerial.available()) {
    int c = coinSerial.read();
    debugChar(c);
    if ( c != EOL ) {
      //if ( c == TEST_VAL ) {
        coinSerial.write(HANDSHAKE);
      //} else if ( c == 1 ) {
      //  coinSerial.write(VENDING);
      //  Serial.print(c);
      //}
    }
  }  
}

void debugChar( char c ){
  Serial.print(c);
}

void fastBlink(){
  blink( 9, 300 );
}

void slowBlink(){
  blink(3, 900);
  Serial.write(HANDSHAKE);
}

void blink( int count, int delayTime ){
  for ( int i=0; i<count; i++) {
    digitalWrite(ledPin, HIGH);   // sets the LED on
    delay(delayTime);                  // waits for a third second
    digitalWrite(ledPin, LOW);    // sets the LED off
    delay(delayTime);
  }
}
