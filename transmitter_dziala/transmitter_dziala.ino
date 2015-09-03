#include <Keypad.h>

// transmitter.pde
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;

void setup()
{
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(50);       // Bits per sec
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);

}
char msg1[] ="j";
char msg2[] = "n";
char  msg3[] = "t";
String msg[] = "nie";
byte count = 0;

void loop()
{ 
  count++;
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  
  if(count%3 == 0) {  vw_send((uint8_t *)msg1, 1);}
if(count%3 == 1) {  vw_send((uint8_t *)msg2, 1);}
if(count%3 == 2) {  vw_send((uint8_t *)msg3, 1);}
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  
}
