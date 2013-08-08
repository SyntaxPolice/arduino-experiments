/*
  Isaac's Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  
  Controlled by talking to the serial console.
 
  This example code is in the public domain.
 */
 
int ledPin = 13;         // Pin 13 has an LED connected on most Arduino boards.
int incomingByte = 0;    // for incoming serial data
int ledState = LOW;      // ledState used to set the LED
long previousMillis = 0; // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;    // interval at which to blink (milliseconds)
String content = "";     //Content from readln

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);     
  Serial.begin(9600);
}

// Show the current speed
void printSpeed () {
  Serial.print ("Current speed: ");
  Serial.print (interval);
  Serial.println ("ms.");
}

// Implements a series of commands to flash the light faster / slower.
void cmdProcess () {
  while(Serial.available()) {
      char character = Serial.read();
      if (character == 10) {
         
         if (content.compareTo ("foo") == 0) {
           Serial.println("That's the magic word.");
         } else if (content.compareTo ("faster") == 0) {
           interval -= 100;
           printSpeed();
         } else if (content.compareTo ("slower") == 0) {
           interval += 100;
           printSpeed();
         } else {
           Serial.print ("Unknown command: ");
           Serial.println(content);
         }
         content = "";
      } else { 
        content.concat(character);
      }
  }
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

void loop() {
   cmdProcess();
   ledProcess();
}
