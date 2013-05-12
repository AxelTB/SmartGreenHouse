/*******************************************************************
*                   ==SmartGreenHouse==
*   Control On/Off Class
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Control Class for digital actuators
Activate an actuator if a state condition is below the target. Implements histeresys, Max On Time and minimum transition time separately.
********************************************************************/
/*
Day 21~23
 Night 18
 */

#define LOWBOUND 1
#define HIGHBOUND 30

#define MAXFAULT 10

#define MAXONTIME  (300000l) //5 min
#define MINOFFTIME (300000l) //5 min
#define MINONTIME (60000) //1 min

#define MEDTIME ((float) (MINONTIME+MINOFFTIME)/1000)
class ControlOnOff
{
public:
    ControlOnOff();
    ControlOnOff(short target,unsigned short delta);

    void setup(short target,unsigned short delta);

//Update & return status
    bool updateStatus(float val);
//Get current status
    bool getStatus();



private:
    bool status;
    //Treesholds
    short min,max;
};
