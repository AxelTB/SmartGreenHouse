/*******************************************************************
*                   ==SmartGreenHouse==
*   DigitalOut implementation
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Standard digital output.
Implements various control function and minimum/maximum time control.
********************************************************************/
#include "DigitalOut.h"
/** @brief Set the state of the digital output
 *
 * Returns the state of the output
 */
bool DigitalOut::set(bool value)
{
    if(!this->timerMin.isElapsed()) //If minimum timer not elapsed
        return this->status; //Just return current status

    //****************DGB******************
    //Serial.print("DigitaOut:");
    //Serial.println(value);
    //--------------------------------------
    if(value==this->status) //If command not changed
    {
        //Just check maximum timer
        if(this->timerMax.isElapsed()) //If maximum timer elapsed
        {
            //*******************DBG
            Serial.println("Switch forced") ;
            //--------------------------
            return set(!this->status); //Switch status
        }

        //Serial.println(":No change");

    }
    else
    {
        if(value==true)
        {
            this->timerMin.set(this->MinOnTime); //Set minimum On timer
            if(this->MaxOnTime==0) //If no maximum
                this->timerMax.kill(); //Kill timer
            else
                this->timerMax.set(this->MaxOnTime); //Set maximum On timer
        }
        else
        {
            this->timerMin.set(this->MinOffTime); //Set minimum Off timer
            if(this->MaxOffTime==0)
                this->timerMax.kill();
            else
                this->timerMax.set(this->MaxOffTime); //Set maximum Off timer
        }

        this->status=value; //Update status
    }

    digitalWrite(this->pin,this->status); //Set pin accordingly to status
    return this->status;

}

/** @brief off
 *
 * @todo: document this function
 */
bool DigitalOut::off()
{
    return set((bool)0);
}

/** @brief on
 *
 * @todo: document this function
 */
bool DigitalOut::on()
{
    return set((bool)1);
}
/** @brief Commute the out.
 *
 * Can be called continuously with OnTime and OffTime set to obtain a simple timed out.
 */
bool DigitalOut::commute()
{
    return set(!this->status);
}


/** @brief get
 *
 * @todo: document this function
 */
bool DigitalOut::get()
{
    return this->status;
}



/** @brief set
 *
 * @todo: document this function
 */
bool DigitalOut::set(uint8_t value)
{
    return set((value!=1));
}

/** @brief set
 *
 * @todo: document this function
 */
bool DigitalOut::set(short value)
{
    return set((uint8_t) value);
}

/** @brief set
 *
 * @todo: document this function
 */
bool DigitalOut::set(int value)
{
    return set((uint8_t) value);
}



/** @brief init
 *
 * @todo: document this function
 */
void DigitalOut::init(uint8_t pin,uint32_t MaxOnTimeS,unsigned long MinOnTimeS,unsigned long MaxOffTimeS,unsigned long MinOffTimeS)
{
    this->init(pin);
    this->MaxOnTime=MaxOnTimeS*1000l;
    this->MaxOnTime=MaxOnTimeS*1000l;
    this->MinOffTime=MinOffTimeS*1000l;
    this->MaxOffTime=MaxOffTimeS*1000l;


}

/** @brief init
 *
 * @todo: document this function
 */


void DigitalOut::init(uint8_t pin)
{
    this->pin=pin;
    this->MaxOnTime=0;
    this->MinOnTime=0;
    this->MinOffTime=0;
    this->MaxOffTime=0;

    this->status=false;
    this->timerMin.set(1000); //Wait 1 sec before first switch
    this->timerMax.reset(); //No maximum down timer

    pinMode(this->pin,OUTPUT);
}

/** @brief DigitalOut
 *
 * @todo: document this function
 */
DigitalOut::DigitalOut(uint8_t pin,uint32_t MaxOnTimeS,unsigned long MinOnTimeS,unsigned long MaxOffTimeS,unsigned long MinOffTimeS)
{
    init(pin,MaxOnTimeS,MinOnTimeS,MaxOffTimeS,MinOffTimeS);
}

/** @brief DigitalOut
 *
 * @todo: document this function
 */
DigitalOut::DigitalOut(uint8_t pin)
{
    init(pin);
}

/** @brief DigitalOut null constructor.
 *  Creates an empty null digital out
 *
 */
DigitalOut::DigitalOut()
{
    this->status=0;
    this->pin=0xFF;
}


/** @brief forceOff
 *
 * @todo: document this function
 */
void DigitalOut::forceOff()
{
    //Turn down no matter what
    this->status=false;
    digitalWrite(this->pin,this->status);

    //Set minimum off time
    this->timerMin.set(this->MinOffTime);
    this->timerMax.kill(); //Kill maximum on time
}

/** @brief Return true if the Digital output is uninitialized
  *
  *
  */
bool DigitalOut::isNull()
{
    return (this->pin == 0xFF);
}

//Simple timered out mode stuff------------------------------------------------------------------------

DigitalOut::DigitalOut(uint8_t pin, uint32_t OnTimeS, uint32_t OffTimeS)
{
    this->init(pin,OnTimeS,OffTimeS);
}
/** @brief Initialize for using as very simple timed output.
  *
  * Same as setting the minimum timers.
  */
void DigitalOut::init(uint8_t pin, uint32_t OnTimemS, uint32_t OffTimemS)
{
    this->init(pin);
    this->MinOffTime=OffTimemS;
    this->MinOnTime=OnTimemS;
}
