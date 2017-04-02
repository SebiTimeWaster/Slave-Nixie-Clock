# Slave-Nixie-Clock
Software to control a "GRA &amp; AFCH" NCM107 + NCT412 Nixie clock via a serial connection

!["GRA &amp; AFCH" NCM107 + NCT412](https://github.com/SebiTimeWaster/Slave-Nixie-Clock/blob/master/NixieClock.jpg)

## What it does
This is an Arduino sketch to control a "GRA &amp; AFCH" NCM107 + NCT412 Nixie clock via serial protocol, basically turning it into a computer display (While ignoring the RTC functionality).

#### One can send two different strings via serial connection to the clock:

##### A 14 byte long display string terminated with a newline:

 * char 0-5:   What to display on the nixies, anything else than a number (isDigit()) shows nothing.
 * char 6:     "1" to light the upper dots
 * char 7:     "1" to light the lower dots
 * char 8-9:   A hex value from 00 to FF representing the brightness of the red led's
 * char 10-11: A hex value from 00 to FF representing the brightness of the green led's
 * char 12-13: A hex value from 00 to FF representing the brightness of the blue led's
 
##### And a 2 byte long color cycling string terminated with a newline:

 * char 0-1: A hex value from 00 to FF representing the speed of a LED color cycling animation between 133 and 0.52 seconds long, "00" turns it off

The color cycling animation overwrites the led color set by the display string.

## Installation
Download a release or clone this project with git. 

## Usage
Open "Slave_Nixie_Clock/Slave_Nixie_Clock.ino" in your Arduino IDE of choice and upload it to your clock.

For more information see: [afch/NixieClock](https://github.com/afch/NixieClock)

## Changelog
Changelog v0.1:
* Initial checkin
