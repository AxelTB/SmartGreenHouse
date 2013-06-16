/*******************************************************************
 *                   ==SmartGreenHouse==
 *   State class
 *   Created: 17/02/2013
 *   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
 * State
 * Contains state variable, target and actuator state.
 ********************************************************************/
#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

#define LOOPT 2 //Loop Time
#define SDPIN 9 //ALSO 11,12 and 13


/*** UNUSED
//Target temperature and humidity
#define TTEMP 23
#define TDELTA 8

#define THUM  40
#define HDELTA 10
*/
class State
{
public:
State();
  //Target variable in common and differential
  //int tTempc, tTempd;
  //int tHumc, tHumd;
  //Actuators---------------
  boolean heater,humidifier,heaterCable;
  unsigned short outFan;
  //State variable----------
  float temp,humidity;
  short light;
  boolean level;

  //Errors variable---------
  byte esensors,eactuators;

  //Time evaluation---------
  //Milliseconds from start
  long milliseconds;
  //SD------------------------
  boolean sdstatus;

  //Error flags for sensors---------------------------------------------------------------
  static const byte ESENS_DHTERR=0b1;
  static const byte ESENS_TOUTOFBOUND=0b10;
  static const byte ESENS_HOUTOFBOUND=0b100;
  //static const byte ESENS_HOUTOFBOUND=0b100;

  //Error flags for actuators
  static const byte EACT_BHO=0b1;


    bool serialOut;
protected:

private:
};


#endif // STATE_H



