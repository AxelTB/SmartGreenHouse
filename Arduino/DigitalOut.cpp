#include "DigitalOut.h"
/** @brief set
 *
 * @todo: document this function
 */
bool DigitalOut::set(bool value)
{
  if(!this->timerMin.isElapsed()) //If minimum timer not elapsed
      return this->status; //Just return current status
  ///****************DGB******************
  Serial.print("DigitaOut:");
  Serial.println(value);
  if(value==this->status) //If command not changed
  {
    //Just check maximum timer
    if(this->timerMax.isElapsed()) //If maximum timer elapsed
    {
Serial.println("Switch forced") ;
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
  this->init(pin);
  this->MaxOnTime=MaxOnTimeS*1000;
  this->MaxOnTime=MinOnTimeS*1000;
  this->MinOffTime=MinOffTimeS*1000;
  this->MaxOffTime=MaxOffTimeS*1000;
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

  this->status=false;
  this->timerMin.set(5000); //Wait 1 sec before switch
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

/** @brief DigitalOut
 *
 * @todo: document this function
 */
DigitalOut::DigitalOut()
{
    this->status=0;
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


