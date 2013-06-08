#ifndef SGH_H
#define SGH_H

#include <DHT.h>
#include "Actuators.h"

class SGH
{
    public:
        SGH();
        int initSTD(); //Inizialize with standard values
        int updateSTD();
        ~SGH();
///Public methods----------------------------------------
        int update(); //Update system according to configured modules

        ///Sensors method (Implemented in Sensors.cpp)
        int attachDHT(uint8_t pin,uint8_t type); //Attach new DHT
        int updateDHT(); //Update status according to DHT measurements

        ///Log methods
        int logInit(uint8_t sdPin); //Initialize sd & logging on defined pin
///------------------------------------------------------
    protected:
    Actuators act;
State state;
    private:

    ///Sensors variables----------------
    DHT dht;
    unsigned short dhterrN;
};

#endif // SGH_H
