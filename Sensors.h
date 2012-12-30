#ifndef SENSORS_H
#define SENSORS_H

#include "State.h"
#include <dht11.h>

#define DHT11PIN 8
#define LEVELPIN 9
#define LIGHTAPIN 0

#define LIGHTTAU 10
#define HUMIDITYTAU 120

#define GOODLEVEL HIGH
#define DHT11MAXERRN 5
class Sensors
{
  class LowPassFilter
  {
public:
    void setup(float tau_s,float dt_s)
    {
      this->a=tau_s/(tau_s+dt_s);
    }
    float update(float value)
    {
      this->sum*=1-a;
      this->sum+=a*value;

      return this->sum;
    }
    float a;
    float sum;
  };
public:
  int setup();
  //Update status with measured data
  int update(State *state);
protected:
private:
  dht11 DHT11;
  unsigned short dht11errN;
  LowPassFilter lplight,lphumidity;

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
    {
      state->esensors|=State::ESENS_DHT11ERR;
      state->log(State::CRITICAL,"Dht11 major error");
    }
    else
      state->log(State::ERROR,"Dht11 minor error");
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
  this->dht11errN=0;
  //Filter definition
  this->lplight.setup(LIGHTTAU,1);
  this->lphumidity.setup(HUMIDITYTAU,1);

}




#endif // SENSORS_H

