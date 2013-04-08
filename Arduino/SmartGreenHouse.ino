#include <dht11.h>
#include "Fan.h"
/*******************************************************************
 *                   ==SmartGreenHouse==
 *   Main sketch
 *   Created: 17/02/2013
 *   Author:  Ax
 *   License: CC BY-SA 3.0 
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
 * All available documentation on https://github.com/AxelTB/SmartGreenHouse
 ********************************************************************/

#include <SD.h>
#include <Wire.h>
#include "Actuators.h"
#include "Sensors.h"
#include "State.h"

File myFile;
short tret;

Actuators act;
Sensors sens;
State state;
long time;

void setup()
{
  Serial.begin(9600); // only required for testing
  Serial.print("Setup...");
  state.setup(SDPIN);
//Actuators-----------------------------------
   
  act.setup();
//Sensors--------------------------------------
  sens.setup();
 
  Serial.println("DONE!");
  time=millis();
}


double temp;
int humidity;


void loop()
{
  sens.update(&state);
  act.update(&state);

  //SD Log -------------------------------------------
  state.saveStats();
  //Wait for looptime---------------------------------------------
  while(millis()-time<LOOPT*1000);
}







