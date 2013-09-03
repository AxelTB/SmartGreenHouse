/*******************************************************************
*                   ==SmartGreenHouse==
*   SerialWriter
*   Created: 3/09/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
********************************************************************/
#ifndef SERIALWRITER_H
#define SERIALWRITER_H
#include <HardwareSerial.h>
#include "SGHWriter.h"
#include <Arduino.h>
class SerialWriter : public SGHWriter
{
public:
    /** Default constructor */
    SerialWriter(int baudrate=9600);
    virtual int write(const char* str);
    virtual int write(int val);
    void setBaudrate(int baudrate);
    /** Default destructor */
    virtual ~SerialWriter();
protected:
private:
};

#endif // SERIALWRITER_H
