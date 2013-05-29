/*******************************************************************
 *                   ==SmartGreenHouse==
 *   Actuator Class
 *   Created: 17/02/2013
 *   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
 *All actuators code goes there
 ********************************************************************/
#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "State.h"
#include "Comparator.h"
#include "ControlTimer.h"

#include "DigitalOut.h"
#include "Fan.h"

#define HEATPIN 2
#define HUMPIN 3
#define HEATCABLEPIN 4
#define OUTFPIN   10

#define HUMCONTROLLED

#define HCDELTA 4

class Actuators
{
public:
    int setup();
    ///Command actuators with data from state
    int update(State *state);
protected:
private:
    DigitalOut heater,
    humidifier,
    heatcable;
    //unsigned short heatpin,humpin;
    Comparator t,tc;
#ifndef HUMCONTROLLED
    ControlTimer cth;
#else
    Comparator h;
#endif
    Fan outFan;



};

#endif // ACTUATORS_H










