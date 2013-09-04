#include "SGHWriter.h"

SGHWriter::SGHWriter()
{
    this->next=0;
}
/** @brief operator<<
  *
  * @todo: document this function
  */
int SGHWriter::operator<<(SGHWriter *sghw)
{
    this->next=sghw;

}

/** @brief write
  *
  * @todo: document this function
  */
int SGHWriter::write(const char* str)
{
    return this->next.write(str); ///Write to next target
}

/** @brief write
  *
  * @todo: document this function
  */
int SGHWriter::write(int val)
{
return this->next.write(val); ///Write to next target
}

