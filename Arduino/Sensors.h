
/*******************************************************************
*                   ==SmartGreenHouse==
*   Sensors Class
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Sensors Class
Contains all sensor procedure to update state variable
********************************************************************/


#ifndef SENSORS_H
#define SENSORS_H

#include "State.h"
#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT11

#define LEVELPIN 5
#define LIGHTAPIN 0

#define LIGHTTAU 10
#define HUMIDITYTAU 120

#define GOODLEVEL HIGH
#define DHTMAXERRN 5
class Sensors
{
//To be used with noisy input
    class LowPassFilter
    {
    public:
//Pole tau and dt setting. dt_s is LOOPT and tau_s must be tuned for the
        void setup(float tau_s)
        {
            this->a=tau_s/(tau_s+LOOPT);
        }
        float update(float value)
        {
            this->sum*=1-a;
            this->sum+=a*value;

            return this->sum;
        }
        float a;
        float sum;
    };
public:
    int setup();
    //Update status with measured data
    int update(State *state);
protected:
private:
    DHT dht;
    unsigned short dhterrN;
    LowPassFilter lplight,lphumidity;

};

#endif // SENSORS_H

