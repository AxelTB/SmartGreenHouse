/*******************************************************************
 *                   ==SmartGreenHouse==
 *   State implementation file
 *   Created: 17/02/2013
 *   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
 * State
 * Contains state variable, target and actuator state.
 ********************************************************************/
#include "State.h"
State::State()
{
  //Initialize error variable
  this->esensors=0;
  this->eactuators=0;

  this->heater=0;
  this->heaterCable=0;
  this->humidifier=0;
  this->outFan=255;

}

