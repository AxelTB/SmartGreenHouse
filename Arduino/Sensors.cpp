#include "SGH.h"
///SGH Sensors Implementation file
/***
Returns: 0 all good!
**/
int SGH::attachDHT(uint8_t pin,uint8_t type)
{
    //Set error number to 0
    this->dhterrN=0;
    this->dht=DHT(pin,type);
    this->dht.begin();
    return 0;
}
/***
Returns 0 -> OK
        #ofConsecutivesError -> Minor error
        -1 -> Major error
**/
int SGH::updateDHT()
{
    //Read temperature and humudity
    float h = dht.readHumidity();
    float t = dht.readTemperature();

//If some error occurred
    if (isnan(t) || isnan(h))
    {
        //If dht11 failed for too many times consecutively
        if((++this->dhterrN)>DHTMAXERRN)
        {
            this->state.esensors|=State::ESENS_DHTERR;
            this->state.log(State::CRITICAL,"Dht11 major error");
        }
        else
            this->state.log(State::ERROR,"Dht11 minor error");

        return this->dhterrN; //Returns number of errors
    }
    else
    {
        //Clear DHT11 Error (If present)
        this->state.esensors&=!(State::ESENS_DHTERR);
        //Update temperature & humidity
        this->state.temp=t;
        this->state.humidity=h;

        //Set error count to 0
        this->dhterrN=0;
    }

}
