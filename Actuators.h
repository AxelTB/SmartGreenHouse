#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "State.h"
#include "ControlOnOff.h"

#define HEATPIN 2
#define HUMPIN 3

#define TDELTA 6
#define TTARGET 21

#define HDELTA 10
#define HTARGET 60

class Actuators
{
public:
    int setup();
    ///Command actuators with data from state
    int update(State *state);
protected:
private:
    unsigned short heatpin,humpin;
    ControlOnOff t,h;
};
/** @brief update
 *
 * @todo: document this function
 */
int Actuators::update(State *state)
{
    int ret;
    state->eactuators=0;
    //Verify DHT11 state
    //If sensoor major error
    if(state->esensors&State::ESENS_DHT11ERR)
    {
   //Shut down both heater and humidifier
        digitalWrite(HEATPIN,0);
        digitalWrite(HUMPIN,0);
	//Add log
        state->log(State::CRITICAL,"DHT11 Major error. Shutting down all actuators");
    }
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

    //Humidity------------------------------------------------------
    //If water level is good
    if(state->level)
    {

        if(  (ret=h.updateStatus(state->humidity))>=0)
        {
            state->humidifier=h.getStatus();
            digitalWrite(HUMPIN,state->humidifier);
        }
        if(ret==3)
            state->log(State::INFORMATION,"Humidifier Maximum uptime reached");
        else if(ret==-2)
            state->eactuators=State::ESENS_HOUTOFBOUND;
    }
    }
    //-------------------------------------------------------------

}

/** @brief setup
 *
 * @todo: document this function
 */
int Actuators::setup()
{
    pinMode(HEATPIN,OUTPUT); //Set Heater pin
    pinMode(HUMPIN,OUTPUT);  //Humidifier pin

    digitalWrite(HEATPIN,LOW);
    digitalWrite(HUMPIN,LOW);

    t.setup(TDELTA);//Set temperature maximum variation around target
    t.setTarget(TTARGET); //Set temperature target
    h.setup(HDELTA,0,0,0,90,10); //Set humidity maximum variation around target
    h.setTarget(HTARGET); //Set humidity target

}


#endif // ACTUATORS_H

