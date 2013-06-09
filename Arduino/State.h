/*******************************************************************
 *                   ==SmartGreenHouse==
 *   State
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

#include <SD.h>
#define LOOPT 2 //Loop Time
#define SDPIN 9 //ALSO 11,12 and 13
//Undefine to disable serial
#define SERIALOUT

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
  //Target variable in common and differential
  //int tTempc, tTempd;
  //int tHumc, tHumd;
  //Actuators---------------
  boolean heater,humidifier,heaterCable;
  unsigned short outFan;
  //State variable----------
  float temp,humidity;
  short light;
  float fhumidity,flight;
  boolean level;

  //Errors variable---------
  byte esensors,eactuators;

  //Time evaluation---------
  //Milliseconds from start
  long milliseconds;
  //SD------------------------
  boolean sdstatus;
  int setupSTD(short sdpin);
  int saveStatsSTD();
  int log(byte level,char *data);

  //Error flags for sensors---------------------------------------------------------------
  static const byte ESENS_DHTERR=0b1;
  static const byte ESENS_TOUTOFBOUND=0b10;
  static const byte ESENS_HOUTOFBOUND=0b100;
  //static const byte ESENS_HOUTOFBOUND=0b100;

  //Error flags for actuators
  static const byte EACT_BHO=0b1;

  //Loglevel
  static const unsigned short CRITICAL=3;
  static const unsigned short ERROR=2;
  static const unsigned short INFORMATION=1;
  static const unsigned short DEBUG=0;
protected:

private:
};


#endif // STATE_H



