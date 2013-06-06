#ifndef SGH_H
#define SGH_H

#include <DHT.h>
#include "Actuators.h"

class SGH
{
    public:
        SGH();
        int init(); //Inizialize with standard values
        int update();
        ~SGH();
    protected:
    Actuators act;
State state;
    private:

    ///Sensors variables----------------
    DHT dht;
    unsigned short dhterrN;
};

#endif // SGH_H
