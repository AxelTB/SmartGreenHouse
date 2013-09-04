#include "SDWriter.h"

/** @brief write
  *
  * @todo: document this function
  */
int SDWriter::write(const char* str)
{
    uint8_t ret=0;
 if(this->status=2)
 {
    SD.print(val);
    SD.print(" ");
}
else
ret=1;
    return ret+this->next.write(val);
}

/** @brief write
  *
  * @todo: document this function
  */
int SDWriter::write(int val)
{
    this->next.write(str);
    Serial.println(str)
}

/** @brief SDWriter
  *
  * @todo: document this function
  */
SDWriter::SDWriter(uint8_t sdPin)
{
    pinMode(10, OUTPUT);
    this->status=0;
    this->sdPin=sdPin;
}

/** @brief SDWriter Null constructor.
  * Sets pin 10 as output
  *
  */
SDWriter::SDWriter()
{
    pinMode(10, OUTPUT);
    this->status=0; //Reset status
    this->sdPin=SD_CHIP_SELECT_PIN; //Use standard SDLibrary pin
}
/** @brief Initialize SD Card and open file
  *
  * Returns:    0 All right
  *             -1 Unable to initialize SD
  *             -2 Unable to open file
  *             -3 Really bad error (Is something writing on random memory location?)
  */
int SDWriter::initSD()
{
    switch (this->status)
    {
    case 0: //Reset
        if(SD.begin(this->sdPin)) //Initialize SD
            this->status=1; //SD Initialized
        else
            return -1;

    case 1: //SD Initialized (File close)
        this->fout=SD.open(SDWFILENAME,FILE_WRITE); //Open file
        if(!this->fout)
            return -2; //File not open
        else
            this->status=2; //File open, ready to write
    case 2: //SD Initialized, file open, nothing to do.
        break;

    default: //WTF??? This shouldn't happen
        this->status=0; //Reset all
        return -3; //Unknown error
    }


    return 0;
}

/** @brief setPin
  *
  * @todo: document this function
  */
void SDWriter::setPin(uint8_t sdPin)
{
    this->sdPin=sdPin;
}

