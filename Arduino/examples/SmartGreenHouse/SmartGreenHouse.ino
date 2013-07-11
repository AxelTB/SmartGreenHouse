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
 * @brief Full version prototype.
 *	Demonstrate the use of all implemented modules. Use implemented SGH state variable, dht and log. All other modules are used as they are.
 * All available documentation on https://github.com/AxelTB/SmartGreenHouse
 ********************************************************************/
#include <SGH.h>

///Sensors defines---------------------------------
#define DHTPIN 8 ///Dht Arduino Pin
#define DHTTYPE DHT11 ///DHT Type

#define LEVELPIN 5 ///Umidifier water level pin
#define GOODLEVEL HIGH ///Pin state if water level is good

//Actuators Defines------------------------------------------------
#define HEATPIN 2 ///Heater pin
#define HUMPIN 3 ///Humidifier pin
#define HEATCABLEPIN 4 ///Heat cable pin
#define OUTFPIN   10 ///Out fan pwm pin

#define FANT 25 ///Fan target temperature
#define FANP 3 ///Fan proportional term

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
//Actuators-------------------------
///Set the maximum time for the digital actuators
//Parameter Order (Time in seconds): MaxOn, MinOn, MaxOff,MinOff
    heater.init(HEATPIN,300,60,0,60); //Heater setup
    humidifier.init(HUMPIN,0,60,0,60);  //Humidifier pin
    heatcable.init(HEATCABLEPIN,0,60,0,0); ///Heat cable setup

    //Fan 27 mq/h -> 0.0075 m^3/sec
    //1 mq/20min = 30 pwm ->
    //Simple temperature control
/***
* Fan Setup:
* pin: OUTFPIN
* minPwm: 45
* maxPwm: 255
* airCircleLoopT: 1200 (20 min)
* airCircleCoefficient: 16320
*
* airCircleCoefficient example:
* Test fan 27 m^3/h at maximum power
* Desired airflow 0.5 m^3 / 20 min    0.0004 m^3/s
* airCicleCoefficient (DesiredAirflow/FanAirflow*255*airCircleLoopT) 0.0004/0.0075*255*1200=16320
***/
    outFan.setup(OUTFPIN,45,255,600,18000);

///Parameter definition:
///Heater 18°+-3;<br>
///Humidifier 35+-10;<br>
///Heat cable 25+-5;<br>
    t.setup(18,6,1);//Set temperature maximum variation around target

    h.setup(35,20,1); ///Humidifier setup
    //Heat cable
    tc.setup(25,10,1);

    //Serial.println("DONE!");

    //-------------------------------------------------------------------------
  time=millis();
}

void loop()
{
  //sgh.updateSTD();-----------------------------------------------------------
  //Sensors updating---------
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







