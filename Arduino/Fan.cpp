#include <Fan.h>

/** @brief setSpeed
 *
 * @todo: document this function
 */
uint8_t Fan::setSpeed(uint8_t command)
{
  uint8_t tpwm;
  float minPwm=0;

  if(command==0)
    tpwm=0;
  else if(command>=100)
    tpwm=this->maxCommand;
  else
    //Evaluate command
    tpwm=(this->KCommand)*command;

  if(this->cicleTms>0)
  {
    float dt=((float)millis()-this->lastCallTms);
    this->lastCallTms=millis();
    //Add moved air
    this->airflowSum+=(float) this->pwm*dt;

    //Define minimum value to respect parameters (Linear way)-2
    minPwm=(float) (this->airflowTarget-this->airflowSum)/(this->cicleTms-(millis()-this->cicleStart))-2;
    minPwm+=2;
#ifdef DEBUGFAN
    Serial.print(this->airflowSum);
    Serial.print("->");
    Serial.print(this->airflowTarget);
    Serial.print("\t");

    Serial.print(millis()-this->cicleStart);
    Serial.print("->");
    Serial.print(this->cicleTms);
    Serial.print("\t");

    Serial.print(command);
    Serial.print("->");
    Serial.print(tpwm);
    Serial.print("->");
    Serial.print(minPwm);
#endif
    //Suppress if less than minimum command
    /*if(minPwm<this->minCommand)
      minPwm=0;*/

    //If period elapsed
    if( (millis()-this->cicleStart) > this->cicleTms)
    {
      //Evaluate difference between target and reality
      long error=this->airflowTarget-this->airflowSum;
      //If not enoutgh air has passed
      if(error>0&&error<this->airflowSum)
        //Add to next cicle
        this->airflowSum=-error;
      else
        this->airflowSum=0;
      //Reset periodic data
      this->cicleStart=millis();
    }
    //Update pwm accordingly
    if(tpwm<minPwm)
      tpwm=minPwm;
  }
this->pwm=tpwm;
  //Check for too low value
  if(this->pwm<this->minCommand)
    this->pwm=0;


#ifdef DEBUGFAN
  Serial.print("->");
  Serial.print(this->pwm);
  Serial.println();
#endif
  analogWrite(this->pin,this->pwm);
  return this->pwm;
}

/** @brief setup
 *
 * @todo: document this function
 */
void Fan::setup(uint8_t pin,uint16_t minCommand,uint16_t maxCommand,float cicleTSec,float airflowTarget)
{
  setup(pin,minCommand,maxCommand);

  //Convert from s to ms
  this->cicleTms=cicleTSec*1000;
  this->airflowTarget=airflowTarget*1000;

  this->airflowSum=0;
  this->cicleStart=millis();
}

/** @brief setup
 *
 * @todo: document this function
 */
void Fan::setup(uint8_t pin,uint16_t minCommand,uint16_t maxCommand)
{
  this->pin=pin;
  this->pwm=0;

  pinMode(pin,OUTPUT);
  analogWrite(pin,pwm);

  this->minCommand=minCommand;
  this->maxCommand=maxCommand;
  this->KCommand=(float)(maxCommand-minCommand)/100;

  this->cicleTms=0;
}

/** @brief stop
 *
 * @todo: document this function
 */
void Fan::stop()
{
  this->pwm=0;
  analogWrite(pin,pwm);
}



