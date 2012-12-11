/***
* SmartGreenHouse
*  Logger
* Author: Axxx
*
*/

#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED
#include <bv4236.h>

#define LOGFILE "log.txt"

class Logger
{
public:
    ///Add line to log
    static void add(int level,const char* stringa0,...);
protected:
private:
};

/** @brief setup
  *
  * @todo: document this function
  */
int Logger::setup()
{

}


/** @brief add
  *
  * @todo: document this function
  */
int Log::add(char *string)
{
    char dstr[20];
    outf = SD.open(LOGFILE,FILE_WRITE);
    if(!outf)
    {
        clock.getDateTime(dstr);
        outf.print(dstr);
        outf.print(" -> ");
        outf.println(string);
        // close the file:
        outf.close();

    }
    else
    {
        // if the file didn't open, print an error:
        Serial.println("error opening file");
        return -1;
    }
    return 0;
}

int Log::addRaw(char *string)
{
    outf = SD.open(LOGFILE,FILE_WRITE);
    if(!outf)
    {
 
        outf.print(string);
        // close the file:
        outf.close();

    }
    else
    {
        // if the file didn't open, print an error:
        Serial.println("error opening file");
        return -1;
    }
    return 0;
}
#endif // LOG_H_INCLUDED
