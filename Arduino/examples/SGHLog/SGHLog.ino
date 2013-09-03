/*******************************************************************
  *                   ==SmartGreenHouse==
  *   SGH Implementation File
  *   Created: 17/02/2013
  *   Author:  Ax
  *   License: CC BY-SA 3.0
  *            http://creativecommons.org/licenses/by-sa/3.0/
  	       DHT Code from: ladyada
  *=====================================================================*
   *
    * Contains
     ********************************************************************/
#include <SGH.h>
#include <DHT.h>
#include <SD.h>

#define SDP 9  		//SD cs pin
#define DHTP 8 		// DHTXX Pin
#define DELAYSECONDS 2 	//Delay between measurements (Set SGHStats.m accordingly if changed)

DHT dht(DHTP,DHT11);
Log logger;

Loop lh,lt; ///Fake loops (No out nor control)
void setup()
{
logger.init(DHTP); ///Initialize with log on serial Serial 9600 baud (std)
//logger.init(DHTP,115200); ///Initialize with serial log at 115200 baud (Only use baudare compatible with Serial.begin)
//logger.init(DHTP,0); ///Initialize without serial

}
int h,t;
void loop()
{
///Read data from DHT
h=dht.readHumidity();
t=dht.readTemperature();

///Save state variable into loop
lh<<h;
lt<<t;

///Log loop state (For this kind of loop the output state will always be 0)
logger<<lt;
logger<<lh;

delay(DELAYSECONDS*1000l);
}
