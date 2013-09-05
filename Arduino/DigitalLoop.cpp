#include "DigitalLoop.h"

DigitalLoop::DigitalLoop()
{
    //ctor
}

DigitalLoop::~DigitalLoop()
{
    //dtor
}
/** @brief operator<<
  *
  * @todo: document this function
  */
int DigitalLoop::operator<<(Comparator *comp)
{
    this->ctrl=comp;
}

/** @brief operator<<
  *
  * @todo: document this function
  */
int DigitalLoop::operator<<(DigitalOut *dout)
{
    this->out=dout;
}


/** @brief Valorize var as the system variable and out as the output state
  *
  * (documentation goes here)
  */
int DigitalLoop::dump(int *var,int *out)
{
    *var=this->var;
    *out=this->out->get();
}

