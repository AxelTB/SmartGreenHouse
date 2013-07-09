/*******************************************************************
*                   ==SmartGreenHouse==
*   SGH Implementation File
*   Created: 17/02/2013
*   Author:  Ax
*   License: CC BY-SA 3.0
*            http://creativecommons.org/licenses/by-sa/3.0/
*=====================================================================*
 *
 * Contains
 ********************************************************************/

#include "SGH.h"


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

#define MAXTEMP 40///Maximum temperature allowed for the system

//Modular methods

int SGH::update()
{
/** @brief Update SmartGreenHouse
  *
  * Returns 0 if everything fine
  * Update DHT and save statistics
  */
    this->updateDHT(); //Update DHT Status
    if(this->state.sdstatus) //If SD configured
        this->saveStats(); //Log statistics

    return 0;
}
//-------------------------------------------------

SGH::SGH()
{
    ///Unused
}

/** @brief Standard Update funcion
  *
  * @todo: document this function
  */
int SGH::updateSTD()
{

}

/** @brief Standard Init
  *
  * Standard initialization
  * To be used only with updateSTD
  */
int SGH::initSTD()
{

}


SGH::~SGH()
{
    //dtor
}


