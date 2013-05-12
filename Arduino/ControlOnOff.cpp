#include "ControlOnOff.h"


/** @brief getStatus
  *
  * @todo: document this function
  */
bool ControlOnOff::getStatus()
{
    return this->status;
}

/** @brief updateStatus
  *
  * @todo: document this function
  */
bool ControlOnOff::updateStatus(float val)
{
    if(val>this->max)
        this->status=1;
    else if (val<this->min)
        this->status=0;

    return this->status;
}

/** @brief setup
  *
  * @todo: document this function
  */
void ControlOnOff::setup(short target,unsigned short delta)
{
    //Evaluate max and min
    this->max=target+delta/2;
    this->min=target-delta/2;


}

/** @brief ControlOnOff
  *
  * @todo: document this function
  */
 ControlOnOff::ControlOnOff(short target,unsigned short delta)
{
        //Start off
    this->status=0;
    setup(target,delta);
}

/** @brief ControlOnOff
  *
  * @todo: document this function
  */
 ControlOnOff::ControlOnOff()
{
    this->status=0;
}
