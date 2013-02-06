#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "State.h"
#include "ControlOnOff.h"

#define HEATPIN 2
#define HUMPIN 3
#define HEATCABLEPIN 4

#define TDELTA 8
#define TTARGET 20

#define HDELTA 10
#define HTARGET 40

#define HCDELTA 0
#define HCTARGET 23

#define OUTFPIN   10
#define OUTFONT     300000l
#define OUTFIDLET   3300000l 
#define OUTFPOWER   200

class Actuators
{
	public:
		int setup();
		///Command actuators with data from state
		int update(State *state);
	protected:
	private:
		unsigned short heatpin,humpin;
		ControlOnOff t,h,tc;

                long outftime;

};
/** @brief update
 *
 * @todo: document this function
 */
int Actuators::update(State *state)
{
	int ret;
	state->eactuators=0;
	//Verify DHT11 state--------------------------------------------------------------------------------
	//If sensoor major error
	if(state->esensors&State::ESENS_DHT11ERR)
	{
		//Shut down both heater and humidifier
		digitalWrite(HEATPIN,0);
		digitalWrite(HEATCABLEPIN,0);
		digitalWrite(HUMPIN,0);
		//Add log
		state->log(State::CRITICAL,"DHT11 Major error. Shutting down all actuators");
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


	}
	//Fresh Air Cicle-------------------------------------------------------------
        //If active for enought time
        if(state->outFan>0 && millis()-outftime>OUTFONT)
        {
          //Turn Off
            state->outFan=0;
            outftime=millis();
        }
        //If idle for enought time
        else if(state->outFan==0 && millis()-outftime>OUTFIDLET)
        {
          state->outFan=OUTFPOWER;
            outftime=millis();
        }
        //Update status
        digitalWrite(OUTFPIN,state->outFan);

}

/** @brief setup
 *
 * @todo: document this function
 */
int Actuators::setup()
{
	pinMode(HEATPIN,OUTPUT); //Set Heater pin
	pinMode(HUMPIN,OUTPUT);  //Humidifier pin
	pinMode(HEATCABLEPIN,OUTPUT);
        pinMode(OUTFPIN,OUTPUT);
        
        digitalWrite(OUTFPIN,255);
        outftime=millis();
        
        
	digitalWrite(HEATPIN,LOW);
	digitalWrite(HUMPIN,LOW);
	digitalWrite(HEATCABLEPIN,LOW);
	t.setup(TDELTA,300000,60000,240000,60,0);//Set temperature maximum variation around target
	t.setTarget(TTARGET); //Set temperature target
	h.setup(HDELTA,0,0,0,90,10); //Set humidity maximum variation around target
	h.setTarget(HTARGET); //Set humidity target
	tc.setup(HCDELTA,0,0,0,60,0);
	tc.setTarget(HCTARGET);

        

}


#endif // ACTUATORS_H




