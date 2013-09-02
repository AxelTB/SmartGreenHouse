#include "SGH.h"
/** @brief (one liner)
  *
  * (documentation goes here)
  */
int SGH::updateHeater()
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
int SGH::attachHeater(uint8_t pin,uint8_t lowTH,uint8_t highTH,int minTransitionSec)
{
    this->heater=DigitalOut(pin,minTransitionSec,minTransitionSec,minTransitionSec,minTransitionSec);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
int SGH::updateHumidifier()
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
int SGH::attachHumidifier(uint8_t pin,uint8_t lowTH,uint8_t highTH,int minTransitionSec)
{

}

