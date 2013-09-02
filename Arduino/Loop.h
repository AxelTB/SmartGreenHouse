#ifndef LOOP_H
#define LOOP_H


class Loop
{
    public:
        /** Default constructor */
        Loop();
        void setVar(int var); ///Set state variable
        int getVar(); ///Get state variable
        void operator<<(int var);

        virtual int dump(int *var,int *out);
        virtual int control(); ///Activate the loop control (Must be redefined in every classs)
        /** Default destructor */
        ~Loop();
    protected:
        int var;
    private:
};

#endif // LOOP_H
