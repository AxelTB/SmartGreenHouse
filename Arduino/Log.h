#ifndef LOG_H
#define LOG_H
#include "Loop.h"
#include <SD.h>
#include "SGHWriter.h"
#include "DigitalOut.h"
class Log
{
    public:

        Log();
        void init(uint8_t sdPin,int baudrate=9600);

        //Writing functions
        int operator<<(Loop l);
        int operator<<(const char *str);
        int operator<<(int var);
        int operator<<(DigitalOut d);
        //Setting function

        int operator<<(SGHWriter *w);


        /** Default destructor */
        virtual ~Log();
    protected:
    SGHWriter w;
    private:
};

#endif // LOG_H
