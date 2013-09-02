#ifndef LOG_H
#define LOG_H
#include "loop.h"

class Log
{
    public:
        /** Default constructor */
        Log();
        int init(uint8_t sdPin,int baudrate=9600);
        int operator<<(Loop l);
        int operator<<(const char *str);
        int operator<<(int var);
        /** Default destructor */
        virtual ~Log();
    protected:
    private:
};

#endif // LOG_H
