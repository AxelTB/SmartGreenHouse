#ifndef LOG_H
#define LOG_H
#include "Loop.h"
#include <SD.h>
#include "SGHWriter.h"
class Log : public SDClass
{
    public:
        /** Default constructor */
        Log();
        void init(uint8_t sdPin,int baudrate=9600);

        //Writing functions
        int operator<<(Loop l);
        int operator<<(const char *str);
        int operator<<(int var);

        //Setting function

        int operator<<(SGHWriter *w);

        /** Default destructor */
        virtual ~Log();
    protected:
    SGHWriter w;
    private:
};

#endif // LOG_H
