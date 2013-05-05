#ifndef DIGITALOUT_H
#define DIGITALOUT_H
#include "Time.h"
/*******************************************************************
 *                   ==SmartGreenHouse==
 *   Digital Output Class
 *   Created: 17/02/2013
 *   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
 *All actuators code goes there
 ********************************************************************/

class DigitalOut
{
    public:
        DigitalOut();
/***
pin -> arduino pin
MaxOnTimeS ->Maximum On time sec
MinOnTimeS -> Min On sec
MinOffTimeS -> Min Off sec
forcedOffS -> Time to wait when forced off before accept new command (For cooling or stuff like this)
**/
        int init(int pin);
        int init(int pin,long MaxOnTimeS,unsigned long MinOnTimeS,unsigned long MinOffTimeS);

        int on();
        int off();
        int set(int value);
        int set(short value);
        int set(bool value);
    protected:

    private:
};

#endif // DIGITALOUT_H
