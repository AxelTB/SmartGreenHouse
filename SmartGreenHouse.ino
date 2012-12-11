#include <dht11.h>

/***
 * SmartGreenHouse
 *
 * Author: Axxx
 */

#include <SD.h>
#include <Wire.h>
#include <bv4236.h>
#include "Actuators.h"
#include "Sensors.h"
//#include "Log.h"
#include "State.h"
#define FILENAME "temp.txt"

#define LEDPIN 13
#define SDPIN 9 //ALSO 11,12 and 13

File myFile;
short tret;

Actuators act;
Sensors sens;
State state;
void setup()
{
  Serial.begin(9600); // only required for testing
  Serial.print("Setup...");
  state.setup(SDPIN);
//Actuators-----------------------------------
  
  pinMode(LEDPIN,OUTPUT);  //Status led pin
  act.setup();
//Sensors--------------------------------------
  sens.setup();
 
  Serial.println("DONE!");
}


double temp;
int humidity;
void loop()
{
  sens.update(&state);
  act.update(&state);

  //SD Log -------------------------------------------
  state.saveStats();
  //---------------------------------------------
  delay(1000);
}







