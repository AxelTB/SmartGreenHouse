/*******************************************************************
*                   ==SmartGreenHouse==
*   Timecounter Class
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Simply returns elapsed time from last getElapsedMillis Call or creation
********************************************************************/

#ifndef TIMECOUNTER_H
#define TIMECOUNTER_H

class TimeCounter
{
    public:
        TimeCounter();

        unsigned long getElapsedMillis();
    protected:
        unsigned long getElapsedMillis(unsigned long startms);
        unsigned long start; //millis() counter at start
    private:

};

#endif // TIMECOUNTER_H
