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

//Target temperature and humidity
#define TTEMP 23
#define TDELTA 8

#define THUM  40
#define HDELTA 10

class State
{
public:
  //Target variable in common and differential
  int tTempc, tTempd;
  int tHumc, tHumd;
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
  int setup(short sdpin);
  int saveStats();
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

int State::setup(short sdpin)
{
  pinMode(10, OUTPUT); //Needed to make sd work
  sdstatus=(SD.begin(sdpin));

  //Initialize error variable
  this->esensors=0;
  this->eactuators=0;

  this->heater=0;
  this->heaterCable=0;
  this->humidifier=0;
  this->outFan=255;

  this->tTempc=TTEMP;
  this->tTempd=TDELTA;
  this->tHumc=THUM;
  this->tHumd=HDELTA;
}
/***
 * Return:
 * 0 -> OK
 * -1 -> File Error
 * 1 -> Sd not initialized
 */
int State::saveStats()
{
#ifdef SERIALOUT
  Serial.print(this->temp);
  Serial.print(",");
  Serial.print(this->heater);
  Serial.print(",");
  Serial.print(this->humidity);
  Serial.print(",");
  Serial.print(this->humidifier);
  Serial.print(",");
  Serial.print(this->heaterCable);
  Serial.print(",");
  Serial.print(this->light);
  Serial.print(",");
  Serial.print(this->flight);
  Serial.print(",");
  Serial.print(this->fhumidity);
  Serial.print(",");
  Serial.print(this->outFan);
  Serial.println();
#endif
  if(!this->sdstatus)
  {
    Serial.println("SD Error");
    return 1;
  }

  File myFile = SD.open("temp.txt",FILE_WRITE);
  if (!myFile)
  {
#ifdef SERIALOUT
    Serial.println("Error opening file");
#endif
    return -1;
  }


  myFile.print(this->temp);
  myFile.print(",");
  myFile.print(this->heater);
  myFile.print(",");
  myFile.print(this->humidity);
  myFile.print(",");
  myFile.print(this->humidifier);
  myFile.print(",");
  myFile.print(this->heaterCable);
  myFile.print(",");
  myFile.print(this->light);
  myFile.print(",");
  myFile.print(this->flight);
  myFile.print(",");
  myFile.print(this->fhumidity);
  myFile.print(",");
  myFile.print(this->outFan);
  myFile.println();
  myFile.close();
  //Serial out---------------------------------------


  return 0;
}

int State::log(byte level,char *data)
{
  if(!this->sdstatus)
    return 1;

  File myFile = SD.open("log.txt",FILE_WRITE);
  if (!myFile)
    return -1;

  myFile.print((int) level);
  myFile.print(",");
  myFile.println(data);

  myFile.close();
#ifdef SERIALOUT
  Serial.print((int) level);
  Serial.print(",");
  Serial.println(data);
#endif
  return 0;
}
#endif // STATE_H



