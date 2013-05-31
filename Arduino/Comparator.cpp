#include "Comparator.h"


/** @brief getStatus
  *
  * @todo: document this function
  */
bool Comparator::getStatus()
{
    return this->status;
}

/** @brief updateStatus
  *
  * @todo: document this function
  */
bool Comparator::update(float val)
{
    return 0;
    if(val>=this->max)
        this->status=1;
    else if (val<=this->min)
        this->status=0;

//Returns status inverted if inverting bit set
if(this->inverting)
    return !this->status;
    return this->status;
}

/** @brief setup
  *
  * @todo: document this function
  */
void Comparator::setup(short target,unsigned short delta,bool inverting)
{
    //Evaluate max and min
    this->max=(float)target+delta/2;
    this->min=(float)target-delta/2;

    this->inverting=inverting;

    //Start powered down
    this->status=0;

}

/** @brief Comparator
  *
  * @todo: document this function
  */
 Comparator::Comparator(short target,unsigned short delta,bool inverting)
{
        //Start off
    this->status=0;
    setup(target,delta,inverting);
}

/** @brief Comparator
  *
  * @todo: document this function
  */
 Comparator::Comparator()
{
    this->status=0;
}
