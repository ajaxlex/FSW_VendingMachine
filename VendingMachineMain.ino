#include <SoftwareSerial.h>
#include <Bounce2.h>

#define button_1 2
#define button_2 3
#define button_3 4
#define button_4 5

# define motor_1 6
# define motor_2 7
# define motor_3 8
# define motor_4 9

#define COIN_IN 11
#define COIN_NULL 0

#define ledPin 13
#define TEST_PIN 14

#define EOL 255
#define TEST_VAL 222
#define HANDSHAKE 233
#define NO_DATA 999

#define MOTOR_TURN_DURATION 6000

#define TEST_MODE 1

#define NUM_PRODUCTS 4

struct productLink {
  int button;
  int motor;
  int cost;
  bool button_state;
  Bounce deb;
} products[NUM_PRODUCTS];


////////////////////////////////////////////////////////////////
// SETUP CODE
////////////////////////////////////////////////////////////////

// Create an object to manage the software serial connections to the coin machine
SoftwareSerial coinSerial = SoftwareSerial(COIN_IN, COIN_NULL);

// Create debounce objects for the button inputs
Bounce deb_1 = Bounce();
Bounce deb_2 = Bounce();
Bounce deb_3 = Bounce();
Bounce deb_4 = Bounce();

// initialize the coin flag to 'Not' enough coins
int coinCount = 0;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(TEST_PIN, INPUT_PULLUP );
  pinMode(COIN_IN, INPUT);

  // set the software serial port to listen at 4800 baud
  // the coin machine must be programmed to communicate at 4800 as well
  coinSerial.begin(4800);

  coinCount = 0;

  products[0] = { button_1, motor_1, 0, false, deb_1 };
  products[1] = { button_2, motor_2, 0, false, deb_2 };
  products[2] = { button_3, motor_3, 0, false, deb_3 };
  products[3] = { button_4, motor_4, 0, false, deb_4 };
  
  products[0].cost = 25;
  products[1].cost = 25;
  products[2].cost = 25;
  products[3].cost = 25;

  setupTest();
  setupButtons();
  setupMotors();

  pinMode( ledPin, OUTPUT );
  pinMode( TEST_PIN, INPUT_PULLUP );
}

void setupTest(){
    if ( TEST_MODE ){
      Serial.begin(9600);
    }
}

void setupButtons(){
  for ( int i=0; i < NUM_PRODUCTS; i++ ){
    pinMode( products[i].button, INPUT_PULLUP );
    products[i].deb.attach( products[i].button );
    products[i].deb.interval(5);
  }
}

void setupMotors() {
  for ( int i=0; i < NUM_PRODUCTS; i++ ){
    pinMode( products[i].motor, OUTPUT );
  }
}










// the loop routine runs over and over again forever:
void loop(){
    readButtons();
    readCoinMachineDIRECT();
}

void readCoinMachineDIRECT(){
  if (coinSerial.available()) {
    int c=coinSerial.read();
    testPrint('C');
    testPrint(c);
    if ( c != EOL ) {
      testPrint('E');
      blink(2,80); // blocking
      coinCount += c;
    }
  }
}

void readButtons(){
  int localRead[NUM_PRODUCTS];

  // updates the debounce values for each button 
  for ( int i=0; i < NUM_PRODUCTS; i++ ){
    products[i].deb.update();
  }

  // assign the debounced values to vals
  for ( int i=0; i < NUM_PRODUCTS; i++ ){
    localRead[i] = products[i].deb.read();
  }

  // check the button state for each read and act if enough coins
  for ( int i=0; i < NUM_PRODUCTS; i++ ){
    checkButtonState( localRead[i], i );
  }
}

// this function tests if a button is pushed.  
// If there are also enough coins, it activates the appropriate motor
void checkButtonState( int state, int idx ){
  if ( state == LOW ) {
    testPrint('B');
    testPrint(idx);
    if ( updateCoinAmount( idx ) ) {
      actuateMotor( products[idx].motor );
    } else {
      delay(500);
    }
  }
}

bool updateCoinAmount( int idx ){
  if ( coinCount >= products[idx].cost ) {
    coinCount -= products[idx].cost;
    return true;
  }
  return false;
}

void actuateMotor( int motor ){
  testPrint('M');
  testPrint(motor);
  blink( motor, 150 );  
  digitalWrite( motor, HIGH );
  delay(MOTOR_TURN_DURATION);
  digitalWrite( motor, LOW );
}



//////////////////////////////////////////////
// UTILITIES
//////////////////////////////////////////////

void blink( int count, int delayTime ){
  for ( int i=0; i<count; i++) {
    digitalWrite(ledPin, HIGH);   // sets the LED on
    delay(delayTime);                  // waits for a third second
    digitalWrite(ledPin, LOW);    // sets the LED off
    delay(delayTime);
  }
}

void testPrint( int i ){
  if ( TEST_MODE ){
    char str[10];
    sprintf(str, "%d", i);
    Serial.print(str);    
  }
}

void testPrint( char c ){
  if ( TEST_MODE ){
    Serial.print(c);
  }
}