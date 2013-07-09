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

///Sensors defines---------------------------------
#define DHTPIN 8
#define DHTTYPE DHT11

#define LEVELPIN 5
#define LIGHTAPIN 0

#define LIGHTTAU 10
#define HUMIDITYTAU 120

#define GOODLEVEL HIGH

//Actuators Defines------------------------------------------------
#define HEATPIN 2
#define HUMPIN 3
#define HEATCABLEPIN 4
#define OUTFPIN   10

#define FANT 25 ///Fan target temperature
#define FANP 3 ///Fan proportional term

#define HUMCONTROLLED

#define HCDELTA 4

#define MAXTEMP 40 ///Maximum temperature allowed for the system



long time;
    //Sensors variables----------------
    DHT dht; ///DHT Sensor
    unsigned short dhterrN;
    //Actuators Variables--------------
    DigitalOut heater,
    humidifier,
    heatcable;
    Comparator t,tc;
    Comparator h;
    Fan outFan;

SGH sgh;
void setup()
{
      Serial.print("Setup...");
//sgh.initSTD();----------------------------------------------
    ///Init log to SDPIN.
    sgh.logInit(SDPIN);

//Sensors Setup------------------
    ///Setup level sensor on LEVELPIN
    pinMode(LEVELPIN,INPUT);
    ///Attach DHT DHTTYPE on DHTPIN
    sgh.attachDHT(DHTPIN,DHTTYPE);
    //Filter definition
    //sgh.lplight.setup(LIGHTTAU);
    //sgh.lphumidity.setup(HUMIDITYTAU);

//Actuators-------------------------
//Order: MaxOn, MinOn, MaxOff,MinOff
    heater.init(HEATPIN,300,60,0,60); //Heater setup
    humidifier.init(HUMPIN,0,60,0,60);  //Humidifier pin
    heatcable.init(HEATCABLEPIN,0,60,0,0);

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
    sgh.updateDHT();
    ///Set level according to level sensor
    if(!(digitalRead(LEVELPIN)==GOODLEVEL) && sgh.state.level)
    {
        //Level just went low
        sgh.log(SGH::ERROR,"Low Water level");
    }
    sgh.state.level=(digitalRead(LEVELPIN)==GOODLEVEL);
    //Read Light sensor----------------------------------------------------
    //state.light=analogRead(LIGHTAPIN);
    //Filtered variables
    //state.flight=lplight.update(state.light);
    //state.fhumidity=lphumidity.update(state.humidity);
//Actuators updating--------------------------------------------------------------------------
    int ret;
    sgh.state.eactuators=0;
    //-----------------------------------------------------------------------------
    ///Verify DHT11 state
    //If sensor major error occurred
    if(sgh.state.esensors&State::ESENS_DHTERR)
    {
        //Emergency suspend function=================================================================
        //Shut down both heater and humidifier
        heater.forceOff();
        heatcable.forceOff();
        humidifier.forceOff();
        //Stop Fan
        outFan.stop();
        //Add log
        sgh.log(SGH::CRITICAL,"DHT Major error. Shutting down all actuators");
        //=============================================================================================
    }
    //----------------------------------------------------------------------------------------------------
    else
    {
        //Heater------------------------------------------------------------------------------------------------
        bool dbgctrl=t.update(sgh.state.temp);
        //Serial.print("H:");
        //Serial.println(dbgctrl);
        sgh.state.heater = heater.set(dbgctrl);

        //Heat Cable------------------------------------------------------
        sgh.state.heaterCable=heatcable.set(tc.update(sgh.state.temp));

        //Humidifier------------------------------------------------------
#ifdef HUMCONTROLLED
        //If water level is not good shut down humidifier
        if(sgh.state.level==0)
            sgh.state.humidifier=humidifier.off();
        //or evaluate status
        else
            sgh.state.humidifier=humidifier.set(h.update(sgh.state.humidity));

#endif
    }

    ///Fan to Full power if > MAXTEMP
    if(sgh.state.temp>MAXTEMP)
        sgh.state.outFan=outFan.setSpeed(255);
    else
    {
        //Evaluate distance from higher point
        float ferror=sgh.state.temp-FANT;
        float kc=FANP;

        if(ferror>0)
            sgh.state.outFan=outFan.setSpeed(kc*ferror);
        else
            sgh.state.outFan=outFan.setSpeed(0);
    }
///-----------------------------------------------------------------------------------------------------

    //SD Log -------------------------------------------
    sgh.saveStats();

  //---------------------------------------------------------------------------
  //Wait for looptime---------------------------------------------
  while(millis()-time<LOOPT*1000);
  time=millis();
}







