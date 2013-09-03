#include "SGHPID.h"

SGHPID::SGHPID()
{
    this->kp=0;
    this->ki=0;
    this->kd=0;

    this->lastErr=0;
    this->sumErr=0;
}

/** @brief update PID status
  *
  *
  */
int SGHPID::update(double error)
{

    double diff=(error-this->lastErr)*((double)this->tc.getElapsedMillis/1000); ///Evaluate D
    this->lastErr=err; ///Save current error

    this->sumErr+=error; ///Sum current error to I

    return kp*error+ki*this->sumErr+kd*diff; ///All other stuff
}

/** @brief set constant and maximum integral error
  *
  *
  */
void SGHPID::set(double kp,double ki,double kd,double maxI)
{
    this->kp=kp;
    this->ki=ki;
    this->kd=kd;
    this->maxI=maxI;
}

/** @brief Full constructor
  *
  *
  */
 SGHPID::SGHPID(double kp,double ki,double kd,double maxI)
{
    set(kp,ki,kd,maxI);
}



SGHPID::~SGHPID()
{
    //dtor
}
