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

#include <SGH.h>
#include <SD.h>

/***
 * Return:
 * 0 -> OK
 * -1 -> File Error
 * 1 -> Sd not initialized
 */
int SGH::saveStats()
{
if(this->state.serialOut)
{
    Serial.print(this->state.temp);
    Serial.print(",");
    Serial.print(this->state.heater);
    Serial.print(",");
    Serial.print(this->state.humidity);
    Serial.print(",");
    Serial.print(this->state.humidifier);
    Serial.print(",");
    Serial.print(this->state.heaterCable);
    Serial.print(",");
    //Serial.print(this->state.light);
    Serial.print("666");//Temporary bho
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


    myFile.print(this->state.temp);
    myFile.print(",");
    myFile.print(this->state.heater);
    myFile.print(",");
    myFile.print(this->state.humidity);
    myFile.print(",");
    myFile.print(this->state.humidifier);
    myFile.print(",");
    myFile.print(this->state.heaterCable);
    myFile.print(",");
    //myFile.print(this->state.light);
    myFile.print(666);
    myFile.print(",");
    myFile.print(this->state.outFan);
    myFile.println();
    myFile.close();
    //Serial out---------------------------------------


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

/** @brief (one liner)
  *
  * (documentation goes here)
  */
int SGH::logInit(uint8_t sdPin,bool serialOut)
{
    pinMode(10, OUTPUT); //Needed to make sd work
    this->state.sdstatus=(SD.begin(sdPin)); //Save sd status

    this->state.serialOut=serialOut; //Save serial output flag

    if(this->state.serialOut)
    {
        Serial.begin(9600); //Enable Serial Output
        Serial.println("Serial Setup done");
    }

    return this->state.sdstatus;
}
