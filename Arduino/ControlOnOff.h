#ifndef CONTROLONOFF_H
#define CONTROLONOFF_H
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

#include <Arduino.h>
#define MAXFAULT 10

#define MAXONTIME  (300000l) //5 min
#define MINOFFTIME (300000l) //5 min
#define MINONTIME (60000) //1 min

#define MEDTIME ((float) (MINONTIME+MINOFFTIME)/1000)
class ControlOnOff
{
public:
    void setup(unsigned short delta);
    void setup(unsigned short delta,int HighBound,int LowBound);
    void setup(unsigned short delta,unsigned long MaxOnTime,unsigned long MinOnTime,unsigned long MinOffTime,int HighBound,int LowBound);
    int updateStatus(float val);
    unsigned short getStatus();
    void setTarget(float Target);
    float getTarget();
    unsigned short adaptiveUpdate(float val);

    uint8_t update(float val);
    void DebugStatistic(char *dbgstr);
private:

    short status;
    unsigned short nfault,delta;
    unsigned long uptime,lasttransition,nextdelay;

    //Treesholds in common and differential
    float tcommon,tdiff;
    //Target valerature
    float target;
    //Time constants
    unsigned long MaxOnTime,MinOnTime,MinOffTime;
    //Maximum ratings
    int HighBound,LowBound;
    //Statistic variables
    float stmedian,sthigh,stlow;
};
#endif
