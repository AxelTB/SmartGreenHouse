#ifndef ANALOGOUT_H
#define ANALOGOUT_H
#include <Arduino.h>

class AnalogOut
{
public:
    AnalogOut();

    int init(int pin);
    int init(int pin,uint16_t minCommand,uint16_t maxCommand);

    int set(int value);
    int set(short value);
protected:
private:
};

#endif // ANALOGOUT_H
