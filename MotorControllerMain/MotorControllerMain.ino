#define COIN_IN 13
#define COIN_OUT 12

#include <SoftwareSerial.h>
SoftwareSerial coinSerial = SoftwareSerial(COIN_IN,COIN_OUT);

#define TEST_VAL 222;
#define HANDSHAKE 233;

#define VENDING 9;

#define EOL 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(COIN_IN, INPUT);
  pinMode(COIN_OUT, OUTPUT);

  Serial.begin(9600);
  Serial.println("motor spirals ready");
  coinSerial.begin(4800);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (coinSerial.available()) {
    int c = coinSerial.read();
    debugChar(c);
    if ( c != EOL ) {
      if ( c == TEST_VAL ) {
        coinSerial.write(HANDSHAKE);
      } else if ( c == 1 ) {
        coinSerial.write(VENDING);
        Serial.print(c);
      }
    }
  }
}


void debugChar( char c ){
  Serial.print(c);
}
