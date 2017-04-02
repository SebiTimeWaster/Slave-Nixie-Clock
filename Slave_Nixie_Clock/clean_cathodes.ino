/*
 *  Shows a rotating numbers animation to prevent cathode poisoning
 */
 
const          int    cleanAnimationDelay       = 200; // (ms)
               String cleanAnimation[10]        = {
                                                    "01234500000000",
                                                    "12345600000000",
                                                    "23456700000000",
                                                    "34567800000000",
                                                    "45678900000000",
                                                    "56789000000000",
                                                    "67890100000000",
                                                    "78901200000000",
                                                    "89012300000000",
                                                    "90123400000000"
                                                  };
               byte   cleanAnimationPointer     = 0;
      unsigned long   cleanAnimationLastRefresh = 0;
      
void cleanCathodes() {
  if(millis() - cleanAnimationLastRefresh >= cleanAnimationDelay) {
    displayBuffer = cleanAnimation[cleanAnimationPointer];
    
    cleanAnimationPointer++;
    if(cleanAnimationPointer > 9) cleanAnimationPointer = 0;
    
    cleanAnimationLastRefresh = millis();
  }
}

