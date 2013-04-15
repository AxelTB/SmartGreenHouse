/*******************************************************************
 *                   ==SmartGreenHouse==
 *   Actuator Class
 *   Created: 17/02/2013
 *   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
 *All actuators code goes there
 ********************************************************************/
#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "State.h"
#include "ControlOnOff.h"
#include "ControlTimer.h"

#define HEATPIN 2
#define HUMPIN 3
#define HEATCABLEPIN 4
#define OUTFPIN   10

#define HUMCONTROLLED

#define HCDELTA 4

class Actuators
{
public:
    int setup();
    ///Command actuators with data from state
    int update(State *state);
protected:
private:
    unsigned short heatpin,humpin;
    ControlOnOff t,tc;
#ifndef HUMCONTROLLED
    ControlTimer cth;
#else
    ControlOnOff h;
#endif
    Fan outFan;



};
/** @brief Update actuators state
 *
 * Update Actuators commands according to state of the system stored in the state variable according
 * to the given Controls
 */
int Actuators::update(State *state)
{
    int ret;
    state->eactuators=0;
    //Update actuator target-------------------------------------------------------
    //TODO: Avoid update if target not changed
    t.setTarget(state->tTempc); //Set heater target
    tc.setTarget(state->tTempc+state->tTempd/2);    //Set heat Cable target
#ifdef HUMCONTROLLED
    h.setTarget(state->tHumc); //Set humidifier target
#endif

    //Verify DHT11 state--------------------------------------------------------------------------------
    //If sensor major error occurred
    if(state->esensors&State::ESENS_DHTERR)
    {
        ///Emergency suspend function=================================================================
        //Shut down both heater and humidifier
        digitalWrite(HEATPIN,0);
        digitalWrite(HEATCABLEPIN,0);
        digitalWrite(HUMPIN,0);
        //Stop Fan
        this->outFan.stop();
        //Add log
        state->log(State::CRITICAL,"DHT Major error. Shutting down all actuators");
        ///=============================================================================================
    }
    //----------------------------------------------------------------------------------------------------
    else
    {
        //Heater---------------------------------------------------------
        if(  (ret=t.updateStatus(state->temp)) >=0 )
        {
            state->heater = t.getStatus();
            digitalWrite(HEATPIN,state->heater);
        }

        if(ret==3)
            state->log(State::INFORMATION,"Heat Maximum uptime reached");
        else if(ret==-2)
            state->eactuators=State::ESENS_TOUTOFBOUND;
        //Heat Cable------------------------------------------------------
        if(tc.updateStatus(state->temp) >= 0)
        {
            state->heaterCable=tc.getStatus();
            digitalWrite(HEATCABLEPIN,state->heaterCable);
        }
#ifdef HUMCONTROLLED
        //Humidity------------------------------------------------------
        //If water level is not good shut down humidifier
        if(state->level==0)
            state->humidifier=0;
        //or evaluate status
        else if(  (ret=h.updateStatus(state->humidity))>=0)
            state->humidifier=h.getStatus();
        //Update humidifier status
        digitalWrite(HUMPIN,state->humidifier);


        if(ret==3)
            state->log(State::INFORMATION,"Humidifier Maximum uptime reached");
        else if(ret==-2)
        {
            state->eactuators=State::ESENS_HOUTOFBOUND;
            state->log(State::ERROR,"Humidity out of bound");
        }

#endif
    }
#ifndef HUMCONTROLLED
    //Humidifier timered version
    state->humidifier=cth.update(millis());
    if(!state->level)
        state->humidifier=0;
    digitalWrite(HUMPIN,state->humidifier);
#endif
    //Full power if > 30°
    if(state->temp>30)
        state->outFan=outFan.setSpeed(255);
    else
    {
      //Evaluate distance from higher point
      float ferror=state->temp-(state->tTempc+state->tTempd/2);
      float kc=30;
      
      if(ferror>0)
        state->outFan=outFan.setSpeed(kc*ferror);
      else
        state->outFan=outFan.setSpeed(0);
    }

}

/** @brief Setup Function
 *
 * Contains all Actuators initializations and startup procedures.
 */
int Actuators::setup()
{
    pinMode(HEATPIN,OUTPUT); //Set Heater pin
    pinMode(HUMPIN,OUTPUT);  //Humidifier pin
    pinMode(HEATCABLEPIN,OUTPUT);

//Fan 27 mq/h
    //1 mq/20min = 30 pwm ->
    //Simple temperature control

    outFan.setup(OUTFPIN,45,255,600,18000);


    digitalWrite(HEATPIN,LOW);
    digitalWrite(HUMPIN,LOW);
    digitalWrite(HEATCABLEPIN,LOW);
    t.setup(TDELTA,300000,60000,240000,60,3);//Set temperature maximum variation around target

#ifdef HUMCONTROLLED
    //Controlled  humidifierversion
    h.setup(HDELTA,720000,60000,300000,90,10); //MaxOnTime=2h MinOnTime=1min MinOffTime=5min
#else
    //Timered Humidifier version
    cth=ControlTimer(600000,240000);
#endif
    //Heat cable
    tc.setup(HCDELTA,1200000,0,120000,60,3);



}



#endif // ACTUATORS_H










