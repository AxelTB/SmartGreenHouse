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
