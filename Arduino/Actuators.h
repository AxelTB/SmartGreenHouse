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
  ControlOnOff t,h,tc;
  ControlTimer cth;
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
  h.setTarget(state->tHumc); //Set humidifier target


  //Verify DHT11 state--------------------------------------------------------------------------------
  //If sensor major error occurred
  if(state->esensors&State::ESENS_DHT11ERR)
  {
      ///Emergency suspend function=================================================================
    //Shut down both heater and humidifier
    digitalWrite(HEATPIN,0);
    digitalWrite(HEATCABLEPIN,0);
    digitalWrite(HUMPIN,0);
    //Stop Fan
    this->outFan.stop();
    //Add log
    state->log(State::CRITICAL,"DHT11 Major error. Shutting down all actuators");
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
    /* //Controlled version
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

     */
  }

  //Humidifier timered version
  state->humidifier=cth.update(millis());
  if(state->level)
    digitalWrite(HUMPIN,state->humidifier);
  else
    digitalWrite(HUMPIN,LOW);


  if(state->temp>27)
    state->outFan=outFan.setSpeed(255);
  else
    state->outFan=outFan.setSpeed(0);

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
  t.setup(TDELTA,300000,60000,240000,60,0);//Set temperature maximum variation around target


  //Controlled  humidifierversion
  //h.setup(HDELTA,600000,120000,120000,90,10); //MaxOnTime=10min MinOnTime=2min MinOffTime=2min

  //Heat cable
  tc.setup(HCDELTA,1200000,0,120000,70,0);


  //Timered Humidifier version
  cth=ControlTimer(600000,240000);

}



#endif // ACTUATORS_H










