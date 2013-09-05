/*******************************************************************
*                   ==SmartGreenHouse==
*   DigitalOut class
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Standard digital output.
Implements various control function and minimum/maximum time control.
********************************************************************/

#ifndef DIGITALOUT_H
#define DIGITALOUT_H
#include <Arduino.h>

#include "TimeAlarm.h"

class DigitalOut
{
public:
    /***
    pin -> Arduino pin
    MaxOnTimeS ->Maximum On time sec (0 means infinite)
    MinOnTimeS -> Min On sec
    MinOffTimeS -> Min Off sec
    MinOffTimeS -> Min Off sec
    **/
    DigitalOut();
    DigitalOut(uint8_t pin);
    DigitalOut(uint8_t pin,uint32_t MaxOnTimeS,unsigned long MinOnTimeS,unsigned long MaxOffTimeS, unsigned long MinOffTimeS);

    DigitalOut(uint8_t pin,uint32_t OnTimemS,uint32_t OffTimemS); ///Constructor for simple timed output

    void init(uint8_t pin);
    void init(uint8_t pin,uint32_t MaxOnTimeS,unsigned long MinOnTimeS,unsigned long MaxOffTimeS,unsigned long MinOffTimeS);
    void init(uint8_t pin,uint32_t OnTimeS,uint32_t OffTimeS); ///Initialize as simple timed output

///All Return true if set HIGH false if LOW
    bool on();
    bool off();
    bool commute();
    bool set(int value);
    bool set(short value);
    bool set(uint8_t value);
    inline bool set(bool value);
    bool get();
    bool isNull();
//Emergency routine
    void forceOff();
protected:
    uint8_t pin;
    bool status;
    TimeAlarm timerMin,
    timerMax;
    uint32_t MaxOnTime,MaxOffTime;
    unsigned long MinOnTime,MinOffTime;
private:
};

#endif // DIGITALOUT_H
