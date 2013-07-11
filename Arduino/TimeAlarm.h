/*******************************************************************
*                   ==SmartGreenHouse==
*   TimeAlarm Class
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Only indicates if a defined timeout elapsed
********************************************************************/

#ifndef TIMEALARM_H
#define TIMEALARM_H

#include "TimeCounter.h"


class TimeAlarm : protected TimeCounter
{
    public:
        TimeAlarm();
        TimeAlarm(unsigned long timeoutms);

        void set(unsigned long timeoutms);
        void reset();
        bool isElapsed();
        void kill();

    protected:
        unsigned long timeout;
        bool active;
    private:
};

#endif // TIMEALARM_H
