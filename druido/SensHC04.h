#ifndef SensHC04_h
#define SensHC04_h

#include <Arduino.h>
class SensHC04 {
  private:
    byte trigger_PIN = 0;
    byte echo_PIN = 0;

    public:
      SensHC04(byte trigger, byte echo) {
        this-> trigger_PIN = trigger;
        this-> echo_PIN = echo;
      init();
    }

    void init() {
      pinMode(trigger_PIN, OUTPUT);
      pinMode(echo_PIN, INPUT);
    }

    int entfernung() { 
      // int als Rückgabe ist in Ordnung, weil der Wert nicht über 500 geht
      long duration = 0;
      long distance = 0;
      digitalWrite(trigger_PIN, LOW);
      delayMicroseconds(2); // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigger_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger_PIN, LOW);

      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echo_PIN, HIGH, 30000);
      if ( duration > 0 ) {
        distance = duration*0.034/2;
      } else { // ups, Fehlmessung, könnte unendlich, könnte aber auch ganz nah sein... wir ignorieren ganz nah und gehen auf max.
        distance = 500;
      }
      // Calculating the distance
      
      return(distance);
    }


    
}; // don't forget the semicolon at the end of the class
#endif
