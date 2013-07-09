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




//Modular methods------------------------------------------------------------------

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

/** @brief Standard Init (OBSOLETE)!!!
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


