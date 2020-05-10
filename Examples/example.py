#  The MIT License (MIT)
#
#  Slave Nixie Clock - Copyright (c) 2017 SebiTimeWaster
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.


import serial
import time
from datetime import datetime
import signal
import sys


usbPort        = ''                       # The serial port to use
                                          # Linux example: '/dev/ttyUSB0'
                                          # OS X example: '/dev/tty.usbserial-DN02IORF'
                                          # Windows example: 'COM1'
dots           = ['00', '10', '01', '11'] # All possible dot combinations, unfortunately the clock is only able to switch the upper and lower dots together
colors         = ['000000', 'ffffff']     # Add as many colors as you want in 3-byte hex format
colorAnimation = 5                        # The number defines the speed (0-255), set this to 0 to switch off the annoying color cycle animation
mySerial       = 0
timeBase       = 0
connected      = 0                        # 0=never connected;  1=connected;  2=disconnected


def connectNixie():
  global mySerial, connected
  try:
    mySerial = serial.Serial(usbPort, 115200, timeout = 1)
    connected = 1
    setColorAnimation()
    setTimeBase()
  except:
    if connected == 0: # if never connected exit
      raise
    else: # if already was connected try again
      connected = 2

def disconnectNixie():
  sendData('xxxxxx') # empty display
  if(colorAnimation > 0):
    sendColorAnimation(0) # stop color animation
  time.sleep(0.1)
  mySerial.close()

def reconnectNixie():
  global timeBase
  mySerial.close()
  time.sleep(10) # wait 10 seconds and try to reconnect
  connectNixie()

def getTimeString():
  return datetime.now().strftime("%H%M%S")

def sendData(string, dot = 0, color = 0):
  global connected
  try:
    mySerial.write((string + dots[dot] + colors[color] + "\n").encode('ascii'))
  except:
    connected = 2

def setColorAnimation():
  if(colorAnimation > 0):
    time.sleep(3)
    sendColorAnimation(colorAnimation) # color cycle speed

def sendColorAnimation(speed):
  global connected
  try:
    mySerial.write((("%0.2x" % speed) + "\n").encode('ascii')) # send hex string representing the color cycle speed
  except:
    connected = 2

def getRealDelay(desiredDelay):
  global timeBase
  timeBase += desiredDelay
  if timeBase - time.time() > 11 or timeBase - time.time() < -11: # when time base deviated too much (i.e. because of sleep mode or user set new time) reset time base
    setTimeBase();
  return max(timeBase - time.time(), 0) # if negative say 0 to catch up to real time

def setTimeBase():
  global timeBase
  timeBase = int(time.time()) + 0.1 # enforce 100 ms after the second

def signalHandler(signal, frame):
  disconnectNixie()
  sys.exit(0) # exit script

def handleCtrlC():
  print('Press Ctrl+C to exit')
  signal.signal(signal.SIGINT, signalHandler) # handle Ctrl + c


# init script
handleCtrlC()
connectNixie()

# endless loop (until script exits)
while True:
  if connected == 1:
    now = getTimeString()
    sendData(now, 1)
    time.sleep(getRealDelay(0.5)) # get an exact delay to avoid time drift
    sendData(now, 2)
    time.sleep(getRealDelay(0.5))
  else:
    reconnectNixie()
