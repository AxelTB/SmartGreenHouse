#ifndef CICLETIMER_H
#define CICLETIMER_H
/*******************************************************************
*                   ==SmartGreenHouse==
*   Control Timer
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0 
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Timered Control Class for digital actuators
Control actuator with period and on time given
********************************************************************/

class ControlTimer
{
    public:
        ControlTimer() {}
        ControlTimer(long Periodms,long OnTimems);
        bool update(long mills);
        ~ControlTimer() {}
    protected:
    private:
    long time,OffTime,OnTime;
    bool status;
};

#endif // CICLETIMER_H
