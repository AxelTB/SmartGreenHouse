#ifndef SGHWRITER_H
#define SGHWRITER_H


class SGHWriter
{
    public:
        /** Default constructor */
        SGHWriter();
        virtual int write(int val);
        virtual int write(const char* str);
        int operator<<(SGHWriter *);
    protected:
        SGHWriter *next;
    private:
};

#endif // SGHWRITER_H
