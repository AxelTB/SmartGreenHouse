#ifndef LOG_H
#define LOG_H
#include "Loop.h"
#include <SD.h>
class Log : public SDClass
{
    public:
    ///Loglevel---------------------
    static const unsigned short CRITICAL=3;
    static const unsigned short ERROR=2;
    static const unsigned short INFORMATION=1;
    static const unsigned short DEBUG=0;
        /** Default constructor */
        Log();
        int init(uint8_t sdPin,int baudrate=9600);
        int operator<<(Loop l);
        int operator<<(const char *str);
        int operator<<(int var);
        /** Default destructor */
        virtual ~Log();
    protected:
    bool sdstatus;
    int baudrate;
    private:
};

#endif // LOG_H
