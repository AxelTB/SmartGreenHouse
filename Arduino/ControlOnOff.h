/***
* SmartGreenHouse ControlOnOff
*
* Author: Axxx
*/
/*
Day 21~23
 Night 18
 */

#define LOWBOUND 1
#define HIGHBOUND 30

#define MAXFAULT 10

#define MAXONTIME  (300000l) //5 min
#define MINOFFTIME (300000l) //5 min
#define MINONTIME (60000) //1 min

#define MEDTIME ((float) (MINONTIME+MINOFFTIME)/1000)
class ControlOnOff
{
public:
    void setup(unsigned short delta);
    void setup(unsigned short delta,unsigned long MaxOnTime,unsigned long MinOnTime,unsigned long MinOffTime,int HighBound,int LowBound);
    int updateStatus(float temp);
    unsigned short getStatus();
    void setTarget(float Target);
    float getTarget();
    unsigned short adaptiveUpdate(float temp);
    
    void DebugStatistic(char *dbgstr);
private:
    
    short status;
    unsigned short nfault,delta;
    unsigned long uptime,lasttransition,nextdelay;

    //Treesholds in common and differential
    float tcommon,tdiff;
    //Target temperature
    float target;
    //Time constants
    unsigned long MaxOnTime,MinOnTime,MinOffTime;
    //Maximum ratings
    int HighBound,LowBound;
    //Statistic variables
    float stmedian,sthigh,stlow;
};
/** @brief UpdateStatus
 *         return  >=0 Status updated
 *                  -2 Temp out of bound
 *                  -1
 *                 <0 Not updated
 *
 *
 * @todo: document this function
 */
int ControlOnOff::updateStatus(float temp)
{

    //Check for too long uptime------------------------------------------
    if(this->status==1 && (millis()-this->uptime)>MaxOnTime && MaxOnTime>0)
    {
        //Shut down for at least MINOFFTIME
        this->status=0;
        this->uptime=0;
        this->nextdelay=MinOffTime;

        return 3;
    }
    //Evaluate if temp realistic-----------------------------------------
    if(temp<LowBound||temp>HighBound)
    {
        //If not try again in half minute
        this->nextdelay=30000;
        nfault++;
        //If unvalid for enought
        if(nfault>MAXFAULT)
        {
            this->status=false;
            return 66;
        }
        return -2;
    }
    else if(this->nfault>0)
        this->nfault=0;

    /*if(hour<7||hour>20)
        setTarget(18);
    else
        setTarget(23);
*/
    return adaptiveUpdate(temp);


}


/** @brief getStatus
 *
 * @todo: document this function
 */

unsigned short ControlOnOff::getStatus()
{
    return this->status;
}

/** @brief adaptiveUpdate
 *
 * @todo: document this function
 */
unsigned short ControlOnOff::adaptiveUpdate(float temp)
{
    //Evaluate treeshold
    float mintemp=tcommon-tdiff;
    float maxtemp=tcommon+tdiff;

    //Statistical temperature---------------------------------------------
    this->stmedian=temp/MEDTIME+(this->stmedian*(1.0f-1.0/MEDTIME));
    if(this->stlow > temp)
        this->stlow= temp;
    else if(this->sthigh<temp)
        this->sthigh=temp;

    //Avoid too close transitions and update status-----------------------
    if((millis()-lasttransition)>this->nextdelay)
    {
        this->lasttransition=millis();

        if(temp<=mintemp)
        {
            this->status=1;
            if(this->uptime==0)
            {
                this->uptime=millis();
                this->nextdelay=MinOnTime;
            }
            else
                this->nextdelay=0;
        }
        else if(temp>=maxtemp)
        {
            //If was on
            if(this->status==1)
            {
                this->status=0;
                this->uptime=0;
                this->nextdelay=MinOffTime;
            }
            else
                this->nextdelay=0;

        }
        else this->nextdelay=0;
          
        return 0;
    }
    else return 1;
    //--------------------------------------------------------
}



/** @brief setup
 *
 * @todo: document this function
 */
void ControlOnOff::setup(unsigned short delta)
{
    this->status=0;
    this->nfault=0;
    this->uptime=0;
    this->lasttransition=millis();
    this->nextdelay=0;

    //Maximum oscillation around target
    this->delta=delta;
    this->target=23;
    this->tcommon=23;
    this->tdiff=delta/2;

    //Load default time constant
    this->MaxOnTime=MAXONTIME;
    this->MinOffTime=MINOFFTIME;
    this->MinOnTime=MINONTIME;

    //Absolute maximum
    this->HighBound=HIGHBOUND;
    this->LowBound=LOWBOUND;
}

/** @brief setTarget
 *
 * @todo: document this function
 */
void ControlOnOff::setTarget(float Target)
{
    this->target=Target;
    this->tcommon=Target;
}

 /** @brief getTarget
  *
  * @todo: document this function
  */
float ControlOnOff::getTarget()
{
    return this->target;
}



/** @brief DebugStatistic
 *
 * @todo: document this function
 */
void ControlOnOff::DebugStatistic(char *dbgstr)
{
    sprintf(dbgstr,"%d,%d,%d",(int)this->stmedian,(int)this->stlow,(int)this->sthigh);
}

/** @brief setup
  *
  * @todo: document this function
  */
void ControlOnOff::setup(unsigned short delta,unsigned long fMaxOnTime,unsigned long fMinOnTime,unsigned long fMinOffTime,int HighBound,int LowBound)
{
    setup(delta);
    //Load given time constant
    this->MaxOnTime=fMaxOnTime;
    this->MinOffTime=fMinOffTime;
    this->MinOnTime=fMinOnTime;
    //Load given bound
    this->HighBound=HighBound;
    this->LowBound=LowBound;
}




