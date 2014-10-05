//==============================================================================
//  PCSOS - modules: bluetooth, internal clock and clock sync
//
//  Created May 16 2014
//  by Erico Silva
//

#include "TimerThree.h"

//------------------------------------------------------------------------------
// Configuration parameters

// Bluetooth
const int SERIAL_BUFFER_SIZE = 10;
const char EOI_BYTE = '\n';              // End of Information byte
const int btVcc = 21;
const int btGnd = 20;

// Pins
const int ledPin = 13;
const int buttonPin = 2;

//------------------------------------------------------------------------------
// State variables

// Bluetooth
String bluetoothInput = "";              // Strings holds the input from serial1
boolean bluetoothInputComplete = false;  // Whether the input string is complete

// Clock
boolean update = false;
int hours = 14;
int minutes = 8;
int seconds = 55;

// Button
boolean trigger = false;

//==============================================================================
// Setup
//
void setup() {
  
  // USB serial (for Debugging using Monitor)
  Serial.begin(9600);
  
  pinMode(btVcc, OUTPUT);
  pinMode(btGnd, OUTPUT);
  
  digitalWrite(btVcc, HIGH);
  digitalWrite(btGnd, LOW);
  
  // Serial 1 (Bluetooth)
  Serial1.begin(9600);
  bluetoothInput.reserve(SERIAL_BUFFER_SIZE);
  
  // Timer
  Timer3.initialize(1000000);          // Set 1 second period
  Timer3.attachInterrupt(updateClock);
  
  // Button
  pinMode(buttonPin, INPUT);
  attachInterrupt(0, emergencyTrigger, RISING);
}

//===============================================================================
// Loop
//
void loop() {
  
  if(bluetoothInputComplete){
    // Serial.println(bluetoothInput); // Debugging
    processCommand(bluetoothInput);
    bluetoothInput = "";
    bluetoothInputComplete = false;
  }
  
  if(update){
    Serial.println(timeToString(hours, minutes));
  }
  
  if(trigger){
    Serial1.println("HELP");
    trigger = false;
  }
}

//==============================================================================
// Interruptions
//

//------------------------------------------------------------------------------
//  serialEvent1 is triggered whenever a new data comes in the serial RX1
void serialEvent1(){
  
  int i = 0;
  while (Serial1.available()){
    // Get new byte from serial 1
    char inChar = (char) Serial1.read();
    
    if(inChar == EOI_BYTE || i > SERIAL_BUFFER_SIZE){
      bluetoothInputComplete = true;
    } else {
      bluetoothInput += inChar;
    }
    
    i++;
  }
  
}

//------------------------------------------------------------------------------
//   updateClock called in the period defined
void updateClock(){
  
  seconds++;
  if(seconds > 59){
    seconds = 0;
    minutes++;
    update = true;
    if(minutes > 59){
      minutes = 0;
      hours++;
      if(hours > 23){
        hours = 0;
      }
    }
  }
}

void emergencyTrigger(){
  trigger = true;
}

//==============================================================================
// Auxiliar functions
//

//------------------------------------------------------------------------------
//   Returns a string representing the current time
String timeToString(int hours, int minutes){
  
  String h = String(hours);
  String m = String(minutes);
  
  if(hours < 10){
    h = String("0" + h);
  }
  
  if(minutes < 10) {
    m = String("0" + m);
  }
  
  update = false;
  
  return String(h + "h" + m);
}

//------------------------------------------------------------------------------
//   Processes the command received
void processCommand(String command){
  
  String time;
  
  Serial.println(command);
  
  if(command.startsWith("SYNC")){
    digitalWrite(ledPin, LOW); 
    time = command.substring(5, 11);
    syncClock(time);
  } else if(command.startsWith("OK")){
    digitalWrite(ledPin, HIGH);
  }
}

void syncClock(String time){
  
  hours = (time.substring(0, 2)).toInt();
  minutes = (time.substring(2, 4)).toInt();
  seconds = (time.substring(4, 6)).toInt();
  /*
  Serial.println(hours);
  Serial.println(minutes);
  Serial.println(seconds);
  */
}
