#ifndef STATE_H
#define STATE_H

#include <SD.h>

//Undefine to disable serial
#define SERIALOUT


class State
{
public:
  //Actuators---------------
  boolean heater,humidifier,heaterCable;
  //State variable----------
  float temp;
  short humidity,light;
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

  //Error flags for sensors
  static const byte ESENS_DHT11ERR=0b1;
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
  Serial.println();
#endif
  if(!this->sdstatus)
    return 1;

  File myFile = SD.open("temp.txt",FILE_WRITE);
  if (!myFile)
    return -1;

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

  Serial.print((int) level);
  Serial.print(",");
  Serial.println(data);

  return 0;
}
#endif // STATE_H

