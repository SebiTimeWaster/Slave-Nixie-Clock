/**
  *  The MIT License (MIT)
  *
  *  Slave Nixie Clock v0.1 Copyright (c) 2017 SebiTimeWaster
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


import serial
import time
from datetime import datetime
import signal
import sys


usbPort        = '/dev/tty.usbserial-DN02IORF' # The serial port to use, under Linux and OS X something like "/dev/tty.usbserial" and under Windows something like "COM1"
dots           = ['00', '10', '01', '11']      # All possible dot combinations, unfortunately the clock is only able to witch the upper and lower dots together
colors         = ['000000', 'ffffff']          # Add as many colors as you want in 3-byte hex format
colorAnimation = True                          # Set this to False to switch off the annoying color cycle animation ^^
mySerial       = 0
interval       = 0


def connectNixie():
  global mySerial
  mySerial = serial.Serial(usbPort, 115200, timeout = 1)

def disconnectNixie():
  global mySerial
  sendData('xxxxxx') # empty display
  time.sleep(0.1)
  mySerial.close()

def getTimeString():
  return datetime.now().strftime("%H%M%S")

def sendData(string, dot = 0, color = 0):
  global mySerial
  mySerial.write((string + dots[dot] + colors[color] + "\n").encode('ascii'))

def setColorAnimation():
  if(colorAnimation):
    time.sleep(3)
    mySerial.write("05\n".encode('ascii')) # hex string representing the color cycle speed

def getDelay():
  global interval
  interval += 1
  return max(interval - time.time(), 0) # if negative say 0 to catch up to real time

def setInterval():
  global interval
  interval = int(time.time()) + 0.1 # enforce 100 ms after the second

def signalHandler(signal, frame):
  disconnectNixie()
  sys.exit(0) # exit script

def handleCtrlC():
  print('Press Ctrl+C to exit')
  signal.signal(signal.SIGINT, signalHandler) # handle Ctrl + c


# init script
handleCtrlC()
connectNixie()
setColorAnimation()
setInterval()

# endless loop (until script exits)
while True:
  now = getTimeString()
  sendData(now, 1)
  time.sleep(0.5)
  sendData(now, 2)
  time.sleep(getDelay()) # get an exact delay to avoid time drift
