/*******************************************************************
*                   ==SmartGreenHouse==
*   SGH Implementation File
*   Created: 17/02/2013
*   Author:  Ax
*   License: CC BY-SA 3.0
*            http://creativecommons.org/licenses/by-sa/3.0/
*=====================================================================*
 *
 * Contains
 ********************************************************************/

#include "SGH.h"


///Sensors defines---------------------------------
#define DHTPIN 8
#define DHTTYPE DHT11

#define LEVELPIN 5
#define LIGHTAPIN 0

#define LIGHTTAU 10
#define HUMIDITYTAU 120

#define GOODLEVEL HIGH

///Actuators Defines------------------------------------------------
#define HEATPIN 2
#define HUMPIN 3
#define HEATCABLEPIN 4
#define OUTFPIN   10
#define FANT 25

#define HUMCONTROLLED

#define HCDELTA 4

///Modular methods
/** @brief update SGH
  *
  * Returns 0 if everything fine
  * Update DHT and save sta
  */
int SGH::update()
{
    this->updateDHT(); //Update DHT Status
    if(this->state.sdstatus) //If SD configured
        this->saveStats(); //Log statistics

    return 0;
}
///-------------------------------------------------

SGH::SGH()
{
    //ctor
}
/** @brief update
  *
  * @todo: document this function
  */
int SGH::updateSTD()
{
///Sensors updating-------------------------------------------------------------------------------
    this->updateDHT();
    //Set level according to level sensor----------------------------------
    if(!(digitalRead(LEVELPIN)==GOODLEVEL) && this->state.level)
    {
        //Level just went low
        this->log(SGH::ERROR,"Low Water level");
    }
    this->state.level=(digitalRead(LEVELPIN)==GOODLEVEL);
    //Read Light sensor----------------------------------------------------
    this->state.light=analogRead(LIGHTAPIN);
    //Filtered variables
    //this->state.flight=this->lplight.update(state.light);
    //this->state.fhumidity=this->lphumidity.update(state.humidity);
///Actuators updating--------------------------------------------------------------------------
    int ret;
    state.eactuators=0;
    //-----------------------------------------------------------------------------
    //Verify DHT11 state--------------------------------------------------------------------------------
    //If sensor major error occurred
    if(state.esensors&State::ESENS_DHTERR)
    {
        ///Emergency suspend function=================================================================
        //Shut down both heater and humidifier
        this->heater.forceOff();
        this->heatcable.forceOff();
        this->humidifier.forceOff();
        //Stop Fan
        this->outFan.stop();
        //Add log
        this->log(SGH::CRITICAL,"DHT Major error. Shutting down all actuators");
        ///=============================================================================================
    }
    //----------------------------------------------------------------------------------------------------
    else
    {
        //Heater------------------------------------------------------------------------------------------------
        bool dbgctrl=t.update(state.temp);
        //Serial.print("H:");
        //Serial.println(dbgctrl);
        state.heater = this->heater.set(dbgctrl);

        //Heat Cable------------------------------------------------------
        state.heaterCable=this->heatcable.set(tc.update(state.temp));

        //Humidifier------------------------------------------------------
#ifdef HUMCONTROLLED
        //If water level is not good shut down humidifier
        if(state.level==0)
            state.humidifier=this->humidifier.off();
        //or evaluate status
        else
            state.humidifier=this->humidifier.set(h.update(state.humidity));

#endif
    }

    //Full power if > 30°
    if(state.temp>30)
        state.outFan=outFan.setSpeed(255);
    else
    {
        //Evaluate distance from higher point
        float ferror=state.temp-FANT;
        float kc=30;

        if(ferror>0)
            state.outFan=outFan.setSpeed(kc*ferror);
        else
            state.outFan=outFan.setSpeed(0);
    }
///-----------------------------------------------------------------------------------------------------

    //SD Log -------------------------------------------
    this->saveStats();

}

/** @brief init
  *
  * @todo: document this function
  */
int SGH::initSTD()
{
    Serial.print("Setup...");
///State setup----------------------------
    logInit(SDPIN);

///Sensors Setup---------------------------------------------------------------------------------------
    pinMode(LEVELPIN,INPUT);
    this->attachDHT(DHTPIN,DHTTYPE);
    //Filter definition
    //this->lplight.setup(LIGHTTAU);
    //this->lphumidity.setup(HUMIDITYTAU);

///Actuators---------------------------------------------------------------------------------------------
///MaxOn, MinOn, MaxOff,MinOff
    this->heater.init(HEATPIN,300,60,0,60); //Heater setup
    this->humidifier.init(HUMPIN,0,60,0,60);  //Humidifier pin
    this->heatcable.init(HEATCABLEPIN,0,60,0,0);

    //Fan 27 mq/h
    //1 mq/20min = 30 pwm ->
    //Simple temperature control

    outFan.setup(OUTFPIN,45,255,600,18000);

///Parameter definition
///Heater 18°+-3
///Humidifier 35+-10
///Heat cable 25+-5
    t.setup(18,6,1);//Set temperature maximum variation around target

#ifdef HUMCONTROLLED
    //Controlled  humidifier version
    h.setup(35,20,1);
#else
    //Timered Humidifier version
    cth=ControlTimer(600000,240000);
#endif
    //Heat cable
    tc.setup(25,10,1);

    //Serial.println("DONE!");
}


SGH::~SGH()
{
    //dtor
}


