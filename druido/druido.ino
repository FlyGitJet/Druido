


#include "SensHC04.h"
#include "DiffDrive.h"
#include "Sensoren.h"
#include <Servo.h>



// *************************************************************************** //
// Druido Hardware Konfiguration                                               //
const int S_Distrig_L = 48; // Left
const int S_Disecho_L = 49; // Left
const int S_Distrig_M = 50; // Mitte
const int S_Disecho_M = 51; // Mitte
const int S_Distrig_R = 52; // Rechts
const int S_Disecho_R = 53; // Rechts 


const int S_Lin_M = A0;
const int S_Lin_L = A2;
const int S_Lin_R = A4;

const int S_LDR1 = A1;
const int S_LDR2 = A3;
const int DIST = A5;

const int S_LiPo = A6; 
// *************************************************************************** //




// Ultraschallsensoren ******************************************************* //
SensHC04 sensor_L(S_Distrig_L, S_Disecho_L); // create servo object to control a servo
SensHC04 sensor_M(S_Distrig_M, S_Disecho_M); // create servo object to control a servo
SensHC04 sensor_R(S_Distrig_R, S_Disecho_R); // create servo object to control a servo


// Analoge Sensoren am Druido ************************************************ //
Sensoren sensor;


// Antrieb ******************************************************************* //
DiffDrive antrieb; 


// Servos ******************************************************************** //
Servo servos;  // create servo object to control a servo


void setup() {
  Serial.begin(9600);
  
  servos.attach(9);  // attaches the servo on pin 9 to the servo object
  servos.write(90);   // tell servo to go to position in variable 'pos'

  
  sensor.LDR(LINKS, S_LDR1);
  sensor.LDR(RECHTS, S_LDR2);
}



int Dist_L = 100;
int Dist_M = 100;
int Dist_R = 100;

int drehung = 0;


void loop() {
 drehung = 0;

 while (true) {
    Serial.print(analogRead(S_Lin_M));
    Serial.println();
    delay(50);
 }
 Dist_L = sensor_L.entfernung();
 Dist_M = sensor_M.entfernung();
 Dist_R = sensor_R.entfernung();





/* reagieren auf Hindernisse 
 if ( Dist_L<80 ) {
  drehung = (80-Dist_L)/2;
 }
 
 if ( Dist_R<80) {
  drehung = -1 * ((80-Dist_R)/2);  
 }
*/

/* reagieren auf Lich */
  drehung = sensor.Lichtrichtung();
 

 if ( Dist_M < 20 ) { // Hinderniss zu nah, drehen
   antrieb.fahren(0, 100); 
   delay(100);  
 } else { // Hinderniss noch entfernt, ausweichen   
   antrieb.fahren(60, drehung);  
 }

 Serial.print("    Drehung ");
 Serial.println(drehung);
 delay(100);


}
