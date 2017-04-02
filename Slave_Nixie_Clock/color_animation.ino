/*
 *  Shows a color animation on the led's, this is independent from the display buffer and overwrites it
 */

const          byte  colorAnimationDelay       = 33; // (ms) 30fps is enough not to be visible by the human eye (only true for color animations)
               float colorAnimationSpeed       = 0; // 0=off;  1=1 color cyle per 133.3 seconds;  ...  255=1 color cyle per 0.52 seconds
               float colorAnimationposition    = 0;
      unsigned long  colorAnimationLastRefresh = 0;
               byte  colorAnimationRGB[3];

void colorAnimation() {
  if(colorAnimationSpeed > 0 && millis() - colorAnimationLastRefresh >= colorAnimationDelay) {
    colorAnimationposition += colorAnimationSpeed / 4000;
    if(colorAnimationposition >= 1) colorAnimationposition = 0;
    
    hToRgb();
    analogWrite(pinRLed, colorAnimationRGB[0]); 
    analogWrite(pinGLed, colorAnimationRGB[1]);
    analogWrite(pinBLed, colorAnimationRGB[2]);

    colorAnimationLastRefresh = millis();
  }
}

void resetColorAnimation() {
  colorAnimationSpeed    = 0;
  colorAnimationposition = 0;
  analogWrite(pinRLed, 0); 
  analogWrite(pinGLed, 0);
  analogWrite(pinBLed, 0);
}

// copied and modified from: https://github.com/ratkins/RGBConverter/blob/master/RGBConverter.cpp
void hToRgb() {
    int   i = int(colorAnimationposition * 6);
    float t = (colorAnimationposition * 6 - i) * 255;
    float q = 255 - t;

    switch(i % 6){
        case 0: colorAnimationRGB[0] = 255, colorAnimationRGB[1] = t,   colorAnimationRGB[2] = 0;   break;
        case 1: colorAnimationRGB[0] = q,   colorAnimationRGB[1] = 255, colorAnimationRGB[2] = 0;   break;
        case 2: colorAnimationRGB[0] = 0,   colorAnimationRGB[1] = 255, colorAnimationRGB[2] = t;   break;
        case 3: colorAnimationRGB[0] = 0,   colorAnimationRGB[1] = q,   colorAnimationRGB[2] = 255; break;
        case 4: colorAnimationRGB[0] = t,   colorAnimationRGB[1] = 0,   colorAnimationRGB[2] = 255; break;
        case 5: colorAnimationRGB[0] = 255, colorAnimationRGB[1] = 0,   colorAnimationRGB[2] = q;   break;
    }
}

