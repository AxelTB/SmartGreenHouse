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
#include "SerialWriter.h"
#include "SDWriter.h"
Log::Log()
{

}

Log::~Log()
{
    //dtor
}

void Log::init(uint8_t sdPin,int baudrate)
{
    this->w.addWriter(new SerialWriter(baudrate));
    this->w.addWriter(new SDWriter(sdPin));
}
/** @brief Sets loop's state variable according to var
  *
  *
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


/** @brief Writer adding operator
  *
  * Calls the same operator on the writer
  */
int Log::operator<<(SGHWriter *w)
{
        this->w.addWriter(w); //Add Writer
}

