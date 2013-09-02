#ifndef LOG_H
#define LOG_H
#include "Loop.h"
#include <SD.h>
class Log : public SDClass
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
    bool sdstatus;
    int baudrate;
    private:
};

#endif // LOG_H
