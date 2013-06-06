#include "SGH.h"


///Sensors defines---------------------------------
#define DHTPIN 8
#define DHTTYPE DHT11

#define LEVELPIN 5
#define LIGHTAPIN 0

#define LIGHTTAU 10
#define HUMIDITYTAU 120

#define GOODLEVEL HIGH
#define DHTMAXERRN 5

///------------------------------------------------
SGH::SGH()
{
    //ctor
}
/** @brief update
  *
  * @todo: document this function
  */
int SGH::update()
{
///Sensors updating-------------------------------------------------------------------------------
//Read temperature and humudity
    float h = dht.readHumidity();
    float t = dht.readTemperature();

//If some error occurred
    if (isnan(t) || isnan(h))
    {
        //If dht11 failed for too many times consecutively
        if((++this->dhterrN)>DHTMAXERRN)
        {
            state->esensors|=State::ESENS_DHTERR;
            state->log(State::CRITICAL,"Dht11 major error");
        }
        else
            state->log(State::ERROR,"Dht11 minor error");
    }
    else
    {
        //Clear DHT11 Error (If present)
        state->esensors&=!(State::ESENS_DHTERR);
        //Update temperature & humidity
        state->temp=t;
        state->humidity=h;

        //Set error count to 0
        this->dhterrN=0;
    }
    //Set level according to level sensor----------------------------------
    if(!(digitalRead(LEVELPIN)==GOODLEVEL) && state->level)
    {
        //Level just went low
        state->log(State::ERROR,"Low Water level");
    }
    state->level=(digitalRead(LEVELPIN)==GOODLEVEL);
    //Read Light sensor----------------------------------------------------
    state->light=analogRead(LIGHTAPIN);
    //Filtered variables
    state->flight=this->lplight.update(state->light);
    state->fhumidity=this->lphumidity.update(state->humidity);
///-----------------------------------------------------------------------------------------------------
  act.update(&this->state);
  //SD Log -------------------------------------------
  this->state.saveStats();
}

/** @brief init
  *
  * @todo: document this function
  */
int SGH::init()
{
Serial.begin(9600); // only required for testing
  Serial.print("Setup...");
  state.setup(SDPIN);

///Sensors Setup---------------------------------------------------------------------------------------
      pinMode(LEVELPIN,INPUT);

    //Set error number to 0
    this->dhterrN=0;
    this->dht=DHT(DHTPIN,DHTTYPE);
    this->dht.begin();
    //Filter definition
    this->lplight.setup(LIGHTTAU);
    this->lphumidity.setup(HUMIDITYTAU);

///Actuators---------------------------------------------------------------------------------------------
  act.setup();
  Serial.println("DONE!");
}


SGH::~SGH()
{
    //dtor
}
