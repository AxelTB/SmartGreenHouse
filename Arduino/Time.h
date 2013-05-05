#ifndef TIME_H
#define TIME_H
#include <inttypes.h>
/*******************************************************************
*                   ==SmartGreenHouse==
*   Time Class
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Static Class for time manipulation
********************************************************************/

class Time
{
    public:
    static void init();
    static void init(uint8_t type); //Initialize with RTC
    ///Return millis() value modded to be more than 49 days...
    static uint64_t getMillis();
    protected:
    private:
        uint32_t millisH; //Contains the high byte
};

#endif // TIME_H
