#ifndef SGHPID_H
#define SGHPID_H

#include "TimeCounter.h"
class SGHPID
{
    public:
        /** Default constructor */
        SGHPID();
        SGHPID(double kp,double ki,double kd,double maxI=1500);

        void set(double kp,double ki,double kd,double maxI=1500);
        int update(double error);
        /** Default destructor */
        virtual ~SGHPID();
    protected:
    TimeCounter tc;
    double lastErr,sumErr;
    private:
};

#endif // SGHPID_H
