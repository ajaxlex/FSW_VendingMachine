#define COIN_IN 0
#define COIN_OUT 1

# define motor_1 2
# define motor_2 3
# define motor_3 4
# define motor_4 5
# define motor_5 6
# define motor_6 7
# define motor_7 8
# define motor_8 9

# define TEST_PIN 14  // analog 0 

#define TEST_VAL 222
#define HANDSHAKE 233

#define VENDING 9

#define ledPin 13

#define EOL 255

void setup() {

  pinMode(ledPin, OUTPUT);

  pinMode(motor_1, OUTPUT);
  pinMode(motor_2, OUTPUT);
  pinMode(motor_3, OUTPUT);
  pinMode(motor_4, OUTPUT);
  pinMode(motor_5, OUTPUT);
  pinMode(motor_6, OUTPUT);
  pinMode(motor_7, OUTPUT);
  pinMode(motor_8, OUTPUT);

  pinMode( TEST_PIN,INPUT_PULLUP );
  
  Serial.begin(4800);
}

void loop() {
  if ( noSpecialRequest() ) {
    responseDIRECT();
  }
}

bool noSpecialRequest(){
  if ( digitalRead( TEST_PIN ) == LOW ) {

    actuateMotor('1'); 
    delay( 2000 );
    actuateMotor('2'); 
    delay( 2000 );
    actuateMotor('3'); 
    delay( 2000 );
    actuateMotor('4'); 
    delay( 2000 );
    actuateMotor('5'); 
    delay( 2000 );    
    actuateMotor('6'); 
    delay( 2000 );
    actuateMotor('7'); 
    delay( 2000 );
    actuateMotor('8'); 

    return false;
  }
  return true;
}

void responseDIRECT(){
  if (Serial.available()) {
    //char b = Serial.read();
    char c = Serial.read();
    if ( c != EOL ) {
      //blink(2, 80);
      actuateMotor( c );
      //Serial.write(HANDSHAKE);

      // FLUSH
      while ( Serial.available() > 0 ) {
        Serial.read();      
      }
    }
  }    
}

void actuateMotor( char c ){

  if ( c == '1' ) {
    sendMotorSignal( motor_1 );
  } else if ( c == '2' ) {
    sendMotorSignal( motor_2 );
  } else if ( c == '3' ) {
    sendMotorSignal( motor_3 );
  } else if ( c == '4' ) {
    sendMotorSignal( motor_4 );
  } else if ( c == '5' ) {
    sendMotorSignal( motor_5 );
  } else if ( c == '6' ) {
    sendMotorSignal( motor_6 );
  } else if ( c == '7' ) {
    sendMotorSignal( motor_7 );
  } else if ( c == '8' ) {
    sendMotorSignal( motor_8 );
  } else {
    blink(500,10);
    delay(1000);
    //blink(c,500);
  }
  
}

void sendMotorSignal( int motor ){
  //testWrite();
  //return;
  blink( motor, 150 );  
  digitalWrite( motor, HIGH );
  delay(6000);
  digitalWrite( motor, LOW );
}

void testWrite(){
  int t=2;
  digitalWrite( t, HIGH );
  delay(5000);
  digitalWrite( t, LOW );
  return;
  
  for ( int i=2; i<10; i++ ){
    digitalWrite( i, HIGH );
  }
  delay(5000);
  for ( int i=2; i<10; i++ ){
    digitalWrite( i, LOW );
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
