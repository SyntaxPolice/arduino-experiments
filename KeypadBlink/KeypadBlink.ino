/*
  Keypad blink.

  Blink the LED based on input from the keypad. Type the interval speed and 
  hit the * key. Use # to reset the keys.  
 
  This example code is in the public domain.
 */
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

int ledPin = 13;         // Pin 13 has an LED connected on most Arduino boards.
int ledState = LOW;      // ledState used to set the LED
long previousMillis = 0; // will store last time LED was updated
String keyInput = "";    // Start the keypad input as empty.

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;    // interval at which to blink (milliseconds)

// ------------- Keypad definitions ------------------------
const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


byte rowPins[ROWS] = { 9,8,7,6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 5,4,3,2, };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// -------------- setup ---------------------------------------
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);     
  Serial.begin(9600);
  Serial.println("Type the numeric interval for blinking then hit *. Use # to reset.");
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

// Show the current speed
void printSpeed () {
  Serial.print ("Current speed: ");
  Serial.print (interval);
  Serial.println ("ms.");
}

void ledProcess () {
  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;  

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}

// Handle keypad input by accumulating data in the pinInput constant
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
	Serial.print(eKey);
	switch (eKey){
	  case '*': interval = keyInput.toInt(); keyInput = ""; Serial.print("\n"); printSpeed(); break;
	  case '#': keyInput = ""; Serial.println ("\nReset"); break;
	  default: keyInput.concat(eKey);
     }
  }
}

void loop() {
   keypad.getKey();
   ledProcess();
}
