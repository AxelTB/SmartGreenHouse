#include <SGH.h>
#include <SD.h>
///Log method implementations File

/***
 * Return:
 * 0 -> OK
 * -1 -> File Error
 * 1 -> Sd not initialized
 */
int SGH::saveStatsSTD()
{
#ifdef SERIALOUT
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
    Serial.print(this->state.light);
    Serial.print(",");
    Serial.print(this->state.flight);
    Serial.print(",");
    Serial.print(this->state.fhumidity);
    Serial.print(",");
    Serial.print(this->state.outFan);
    Serial.println();
#endif
    if(!this->state.sdstatus)
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
    myFile.print(this->state.light);
    myFile.print(",");
    myFile.print(this->state.flight);
    myFile.print(",");
    myFile.print(this->state.fhumidity);
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
#ifdef SERIALOUT
    Serial.print((int) level);
    Serial.print(",");
    Serial.println(data);
#endif
    return 0;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
int SGH::logInit(uint8_t sdPin)
{
    pinMode(10, OUTPUT); //Needed to make sd work
    this->state.sdstatus=(SD.begin(sdPin)); //Save sd status

#ifdef SERIALOUT
Serial.begin(9600); // only required for testing
#endif
    return this->state.sdstatus;
}
