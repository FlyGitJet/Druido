#ifndef Sensoren_h
#define Sensoren_h

#include <Arduino.h>

#define LINKS 0
#define RECHTS 1

class Sensoren {
    private:
    byte LDR_L_PIN = 0;
    byte LDR_R_PIN = 0;

    public:
      Sensoren() {
        
      }

      void LDR(boolean SEITE, byte LDR_PIN) {
        if ( SEITE==LINKS ) {
          this->LDR_L_PIN = LDR_PIN; 
          pinMode(this->LDR_L_PIN, INPUT);
        } else {
          this->LDR_R_PIN = LDR_PIN;
          pinMode(this->LDR_R_PIN, INPUT);
        }
      }

      int Lichtrichtung() {
        float temp;
        int LDR1 = analogRead(LDR_L_PIN);
        int LDR2 = analogRead(LDR_R_PIN); 

        if ( LDR1 > LDR2 )  {

          temp = LDR2; 
          temp = 1 - (temp / LDR1);      
          temp = temp * 100;                 
          return (int)temp;
        } else {
          
          temp = LDR1; 
          temp = 1 - (temp / LDR2);           
          temp = temp * -100; 
          return (int)temp;
        }
      }

      int Licht() {     
        return (analogRead(LDR_L_PIN) + analogRead(LDR_R_PIN))/2;
      }

    
}; // don't forget the semicolon at the end of the class

#endif
