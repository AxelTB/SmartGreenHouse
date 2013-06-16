/*******************************************************************
*                   ==SmartGreenHouse==
*   Low Pass Filter
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Fan output.
Re-map fan power between minimum and maximum command.
Implements an air circle routine.
********************************************************************/
#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H


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

#endif // LOWPASSFILTER_H
