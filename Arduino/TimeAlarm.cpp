#include "TimeAlarm.h"
#include <Arduino.h>
/** @brief isElapsed
  *
  * @todo: document this function
  */
bool TimeAlarm::isElapsed()
{
    //If not active never elapsed
    if(!active)
        return false;
  ///*************DEBUG*********************
  unsigned long dbgt=getElapsedMillis(this->start);
//  Serial.print("---");  Serial.print(dbgt);  Serial.println("---");
    if(dbgt>this->timeout) //If timeout occurred & Timer active
        return true;
        else
    return false;
}

/** @brief reset
  *
  * @todo: document this function
  */
void TimeAlarm::reset()
{
    this->kill();
}

/** @brief set
  *
  * @todo: document this function
  */
void TimeAlarm::set(unsigned long timeoutms)
{
    this->start=millis();
    this->timeout=timeoutms;
    this->active=true;
}

/** @brief TimeAlarm
  *
  * @todo: document this function
  */
 TimeAlarm::TimeAlarm(unsigned long timeoutms)
{
    set(timeoutms);
}
TimeAlarm::TimeAlarm()
{
    this->kill();
}

/** @brief kill
  *
  * @todo: document this function
  */
void TimeAlarm::kill()
{
    this->active=false;
}
