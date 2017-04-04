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

When no serial string is received for longer than 60 seconds a 20 second cathode cleaning cycle starts and after that it turns the display "off" meaning no refresh is done anymore. when at some point a new serial string is received the display turns on again.

## Installation
Download a release or clone this project with git. 

## Usage
Open "Slave_Nixie_Clock/Slave_Nixie_Clock.ino" in your Arduino IDE of choice and upload it to your clock.

In /examples you will find an example Python script to control the Nixie Clock (It sends the computer time to the Nixie Clock). It comes without any guarantee (It was only tested under OS X), if you want to create your own scripts on top of it please don't ask me for support.

For more information about the Nixie Clock itself see the [GRA & AFCH Website](http://gra-afch.com/) and the [afch/NixieClock GitHub Repo](https://github.com/afch/NixieClock)

## Changelog
Changelog v0.2:
* Fixed some small bugs
* Added example Python script

Changelog v0.1:
* Initial checkin
