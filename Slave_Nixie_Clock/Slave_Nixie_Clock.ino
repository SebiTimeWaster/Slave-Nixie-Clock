/**
  *  The MIT License (MIT)
  *
  *  Slave Nixie Clock - Copyright (c) 2017 SebiTimeWaster
  *
  *  Permission is hereby granted, free of charge, to any person obtaining a copy
  *  of this software and associated documentation files (the "Software"), to deal
  *  in the Software without restriction, including without limitation the rights
  *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  *  copies of the Software, and to permit persons to whom the Software is
  *  furnished to do so, subject to the following conditions:
  *
  *  The above copyright notice and this permission notice shall be included in all
  *  copies or substantial portions of the Software.
  *
  *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  *  SOFTWARE.
  */

#include <SPI.h>

#define pinLatchEnable 10
#define pinAnode0      5
#define pinAnode1      7
#define pinAnode2      8
#define pinUpperDots   12
#define pinLowerDots   4
#define pinRLed        9
#define pinGLed        6
#define pinBLed        3

#define enablePinHigh PORTB |= 0b00000100
#define enablePinLow  PORTB &= 0b11111011
#define anode0High    PORTD |= 0b00100000
#define anode0Low     PORTD &= 0b11011111
#define anode1High    PORTD |= 0b10000000
#define anode1Low     PORTD &= 0b01111111
#define anode2High    PORTB |= 0b00000001
#define anode2Low     PORTB &= 0b11111110
      
String displayClear  = "xxxxxx00000000"; // display data to show empty (and not illuminated) display
String displayBuffer = displayClear;
/*
 * displayBuffer contains all data needed to display 6 numbers and light the points and the led's.
 * char 0-5:   What to display on the nixies, anything else than a number (isDigit()) shows nothing.
 * char 6:     "1" to light the upper dots
 * char 7:     "1" to light the lower dots
 * char 8-9:   A hex value from 00 to FF representing the brightness of the red led's
 * char 10-11: A hex value from 00 to FF representing the brightness of the green led's
 * char 12-13: A hex value from 00 to FF representing the brightness of the blue led's
 */

