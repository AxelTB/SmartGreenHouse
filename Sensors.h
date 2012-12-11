#ifndef SENSORS_H
#define SENSORS_H

#include "State.h"
#include <dht11.h>

#define DHT11PIN 8
#define LEVELPIN 14

#define GOODLEVEL LOW
#define DHT11MAXERRN 5
class Sensors
{
public:
    int setup();
    //Update status with measured data
    int update(State *state);
protected:
private:
    dht11 DHT11;
    unsigned short dht11errN;
};
/** @brief update
  *
  * @todo: document this function
  */
int Sensors::update(State *state)
{
    //Read temperature and humudity and store it in state-----------------
    if(DHT11.read(DHT11PIN)==DHTLIB_OK)
    {
        //Clear DHT11 Error (If present)
        state->esensors&=!(State::ESENS_DHT11ERR);
        //Update temperature & humidity
        state->temp=DHT11.temperature;
        state->humidity=DHT11.humidity;
	//Set error number to 0
	this->dht11errN=0;
    }
    else
    {
	    //If dht11 failed for too many times consecutively
	if((++this->dht11errN)>DHT11MAXERRN)
        	state->esensors|=State::ESENS_DHT11ERR;
	state->log(State::ERROR,"Dht11 minor error");
    }
    //Set level according to level sensor
    state->level=(digitalRead(LEVELPIN)==GOODLEVEL);
}

/** @brief setup
  *
  * @todo: document this function
  */
int Sensors::setup()
{
    pinMode(LEVELPIN,INPUT);
    //Set error number to 0
    this->dht11errN=0;
}




#endif // SENSORS_H
