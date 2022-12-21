/*
 * 
 * CS 362 Project 1: Subsystem 1
 * Author: Krish Patel
 * 
 */

// Include all the necessary libraries.
# include <SPI.h>
# include <nRF24L01.h>
# include <RF24.h>

// Set the radio at pin 7,8
RF24 radio(7, 8);

// Set the channel address.
// const byte address[6] = {"00001"};
const byte addresses[][6] = {"00001", "00002"};

// Declare the button pins and led pins.
const int buttonPin = 6;
const int redLED = 5;
const int greenLED =  4;

//
//
//
void setup() {

  Serial.begin(9600);

  // Setup Buttons and LEDs
  pinMode(buttonPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Start the radio.
  radio.begin();
  
  // Set the radio channels and pipes.
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001

  radio.setPALevel(RF24_PA_MIN);
}

//
//
//
void loop() {

  int ButtonState = digitalRead(buttonPin);

  //
  //
  //
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  // Check if transmission button is pressed or not..
  if(ButtonState == HIGH) {
    // Stop the input stream.
    radio.stopListening();

    // Get the microphone input.
    int value = analogRead(A0);
    
    // Light up the green LED. indicates messgae transfer.
    digitalWrite(greenLED, HIGH);

    // Write to speaker..
    tone(2, value, 500);
        
  
    // Serial.println(text);
    radio.write(&value, sizeof(value));

    // Start the radio input stream.
    radio.startListening();
  } else {
    
    radio.startListening();

    if(radio.available()) {

      // Light up the red LED..
      digitalWrite(redLED, HIGH);

      // Get the input value. 
      int InputValue = 0;
      radio.read(&InputValue, sizeof(InputValue));
      // Serial.println(); // for debugging purposes.

      // Play audio on the speaker.
      tone(2, InputValue, 500);
    }

    radio.stopListening();
  }
  
}
