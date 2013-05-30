#include "State.h"
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
