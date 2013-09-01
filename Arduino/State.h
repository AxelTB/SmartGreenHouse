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

class State
{
public:
State();
  //Actuators---------------
  boolean heater, /**Heater status*/
  humidifier;      /**Humidifier status*/


  unsigned short outFan; /**Fan power (0-255)*/
  //State variable----------
  float temp, /**Temperature*/
  humidity; /***Humidity*/
  boolean level; /**Humidifier water sensor level status*/

  //Errors variable---------
  byte esensors,    /**Sensors error byte*/
  eactuators;       /***Actuators error byte*/

  //Time evaluation---------

  //long milliseconds;    /*** Milliseconds from start UNUSED*/
  //SD------------------------
  boolean sdstatus; /***SD Status*/

  //Error flags for sensors---------------------------------------------------------------
  static const byte ESENS_DHTERR=0b1;
  static const byte ESENS_TOUTOFBOUND=0b10;
  static const byte ESENS_HOUTOFBOUND=0b100;
  //static const byte ESENS_HOUTOFBOUND=0b100;

  //Error flags for actuators
  static const byte EACT_BHO=0b1;


    bool serialOut; ///Serial output active flag
protected:

private:
};


#endif // STATE_H



