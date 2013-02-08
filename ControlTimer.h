#ifndef CICLETIMER_H
#define CICLETIMER_H


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
