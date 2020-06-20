#include <Arduino.h>

/*
  CS >>> D10
  SCLK >> D13
  DI  >>> D11
  PA0 TO VCC
  PBO TO GND
  SHDN >> 9
*/
#include <SPI.h>
//#define I2C_ADDRESS 0x3C
//#include <SSD1306Ascii.h>
//#include <SSD1306AsciiAvrI2c.h>
//SSD1306AsciiAvrI2c oled;
#define upPin 7     //Up tactile switch for increasing counter value, that influences wiper on scale 0-255
#define downPin 3   //dOWN tactile switch for Decreasing counter value, that influences wiper on scale 0-255
#define CS  10    //Chip control goes to pin 10
#define SHDN 9  //Chip SHUTDOWN - PIN 9
#define RS 8    //Chip RESET - PIN 8
#define MDat A4 //meter clock
#define MClk A5 //meter data

byte addressPot0 =     0b00010001;      //To define potentiometer use last two BITS 01= POT 0
byte addressPot1 =     0b00010010;      //To define potentiometer use last two BITS 10= POT 1
byte addressPot0and1 = 0b00010011;  //To define potentiometer use last two BITS 11= POT 0 and 1

int counter = 0;

void setup()
{
  Serial.begin(9600);
  pinMode (CS, OUTPUT); //CS - When High, sets chip to read the data.
  pinMode (SHDN, OUTPUT); //CS - When High, sets chip to read the data.
  pinMode (RS, OUTPUT); //CS - When High, sets chip to read the data.
  pinMode (upPin, INPUT);
  pinMode (downPin, INPUT);
  digitalWrite(SHDN, HIGH); //Power ON (HIGH)
  digitalWrite(RS, HIGH); //Power NO RESET (LOW)
  //initiate OLED
//  oled.begin(&Adafruit128x64, I2C_ADDRESS);
//  oled.setFont(System5x7);
  SPI.begin();
}

void loop()
{
  /*
    PotHighAndLow_bt(addressPot0);      //Change POT values on Pot0
    PotHighAndLow_bt(addressPot1);     //Change POT values on Pot1
    PotHighAndLow_bt(addressPot0and1); //Change POT values on both
  */
  PotHighAndLow_bt(addressPot0);

  Serial.print("counter ");
  Serial.println(counter);
  //oled.print(counter);
  delay(100);
}

void PotHighAndLow_bt(byte address)
{

  int detectUp = digitalRead(upPin);
  int detectDown = digitalRead(downPin);
  if (detectUp == 1 && counter < 255) {
    counter = counter + 5;
    digitalPotWrite(counter, address);
    delay(10);
  }
  else if (detectDown == 1 && counter > 0) {
    counter = counter - 5;
    digitalPotWrite(counter, address);
    delay(10);
  }
  Serial.print("detectUp ");
  Serial.println(detectUp);

  Serial.print("detectDown ");
  Serial.println(detectDown);
}

int digitalPotWrite(byte value, byte address)
{
  digitalWrite(CS, LOW); //Set Chip Active
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH); //Set Chip Inactive
}
