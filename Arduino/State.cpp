#include "State.h"
State::State()
{
  //Initialize error variable
  this->esensors=0;
  this->eactuators=0;

  this->heater=0;
  this->heaterCable=0;
  this->humidifier=0;
  this->outFan=255;

}

