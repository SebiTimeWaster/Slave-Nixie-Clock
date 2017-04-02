/*
 *  Loop
 */
 
const unsigned long serialTimeout     = 61000; // 61 seconds after last serial string start cathode cleaning and stop color animation
const unsigned long cleanerTimeout    = 81000; // 81 seconds after last serial string stop cathode cleaning, clear display and stop updating display
               char serialBuffer[20];
               byte serialLength      = 0;
      unsigned long serialLastRefresh = 0;
               byte serialState       = 0; // 0=showing serial data;  1=cathode cleaning;  2="sleep" mode

void loop() {
  if(Serial.available() > 0) {
    serialLength = Serial.readBytesUntil('\n', serialBuffer, 19);
    
    if(serialState == 0 && serialLength == 2) {
      serialBuffer[2] = '\0'; // terminate buffer
      colorAnimationSpeed = byte(strtol(serialBuffer, NULL, 16));
      if(colorAnimationSpeed == 0) {
        resetColorAnimation();
      }
    }
    
    if(serialLength == 14) {
      serialBuffer[14] = '\0'; // terminate buffer to avoid pulling garbage into displayBuffer
      displayBuffer = serialBuffer;
      serialLastRefresh = millis();
      serialState = 0;
    }
  }

  if(serialState == 0 && millis() - serialLastRefresh >= serialTimeout) {
    serialState = 1;
    resetColorAnimation();
  }
  
  if(serialState == 1) {
    cleanCathodes();
  }
  
  if(serialState == 1 && millis() - serialLastRefresh >= cleanerTimeout) {
    serialState = 2;
    clearDisplay();
  }
  
  if(serialState < 2) {
    updateDisplay();
  }

  if(serialState == 0) {
    colorAnimation();
  }
}

