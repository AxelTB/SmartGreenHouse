#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H


class LowPassFilter
{
   public:
//Pole tau and dt setting. dt_s is LOOPT and tau_s must be tuned for the
        void setup(float tau_s)
        {
            this->a=tau_s/(tau_s+LOOPT);
        }
        float update(float value)
        {
            this->sum*=1-a;
            this->sum+=a*value;

            return this->sum;
        }
        float a;
        float sum;
};

#endif // LOWPASSFILTER_H
