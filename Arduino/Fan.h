#ifndef FAN_H
#define FAN_H
#include <Arduino.h>
/*******************************************************************
*                   ==SmartGreenHouse==
*   Control On/Off Class
*   Created: 07/03/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Control Class for fan
********************************************************************/

class Fan
{
public:
    /** Setup
        pin -> fan pin
        minCommand & maxCommand -> minimum and maximum accepted command.

        cicleTSec -> Time interval between minimum airflow control
        airflowTarget -> Airflow targed intended as raw_command*sec

    Everyting below minCommand will be 0 (To avoid fan noise), everything greather than maxCommand will be MaxCommand
    **/
    void setup(uint8_t pin,uint16_t minCommand,uint16_t maxCommand);
    void setup(uint8_t pin,uint16_t minCommand,uint16_t maxCommand,float cicleTSec,float airflowTarget);

    /*** Set fan speed
    command -> 0-100 set fan percentage
    0 fan off
    1 minCommand
    100 maxCommand

    Returns fan output raw
    */
    uint8_t setSpeed(uint8_t command);
protected:
private:
    uint8_t pin; //Fan pin
    uint16_t minCommand,maxCommand; //Maximum and minimum command available
    float KCommand;
    long cicleTms,airflowTarget; //Fresh air control variables
    long cicleStart, airflowSum;  //Freash air cicle temporary variables
    long lastCallTms;

    uint8_t pwm;
};

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
        float dts=((float)millis()-this->lastCallTms)/1000;
        this->lastCallTms=millis();
        //Add moved air
        this->airflowSum+=(float) this->pwm*dts;

        //Define minimum value to respect parameters (Linear way)+1
        minPwm=(float) (this->airflowTarget-this->airflowSum)/(this->cicleTms-(millis()-this->cicleStart))+1;

        //Suppress if less than minimum command
        if(minPwm<this->minCommand)
            minPwm=0;

        //If period elapsed
        if( (millis()-this->cicleStart) > this->cicleTms)
        {
            //Evaluate difference between target and reality
            long error=this->airflowTarget-this->airflowSum;
            //If not enoutgh air has passed
            if(error>0)
                //Add to next cicle
                this->airflowSum=-error;
            else
                this->airflowSum=0;
            //Reset periodic data
            this->cicleStart=millis();
        }
    }

    if(tpwm<minPwm)
        this->pwm=minPwm;
    else
        this->pwm=tpwm;

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


#endif // FAN_H
