
#ifndef DiffDrive_h
#define DiffDrive_h

#include <Arduino.h>
class DiffDrive {
  private:
    const byte ML_V_Pin = 4;
    const byte MR_R_Pin = 5;
    const byte ML_R_Pin = 6;
    const byte MR_V_Pin = 7;
    const int max_Speed = 250;
    int Rad_L = 0;
    int Rad_R = 0;
    float norm = 1;

  public:
    DiffDrive() {
    init();
  }

    void init() {
      pinMode(ML_V_Pin, OUTPUT);
      pinMode(ML_R_Pin, OUTPUT);
      pinMode(MR_V_Pin, OUTPUT);
      pinMode(MR_R_Pin, OUTPUT);
      halt();  
    }
    
    void halt() {
      digitalWrite(ML_V_Pin, LOW);
      digitalWrite(ML_R_Pin, LOW);
      digitalWrite(MR_V_Pin, LOW);
      digitalWrite(MR_R_Pin, LOW);
    }

    
    void fahren(int geradeaus, int drehen) {
      // Limit Range
      if ( geradeaus > 100 ) { geradeaus = 100; }
      if ( geradeaus < -100 ) { geradeaus = -100; }
      if ( drehen > 100 ) { drehen = 100; }
      if ( drehen < -100 ) { drehen = -100; }
                
      // Geschwindigkeit linear + drehen
      Rad_L = geradeaus + drehen;
      Rad_R = geradeaus - drehen;
      


      
      // Normieren
      norm = 1;
      if ( abs(Rad_L) > 100 ) { norm = 100.0/(float)Rad_L; norm = abs(norm); }

      Rad_L = Rad_L * norm;
      Rad_R = Rad_R * norm;
    
      // immer noch zu hoch?
      norm = 1;
      if ( abs(Rad_R > 100) ) { norm = 100.0/(float)Rad_R; norm = abs(norm); }
      
      Rad_L = Rad_L * norm;
      Rad_R = Rad_R * norm;

       
      this->Motoren(Rad_L, Rad_R);
    }
    
    void Motoren(int M_L, int M_R) {
    
      M_L = (M_L * max_Speed) / 100;
      M_R = (M_R * max_Speed) / 100;


      this->halt();
      
      if ( M_L > 0 ) {
        analogWrite(ML_V_Pin, M_L);
        Serial.print(" ML_V ");Serial.print(M_L);
      } else {
        analogWrite(ML_R_Pin, abs(M_L) );
        Serial.print(" ML_R ");Serial.print(M_L);
      }

      
      if ( M_R > 0 ) {
        analogWrite(MR_V_Pin, M_R);
        Serial.print(" MR_V ");Serial.print(M_R);
      } else {
        analogWrite(MR_R_Pin, abs(M_R));
        Serial.print(" MR_R ");Serial.print(M_R);
      }
    }
    
}; // don't forget the semicolon at the end of the class
#endif 
