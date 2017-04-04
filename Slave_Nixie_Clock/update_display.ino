/*
 *  Displays a "string" on the nixie tubes and lights the nixie points and led's
 */
 
const unsigned long   one                = 1;
const          byte   displayDelay       = 2; // in millis per block (3 blocks per frame):  0=~1430fps;  1=~325fps;  2=164fps;  3=109fps;  4=83fps;  5=66fps;  6=54fps;
               String displayOldBuffer   = "";
      unsigned long   displayData        = 0;
               byte   displayBlock       = 0;
      unsigned long   displayLastRefresh = 0;

void updateDisplay() {
  if(millis() - displayLastRefresh >= displayDelay) {
    writeNixieBlock();
    setLight();
    displayLastRefresh = millis();
  }
}
               
void writeNixieBlock() {
  enablePinLow;
  writeData(createDisplayData(displayBlock * 2));
  enablePinHigh;
  switchAnodes();
  displayBlock++;
  if(displayBlock > 2) displayBlock = 0;
}

void setLight() {
  if(displayBuffer != displayOldBuffer) {
    digitalWrite(pinUpperDots, displayBuffer.substring(6, 7) == "1" ? HIGH : LOW);
    digitalWrite(pinLowerDots, displayBuffer.substring(7, 8) == "1" ? HIGH : LOW);
    if(colorAnimationSpeed == 0) {
      analogWrite(pinRLed, hexStringToByte(displayBuffer, 8)); 
      analogWrite(pinGLed, hexStringToByte(displayBuffer, 10));
      analogWrite(pinBLed, hexStringToByte(displayBuffer, 12));
    }
    displayOldBuffer = displayBuffer;
  }
}

void clearDisplay() {
  displayBuffer = displayClear;
  writeNixieBlock();
  setLight();
  anode0Low;
  anode1Low;
  anode2Low;
}

unsigned long createDisplayData(byte pos) {
  displayData = 0;
  if(isDigit(displayBuffer.charAt(pos)))     displayData  = one << displayBuffer.charAt(pos)     - 48;      // shift high bit position by number to display
  if(isDigit(displayBuffer.charAt(pos + 1))) displayData |= one << displayBuffer.charAt(pos + 1) - 48 + 10;
  return ~displayData;
}

void writeData(unsigned long data) {
  SPI.transfer(data >> 16);
  SPI.transfer(data >> 8);
  SPI.transfer(data);
}

void switchAnodes() {
  if(displayBlock == 0) {
    anode0High;           anode2Low;
  } else if(displayBlock == 1) {
    anode0Low; anode1High;          
  } else {
               anode1Low; anode2High;
  }
}

byte hexStringToByte(String str, byte pos) {
  return byte(strtol(str.substring(pos, pos + 2).c_str(), NULL, 16));
}

