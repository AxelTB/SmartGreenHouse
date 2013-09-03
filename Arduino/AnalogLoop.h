#ifndef ANALOGLOOP_H
#define ANALOGLOOP_H

#include "Loop.h"
#include "AnalogOut.h"
#include "SGHPID.h"
class AnalogLoop : public Loop
{
    public:
        /** Default constructor */
        AnalogLoop();
        int operator<<(AnalogOut);
        int operator<<(SGHPID);
    protected:
    private:
};

#endif // ANALOGLOOP_H
