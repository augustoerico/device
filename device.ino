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

//------------------------------------------------------------------------------
// Configuration parameters

// Display SCL = A5, SDA = A4
const int displayAddress = 0x3c;
const int MAX_COLUMN     = 92;

//------------------------------------------------------------------------------
// State variables

// Clock
boolean update = false;
int hours = 10;
int minutes = 8;
int seconds = 55;

//==============================================================================
// Setup
//
void setup(){
  
  // USB serial (for Debugging using Monitor)
  // Serial.begin(9600);
  
  // Timer
  Timer1.initialize(1000000);          //FIXME: set for 1 ms? // Set 1 second period
  Timer1.attachInterrupt(updateClock);
  
  Wire.begin();
  delay(10);
  
  initializeDisplay();
  // TODO: PCSOS logo here
  
  writeDigit(1);
  writeDigit(2);
  writeDigit(3);
  writeDigit(minutes);
  writeLetter(0);
  
}

//===============================================================================
// Loop
//
void loop(){
  
  if(update){
    printClock();
    update = false;
  }
  
}


//==============================================================================
// Interruptions
//

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
