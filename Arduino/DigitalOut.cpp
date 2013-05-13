#include "DigitalOut.h"
/** @brief set
  *
  * @todo: document this function
  */
bool DigitalOut::set(bool value)
{
    if(!this->timerMin.isElapsed()) //If minimum timer not elapsed
        return this->status; //Just return current status

    if(value==this->status) //If command not changed
    {
        //Just check maximum timer
        if(this->timerMax.isElapsed()) //If maximum timer elapsed
            return set(!this->status); //Switch status
    }
    else
    {
        if(value)
        {
            this->timerMin.set(this->MinOnTime); //Set minimum On timer
            this->timerMax.set(this->MaxOnTime); //Set maximum On timer
        }
        else
        {
            this->timerMin.set(this->MinOffTime); //Set minimum Off timer
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
int DigitalOut::init(uint8_t pin,uint32_t MaxOnTimeS,unsigned long MinOnTimeS,unsigned long MaxOffTimeS,unsigned long MinOffTimeS)
{
    this->pin=pin;
    this->MaxOnTime=MaxOnTimeS;
    this->MaxOnTime=MinOnTimeS;
    this->MinOffTime=MinOffTimeS;
    this->MaxOffTime=MaxOffTimeS;
    return 0;

}

/** @brief init
  *
  * @todo: document this function
  */
int DigitalOut::init(uint8_t pin)
{
    this->pin=pin;
    this->MaxOnTime=0;
    this->MaxOnTime=0;
    this->MinOffTime=0;
    this->MaxOffTime=0;
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

/** @brief DigitalOut
  *
  * @todo: document this function
  */
DigitalOut::DigitalOut()
{

}

