/*******************************************************************
*                   ==SmartGreenHouse==
*   Fan Class
*   Created: 17/02/2013
*   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
Fan output.
Re-map fan power between minimum and maximum command.
Implements an air circle routine.
********************************************************************/
#ifndef FAN_H
#define FAN_H
#include <Arduino.h>

/**
* @brief Fan module.
*   Provides function to control a dc fan trought a PWM output.
*
*
*/
class Fan
{
public:
  /** Setup
   * pin -> fan pin
   * minCommand & maxCommand -> minimum and maximum accepted command.
   *
   * cicleTSec -> Time interval between minimum airflow control
   * airflowTarget -> Airflow targed intended as raw_command*sec
   *
   * Everyting below minCommand will be 0 (To avoid fan noise), everything greather than maxCommand will be MaxCommand
   **/
  void setup(uint8_t pin,uint16_t minCommand,uint16_t maxCommand);
  void setup(uint8_t pin,uint16_t minCommand,uint16_t maxCommand,float cicleTSec,float airflowTarget);

  /*** Set fan speed
   * command -> 0-100 set fan percentage
   * 0 fan off
   * 1 minCommand
   * 100 maxCommand
   *
   * Returns fan output raw
   */
  uint8_t setSpeed(uint8_t command);

  /*** Fan stop
   Stop the fan don't regarding air changing cicle */
  void stop();
protected:
private:
  uint8_t pin; //Fan pin
  uint16_t minCommand,maxCommand; //Maximum and minimum command available
  float KCommand;
  long cicleTms,airflowTarget; //Fresh air control variables
  long cicleStart, airflowSum;  //Freash air cicle temporary variables
  long lastCallTms;

  uint8_t pwm;
};

#endif // FAN_H

