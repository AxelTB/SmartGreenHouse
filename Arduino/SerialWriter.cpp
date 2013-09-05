/*******************************************************************
*                   ==SmartGreenHouse==
*   SerialWriter
*   Created: 3/09/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
********************************************************************/
#include "SerialWriter.h"

/** @brief setBaudrate
  *
  * @todo: document this function
  */
void SerialWriter::setBaudrate(int baudrate)
{
if(baudrate!=0)
    {
        Serial.begin(baudrate); //Enable Serial Output
        Serial.println("Serial Setup done");
    }
}

/** @brief write
  *
  * @todo: document this function
  */
int SerialWriter::write(int val)
{
    Serial.print(val); //Write val
    Serial.print(" ");

    if(this->next!=0)
    return this->next->write(val);
    else
        return 1;

}

/** @brief write
  *
  * @todo: document this function
  */
int SerialWriter::write(const char* str)
{
    Serial.println(str);
    if(this->next!=0)
    return 1+this->next->write(str);
    else
        return 1;
}



/** @brief SerialWriter
  *
  * @todo: document this function
  */
 SerialWriter::SerialWriter(int baudrate)
{
    setBaudrate(baudrate);
}

/** @brief ~SerialWriter
  *
  * @todo: document this function
  */
 SerialWriter::~SerialWriter()
{

}

