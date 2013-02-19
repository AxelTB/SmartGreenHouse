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
/** @brief update
  *
  * @todo: document this function
  */
bool ControlTimer::update(long mills)
{
    long dt=mills-this->time;
    if(status && dt>this->OnTime)
    {
        this->status=0;
        this->time=mills;
    }
    else if(!status && dt>this->OffTime)
    {
        this->status=1;
        this->time=mills;
    }
    
    return this->status;
}

/** @brief ControlTimer
  *
  * @todo: document this function
  */
 ControlTimer::ControlTimer(long Periodms,long OnTimems)
{
    this->OffTime=Periodms-OnTimems;
    this->OnTime=OnTimems;

    this->time=0;
    this->status=1;
}


#endif // CICLETIMER_H
