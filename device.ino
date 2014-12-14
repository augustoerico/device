//==============================================================================
//  Display I2C
//
//  Created Nov 13 2014
//  by Erico Silva
//

#include <TimerOne.h>
#include <Wire.h>
#include "numbers.h"
#include "letters.h"
#include "icons.h"

//------------------------------------------------------------------------------
// Configuration parameters

// Display SCL = A5, SDA = A4
const int displayAddress = 0x3c;
const int MAX_COLUMN     = 92;

// Bluetooth
const int SERIAL_BUFFER_SIZE = 10;
const char EOI_BYTE = '\n';              // End of Information byte
const int btVcc = 5;
const String AT_SETNAME = "AT+NAME"; 

// Pins
const int buttonPin = 2;
const int ledPin    = 13;

//------------------------------------------------------------------------------
// State variables

// Bluetooth
String bluetoothInput = "";              // Strings holds the input from serial1
boolean bluetoothInputComplete = false;  // Whether the input string is complete

// Clock
boolean update = false;
int hours = 10;
int minutes = 8;
int seconds = 55;

// Button
boolean trigger = false;

// Led
boolean led = LOW;

//==============================================================================
// Setup
//
void setup(){
  
  // Timer
  Timer1.initialize(1000000);          //FIXME: set for 1 ms? // Set 1 second period
  Timer1.attachInterrupt(updateClock);
  
  // Button
  pinMode(buttonPin, INPUT);
  attachInterrupt(0, emergencyTrigger, RISING);
  
  // Bluetooth
  Serial.begin(9600);
  configureBluetooth();
  
  Wire.begin();
  delay(10);
  initializeDisplay();
  // TODO: PCSOS logo here
  
  // Dummy test
  writeLetter(0);
  writeDigit(0);
  writeDigit(0);
  writeDigit(3);
  writeDigit(1);  
}

//===============================================================================
// Loop
//
void loop(){
  
  if(bluetoothInputComplete){
    processCommand(bluetoothInput);
    bluetoothInput = "";
    bluetoothInputComplete = false;
  }
  
  if(update){
    printClock();
    update = false;
  }
  
  if(trigger){
    Serial.println("HELP");
    trigger = false;
  }
  
}


//==============================================================================
// Interruptions
//

//------------------------------------------------------------------------------
//  serialEvent is triggered whenever a new data comes in the serial RX0
void serialEvent(){
  
  int i = 0;
  while (Serial.available()){
    // Get new byte from serial
    char inChar = (char) Serial.read();
    
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

void initializeDisplay(){
  
  clearDisplay();
  
  writeCommand(0xD3); // set vertical offset
  writeCommand(0x00); // to column 0
  
  delay(50);
  
  writeCommand(0x20); // set addressing mode
  writeCommand(0x01); // vertical addressing
  
  writeCommand(0x21); // set column address
  writeCommand(0x05); // start in 5d
  writeCommand(0x77); // ends in 119d
  
  writeCommand(0x22); // set page address
  writeCommand(0x02); // starts in page 2d
  writeCommand(0x05); // ends in page 5d
  
  writeCommand(0x81); // set contrast value
  writeCommand(0x00); // lowest value
  
  writeCommand(0xA4); // display memory content (instead of all on)
  
  delay(50);
  writeCommand(0xAF); // display on
  
}

void configureBluetooth(){
  
  Serial.println("\n" + AT_SETNAME + "PCS.O.S");
  bluetoothInput = "";
  
}

//==============================================================================
// Set all pixels off
//
void clearDisplay(){
  
  writeCommand(0x20); // set addressing mode
  writeCommand(0x00); // horizontal addressing
  
  writeCommand(0x21); // set column address
  writeCommand(0x00); // start in 0d
  writeCommand(0x7F); // ends in 127d
  
  writeCommand(0x22); // set page address
  writeCommand(0x00); // starts in page 0d
  writeCommand(0x07); // ends in page 7d
  
  int i, j;
  for(i = 0; i < 8; i++){
    for(j = 0; j < 128; j++){
      writeData(0x00);
    }
  }
  
}

void printClock(){
  
  writeCommand(0x20); // set addressing mode
  writeCommand(0x01); // vertical addressing
  
  writeCommand(0x21); // set column address
  writeCommand(0x05); // start in 5d
  writeCommand(0x77); // ends in 119d
  
  writeCommand(0x22); // set page address
  writeCommand(0x02); // starts in page 2d
  writeCommand(0x05); // ends in page 5d
  
  writeDigit(hours/10);
  writeDigit(hours%10);
  writeLetter(0);
  writeDigit(minutes/10);
  writeDigit(minutes%10);
  
}

//==============================================================================
// Write a digit to display
//
void writeDigit(int digit){
  
  int i;
  for(i = 0; i < MAX_COLUMN; i++){
    writeData(digits[digit][i]);
  }
  
}

//==============================================================================
// Write a icon to display
//
void writeIcon(const unsigned char icon[], int startPage, int startColumn, 
  int endPage, int endColumn){
   
    // TODO: write validation function
    
    // set columns delimitations
    writeCommand(0x21);       // set column address
    writeCommand(startColumn); 
    writeCommand(endColumn);
    
    // set page delimitations
    writeCommand(0x22);       // set page address
    writeCommand(startPage);
    writeCommand(endPage);
    
    // Write icon
    int bytes = (endPage - startPage + 1)*(endColumn - startColumn + 1);
    int b;
    for(b = 0; b < bytes; b++){
      writeData(icon[b]);
    }
    
    // Back to previous state // TODO: stack the display configurations
    writeCommand(0x21); // set column address
    writeCommand(0x05); // start in 5d
    writeCommand(0x77); // ends in 119d
    
    writeCommand(0x22); // set page address
    writeCommand(0x02); // starts in page 2d
    writeCommand(0x05); // ends in page 5d
}

//==============================================================================
// Write a letter to display
//
void writeLetter(int letterIndex){
  
  int i;
  for(i = 0; i < MAX_COLUMN; i++){
    writeData(letters[letterIndex][i]);
  }
  
}

void writeCommand(int cmd){
  
  Wire.beginTransmission(displayAddress);
  Wire.write(0x80);
  Wire.write(cmd);
  Wire.endTransmission();

}

void writeData(int data){
  
  Wire.beginTransmission(displayAddress);
  Wire.write(0x40);
  Wire.write(data);
  Wire.endTransmission();
  
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
    printClock();
  } else if(command.startsWith("OK")){
    digitalWrite(ledPin, HIGH);
    writeIcon(rescueInProgress, 0, 0, 0, 7); 
  } else if(command.startsWith("END")){
    clearDisplay();
    printClock();
  }
}

void syncClock(String time){
  
  hours = (time.substring(0, 2)).toInt();
  minutes = (time.substring(2, 4)).toInt();
  seconds = (time.substring(4, 6)).toInt();
  
}
