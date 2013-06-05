#ifndef SGH_H
#define SGH_H

#include "Actuators.h"
#include "Sensors.h"
//#include "State.h"

class SGH
{
    public:
        SGH();
        int init(); //Inizialize with standard values
        int update();
        ~SGH();
    protected:
    Actuators act;

Sensors sens;
State state;
    private:
};

#endif // SGH_H
