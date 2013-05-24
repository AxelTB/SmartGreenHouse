#include "TimeCounter.h"
#include <Arduino.h>

#define OVERFLOWEDGEHIGH ((unsigned long)0xFFFF0000 )
#define OVERFLOWEDGELOW  ((unsigned long)0x0000FFFF )
#define MAXMILLIS ((unsigned long)0xFFFFFFFF )

TimeCounter::TimeCounter()
{
  this->start=millis();
}

/** @brief getElapsedMillis
 *
 * returns time in milliseconds since last call
 */
unsigned long TimeCounter::getElapsedMillis()
{
  unsigned long ret=getElapsedMillis(this->start);
  this->start=millis();
  return ret;

}




/** @brief getElapsedMillis Function
 *
 * @todo: get millis from start time
 */
unsigned long TimeCounter::getElapsedMillis(unsigned long startms)
{
  unsigned long now=millis();
  if(startms>now) //Some error occurred
  {
    Serial.println("***TIME OVERFLOW***");
    if(this->start>OVERFLOWEDGEHIGH && now<OVERFLOWEDGELOW)
    {
      //Overflow
      return (MAXMILLIS-startms)+now;
    }
    Serial.println("Grande Giove!");
    //WTF?!? This should not happen... Just return 0 and forget this ever happened
    return 0;
    //TODO: Maybe add something...

  }

  //If everything worked fine
  return startms-now;
}


