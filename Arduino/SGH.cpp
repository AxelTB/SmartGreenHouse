#include "SGH.h"

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
sens.update(&this->state);
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
//Actuators-----------------------------------

  act.setup();
//Sensors--------------------------------------
  sens.setup();

  Serial.println("DONE!");
}


SGH::~SGH()
{
    //dtor
}
