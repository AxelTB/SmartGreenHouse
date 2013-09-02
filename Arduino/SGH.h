/*******************************************************************
*                   ==SmartGreenHouse==
*   SGH Class Definition
*   Created: 17/02/2013
*   Author:  Ax
*   License: CC BY-SA 3.0
*            http://creativecommons.org/licenses/by-sa/3.0/
*=====================================================================
 * SmartGreenHouse class
 * Main class
 ********************************************************************/
#ifndef SGH_H
#define SGH_H


#include <DHT.h>
#include "State.h"
#include "DigitalOut.h"
#include "Comparator.h"
#include "Fan.h"
//Saved defines---------------
#define DHTMAXERRN 5
/**
* @brief Higher level interface.
*   Provide function to set simple behaviour for the SmartGreenHouse system.
*
*
*/
class SGH
{
public:
    ///Standard Constructor
    SGH();
    ///Standard destructor
    ~SGH();
//Public methods----------------------------------------
///Update system according to configured modules
    int update();

//Sensors method (Implemented in Sensors.cpp)
    int attachDHT(uint8_t pin,uint8_t type); ///Attach new DHT
    int updateDHT(); ///Update status according to DHT measurements (Obsolete)

/*//Log methods----------------------------------------------------------------------
    int logInit(uint8_t sdPin,bool serialOut=true); ///Initialize sd & logging on defined pin
    int saveStats(); ///Save statistics
    int log(byte level,char *data); ///Log char string (On log.txt file)
    ///Loglevel---------------------
    static const unsigned short CRITICAL=3;
    static const unsigned short ERROR=2;
    static const unsigned short INFORMATION=1;
    static const unsigned short DEBUG=0;
//------------------------------------------------------
State state;*/
protected:

private:
    //Sensors variables----------------
    DHT dht; ///DHT Sensor
    unsigned short dhterrN;
};

#endif // SGH_H
