#ifndef TIME_H
#define TIME_H
#include <inttypes.h>

typedef uint32_t time_sec;
typedef uint64_t time_millis;
/*******************************************************************
*                   ==SmartGreenHouse==
*   Time Class
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Static Class for time manipulation

Use on board timer to evaluate short period of time and fixes overflow (Every ~41 days)
********************************************************************/

class Time
{
public:
    static void init();
    static void init(uint8_t type); //Initialize with RTC
    ///
    static time_millis getMillis();

protected:
private:
    //Short time variable (till minutes)
    uint32_t millisH; //Contains the high byte
    long lastmillis; //To evaluate overflow
    //Long time variable
    unsigned short hour,
    day,
    month,
    year;//If you are still using this code and it's 2190 you may wanna changhe this

class softwareTimeCounter{
    public:
}
};

#endif // TIME_H
