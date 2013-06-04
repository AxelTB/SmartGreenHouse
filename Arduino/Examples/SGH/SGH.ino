#include <DHT.h>
#include <SD.h>
#include <Wire.h>
/*******************************************************************
 *                   ==SmartGreenHouse==
 *   Main sketch
 *   Created: 17/02/2013
 *   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 *=====================================================================
 * All available documentation on https://github.com/AxelTB/SmartGreenHouse
 ********************************************************************/
#include <SGH.h>

SGH sgh;
long time;

void setup()
{
  sgh.init();
  time=millis();
}

void loop()
{
  sgh.update();
  //Wait for looptime---------------------------------------------
  while(millis()-time<LOOPT*1000);
  time=millis();
}







