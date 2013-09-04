#include "SGHWriter.h"

SGHWriter::SGHWriter()
{
    this->next=0;
}
/** @brief operator<<
  *
  * @todo: document this function
  */
int SGHWriter::addWriter(SGHWriter *sghw)
{
    if(this->next==0) //If this is the last
        this->next=sghw; //Append the new one
    else
        this->next->addWriter(sghw); //Not my problem

}

/** @brief write
  *
  * @todo: document this function
  */
int SGHWriter::write(const char* str)
{
    return this->next->write(str); ///Write to next target
}

/** @brief write
  *
  * @todo: document this function
  */
int SGHWriter::write(int val)
{
return this->next->write(val); ///Write to next target
}

