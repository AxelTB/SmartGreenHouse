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
        void kill();

    protected:
        unsigned long timeout;
        bool active;
    private:
};

#endif // TIMEALARM_H
