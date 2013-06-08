#include "SGH.h"


///Sensors defines---------------------------------
#define DHTPIN 8
#define DHTTYPE DHT11

#define LEVELPIN 5
#define LIGHTAPIN 0

#define LIGHTTAU 10
#define HUMIDITYTAU 120

#define GOODLEVEL HIGH

///------------------------------------------------
///Modular methods
/** @brief update
  *
  * @todo: document this function
  */
int SGH::update()
{
    this->updateDHT();
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
        this->state.log(State::ERROR,"Low Water level");
    }
    this->state.level=(digitalRead(LEVELPIN)==GOODLEVEL);
    //Read Light sensor----------------------------------------------------
    this->state.light=analogRead(LIGHTAPIN);
    //Filtered variables
    //this->state.flight=this->lplight.update(state->light);
    //this->state.fhumidity=this->lphumidity.update(state->humidity);
///-----------------------------------------------------------------------------------------------------
  act.update(&this->state);
  //SD Log -------------------------------------------
  this->state.saveStats();
}

/** @brief init
  *
  * @todo: document this function
  */
int SGH::initSTD()
{
Serial.begin(9600); // only required for testing
  Serial.print("Setup...");
  state.setup(SDPIN);

///Sensors Setup---------------------------------------------------------------------------------------
      pinMode(LEVELPIN,INPUT);
    this->attachDHT(DHTPIN,DHTTYPE);
    //Filter definition
    //this->lplight.setup(LIGHTTAU);
    //this->lphumidity.setup(HUMIDITYTAU);

///Actuators---------------------------------------------------------------------------------------------
  act.setup();
  Serial.println("DONE!");
}


SGH::~SGH()
{
    //dtor
}


