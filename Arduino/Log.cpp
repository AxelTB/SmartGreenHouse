/*******************************************************************
 *                   ==SmartGreenHouse==
 *   Log method implementations File
 *   Created: 17/02/2013
 *   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
 * Log
 *
 ********************************************************************/
#include "Log.h"

Log::Log()
{
    //ctor
}

Log::~Log()
{
    //dtor
}



/***
 * Return:
 * 0 -> OK
 * -1 -> File Error
 * 1 -> Sd not initialized

int SGH::saveStats()
{
if(this->state.serialOut)
{
    Serial.print(this->state.temp);
    Serial.print(",");
    Serial.print(this->state.humidity);
    Serial.print(",");
    Serial.print(this->state.heater);
    Serial.print(",");
    Serial.print(this->state.humidifier);
    Serial.print(",");
    Serial.print(this->state.outFan);
    Serial.println();
}
    if(!this->state.sdstatus)
    {
        Serial.println("SD Error");
        return 1;
    }

    File myFile = SD.open("data.txt",FILE_WRITE);
    if (!myFile)
    {
if(this->state.serialOut)
        Serial.println("Error opening file");

        return -1;
    }

#define Serial myFile //Extremely lazy define
    Serial.print(this->state.temp);
    Serial.print(",");
    Serial.print(this->state.humidity);
    Serial.print(",");
    Serial.print(this->state.heater);
    Serial.print(",");
    Serial.print(this->state.humidifier);
    Serial.print(",");
    Serial.print(this->state.outFan);
    Serial.println();
#undef Serial

    return 0;
}

int SGH::log(byte level,char *data)
{
    if(!this->state.sdstatus)
        return 1;

    File myFile = SD.open("log.txt",FILE_WRITE);
    if (!myFile)
        return -1;

    myFile.print((int) level);
    myFile.print(",");
    myFile.println(data);

    myFile.close();
if(this->state.serialOut)
{

    Serial.print((int) level);
    Serial.print(",");
    Serial.println(data);
}
    return 0;
}
*/
/** @brief (one liner)
  *
  * (documentation goes here)
  */
int Log::init(uint8_t sdPin,int baudrate)
{
    pinMode(10, OUTPUT); //Needed to make sd work
    this->sdstatus=(SD.begin(sdPin)); //Save sd status

    if(this->baudrate!=0)
    {
        Serial.begin(baudrate); //Enable Serial Output
        Serial.println("Serial Setup done");
    }

    return this->state.sdstatus;
}
/** @brief operator<<
  *
  * @todo: document this function
  */
int Log::operator<<(int var)
{

}

/** @brief operator<<
  *
  * @todo: document this function
  */
int Log::operator<<(const char *str)
{

}

/** @brief operator<<
  *
  * @todo: document this function
  */
int Log::operator<<(Loop l)
{

}


