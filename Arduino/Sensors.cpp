#include "Sensors.h"

/** @brief update
 *
 * @todo: document this function
 */
int Sensors::update(State *state)
{
    //Read temperature and humudity and store it in state variable-----------------
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
}

/** @brief setup
 *
 * @todo: document this function
 */
int Sensors::setup()
{
    pinMode(LEVELPIN,INPUT);

    //Set error number to 0
    this->dhterrN=0;
    this->dht=DHT(DHTPIN,DHTTYPE);
    this->dht.begin();
    //Filter definition
    this->lplight.setup(LIGHTTAU);
    this->lphumidity.setup(HUMIDITYTAU);

}



