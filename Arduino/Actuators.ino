#include "Actuators.h"
/** @brief Update actuators state
 *
 * Update Actuators commands according to state of the system stored in the state variable according
 * to the given Controls
 */
int Actuators::update(State *state)
{
    int ret;
    state->eactuators=0;
    //Update actuator target (For dynamic update)-------------------------------------------------------
    t.setTarget(state->tTempc); //Set heater target
    tc.setTarget(state->tTempc+state->tTempd/2);    //Set heat Cable target
	
#ifdef HUMCONTROLLED
    h.setTarget(state->tHumc); //Set humidifier target
#endif
//-----------------------------------------------------------------------------
    //Verify DHT11 state--------------------------------------------------------------------------------
    //If sensor major error occurred
    if(state->esensors&State::ESENS_DHTERR)
    {
        ///Emergency suspend function=================================================================
        //Shut down both heater and humidifier
        this->heater.forceOff();
        this->heatcable.forceOff();
        this->humidifier.forceOff();
        //Stop Fan
        this->outFan.stop();
        //Add log
        state->log(State::CRITICAL,"DHT Major error. Shutting down all actuators");
        ///=============================================================================================
    }
    //----------------------------------------------------------------------------------------------------
    else
    {
//Heater------------------------------------------------------------------------------------------------
        state->heater = this->heater.set(t.update(state->temp));

//Heat Cable------------------------------------------------------
        state->heaterCable=this->heatcable.set(tc.update(state->temp));

//Humidifier------------------------------------------------------
#ifdef HUMCONTROLLED
        //If water level is not good shut down humidifier
        if(state->level==0)
            state->humidifier=this->humidifier.off();
        //or evaluate status
        else
            state->humidifier=this->humidifier.set(h.update(state->humidity));

#endif
    }
#ifndef HUMCONTROLLED
    /*//Humidifier timered version
    state->humidifier=cth.update(millis());
    if(!state->level)
        state->humidifier=0;
    digitalWrite(HUMPIN,state->humidifier);*/ not implemented, define HUMCONTROLLED
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

    this->heater.init(HEATPIN,300,60,0,600); //Heater setup
    this->humidifier.init(HUMPIN,0,60,0,60);  //Humidifier pin
    this->heatcable.init(HEATCABLEPIN,0,1200,0,0);

//Fan 27 mq/h
    //1 mq/20min = 30 pwm ->
    //Simple temperature control

    outFan.setup(OUTFPIN,45,255,600,18000);


    t.setup(TDELTA,60,3);//Set temperature maximum variation around target

#ifdef HUMCONTROLLED
    //Controlled  humidifierversion
    h.setup(HDELTA,90,10);
#else
    //Timered Humidifier version
    cth=ControlTimer(600000,240000);
#endif
    //Heat cable
    tc.setup(HCDELTA,60,3);



}


