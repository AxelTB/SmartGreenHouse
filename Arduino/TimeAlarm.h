#ifndef TIMEALARM_H
#define TIMEALARM_H

#include "TimeCounter.h"


class TimeAlarm : protected TimeCounter
{
    public:
        TimeAlarm();
        TimeAlarm(unsigned long timeoutms);

        void set(unsigned long timeoutms);
        void reset();
        bool isElapsed();

    protected:
        unsigned long timeout;
    private:
};

#endif // TIMEALARM_H
