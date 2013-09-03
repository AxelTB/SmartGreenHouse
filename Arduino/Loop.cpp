/*******************************************************************
*                   ==SmartGreenHouse==
*   Fan implementation
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
********************************************************************/
#include "Loop.h"

Loop::Loop()
{
    //ctor
}

Loop::~Loop()
{
    //dtor
}

/** @brief return state variable
  *
  *
  */
int Loop::getVar()
{
    return this->var;
}

/** @brief Set state variable
  *
  *
  */
void Loop::setVar(int var)
{
    this->var=var;
}
/** @brief operator<<(float) sets the state variable as var

  * Same as calling setVar(float)
  *
  *
  */
void Loop::operator<<(int var)
{
    this->var=var;
}


/** @brief Valorize var with the variable value (And out to 0 for compatibilititituyfgfds)
  *
  *
  */
int Loop::dump(int *var,int *out)
{
    *var=this->var;
    *out=0;
}
/** @brief Just an empty function
  *
  *  Returns The Answer to the Ultimate Question of Life, the Universe, and Everything.
  */
int Loop::control()
{
    return '*'; ///Return Everything
}

