/*
 *  Setup
 */

void setup() {
  pinMode(pinLatchEnable, OUTPUT);
  pinMode(pinAnode0, OUTPUT);
  pinMode(pinAnode1, OUTPUT);
  pinMode(pinAnode2, OUTPUT);
  pinMode(pinUpperDots, OUTPUT);
  pinMode(pinLowerDots, OUTPUT);
  pinMode(pinRLed, OUTPUT);
  pinMode(pinGLed, OUTPUT);
  pinMode(pinBLed, OUTPUT);
      
  SPI.begin(); 
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  
  Serial.begin(115200);
  Serial.setTimeout(20);
}

