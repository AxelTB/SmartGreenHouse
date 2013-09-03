#ifndef SDWRITER_H
#define SDWRITER_H

#include "SGHWriter.h"


class SDWriter : public SGHWriter
{
    public:
        /** Default constructor */
        SDWriter(uint8_t sdPin);
        virtual int write(int val);
        virtual int write(const char* str);
    protected:
    private:
};

#endif // SDWRITER_H
