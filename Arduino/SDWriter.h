#ifndef SDWRITER_H
#define SDWRITER_H

#include "SGHWriter.h"
#include <SD.h>

#define SDWFILENAME "bho.log"
class SDWriter : public SGHWriter
{
    public:
        /** Default constructor */
        SDWriter();
        SDWriter(uint8_t sdPin);
        void setPin(uint8_t sdPin);
        virtual int write(int val);
        virtual int write(const char* str);
    protected:
        uint8_t status; ///0: reset   1: SD Initialized (No file open) 2: file open

        uint8_t sdPin;
        int initSD(); ///-1: SD Init Error    -2: file open error
        File fout;
    private:
};

#endif // SDWRITER_H
