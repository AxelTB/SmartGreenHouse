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
    this->next.write(val);
    Serial.print(val);
    Serial.print(" ");
}

/** @brief write
  *
  * @todo: document this function
  */
int SerialWriter::write(const char* str)
{
    this->next.write(str);
    Serial.println(str)
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

