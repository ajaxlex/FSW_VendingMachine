#define COIN_IN 13
#define COIN_OUT 12

#include <SoftwareSerial.h>
SoftwareSerial coinSerial = SoftwareSerial(COIN_IN,COIN_OUT);

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
    Serial.print(c);
    if ( c != 255 ) {
      if ( c == 1 ) {
        coinSerial.write(9);
        Serial.print(c);
      }
    }
  }
}
