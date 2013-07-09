#include <DHT.h>
#include <SD.h>
#include <Wire.h>
/*******************************************************************
 *                   ==SmartGreenHouse==
 *   Main sketch
 *   Created: 17/02/2013
 *   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
 * All available documentation on https://github.com/AxelTB/SmartGreenHouse
 ********************************************************************/
#include <SGH.h>

SGH sgh;
long time;

void setup()
{
      Serial.print("Setup...");
//sgh.initSTD();----------------------------------------------
    ///Init log to SDPIN.
    logInit(SDPIN);

//Sensors Setup------------------
    ///Setup level sensor on LEVELPIN
    pinMode(LEVELPIN,INPUT);
    ///Attach DHT DHTTYPE on DHTPIN
    this->attachDHT(DHTPIN,DHTTYPE);
    //Filter definition
    //this->lplight.setup(LIGHTTAU);
    //this->lphumidity.setup(HUMIDITYTAU);

//Actuators-------------------------
//Order: MaxOn, MinOn, MaxOff,MinOff
    this->heater.init(HEATPIN,300,60,0,60); //Heater setup
    this->humidifier.init(HUMPIN,0,60,0,60);  //Humidifier pin
    this->heatcable.init(HEATCABLEPIN,0,60,0,0);

    //Fan 27 mq/h
    //1 mq/20min = 30 pwm ->
    //Simple temperature control

    outFan.setup(OUTFPIN,45,255,600,18000);

///Parameter definition:
///Heater 18°+-3;<br>
///Humidifier 35+-10;<br>
///Heat cable 25+-5;<br>
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

    //-------------------------------------------------------------------------
  time=millis();
}

void loop()
{
  //sgh.updateSTD();-----------------------------------------------------------
  //Sensors updating-------------------------------------------------------------------------------
    this->updateDHT();
    ///Set level according to level sensor
    if(!(digitalRead(LEVELPIN)==GOODLEVEL) && this->state.level)
    {
        //Level just went low
        this->log(SGH::ERROR,"Low Water level");
    }
    this->state.level=(digitalRead(LEVELPIN)==GOODLEVEL);
    //Read Light sensor----------------------------------------------------
    //this->state.light=analogRead(LIGHTAPIN);
    //Filtered variables
    //this->state.flight=this->lplight.update(state.light);
    //this->state.fhumidity=this->lphumidity.update(state.humidity);
//Actuators updating--------------------------------------------------------------------------
    int ret;
    state.eactuators=0;
    //-----------------------------------------------------------------------------
    ///Verify DHT11 state
    //If sensor major error occurred
    if(state.esensors&State::ESENS_DHTERR)
    {
        //Emergency suspend function=================================================================
        //Shut down both heater and humidifier
        this->heater.forceOff();
        this->heatcable.forceOff();
        this->humidifier.forceOff();
        //Stop Fan
        this->outFan.stop();
        //Add log
        this->log(SGH::CRITICAL,"DHT Major error. Shutting down all actuators");
        //=============================================================================================
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

    ///Fan to Full power if > MAXTEMP
    if(state.temp>MAXTEMP)
        state.outFan=outFan.setSpeed(255);
    else
    {
        //Evaluate distance from higher point
        float ferror=state.temp-FANT;
        float kc=FANP;

        if(ferror>0)
            state.outFan=outFan.setSpeed(kc*ferror);
        else
            state.outFan=outFan.setSpeed(0);
    }
///-----------------------------------------------------------------------------------------------------

    //SD Log -------------------------------------------
    this->saveStats();

  //---------------------------------------------------------------------------
  //Wait for looptime---------------------------------------------
  while(millis()-time<LOOPT*1000);
  time=millis();
}







