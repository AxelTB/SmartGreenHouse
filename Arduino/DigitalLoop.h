#ifndef DIGITALLOOP_H
#define DIGITALLOOP_H

#include "Loop.h"
#include "DigitalOut.h"
#include "Comparator.h"

class DigitalLoop : public Loop
{
    public:
        /** Default constructor */
        DigitalLoop();
        int operator<<(DigitalOut *);
        int operator<<(Comparator *);
virtual int dump(int *var,int *out);
        //virtual int dump(int *var,int *out);
        /** Default destructor */
        virtual ~DigitalLoop();
    protected:
    Comparator *ctrl;
    DigitalOut *out;
    private:
};

#endif // DIGITALLOOP_H
