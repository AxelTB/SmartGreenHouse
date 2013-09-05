/*******************************************************************
 *                   ==SmartGreenHouse==
 *   
 *   Created: 5/09/2013
 *   Author:  Ax
 *   License: CC BY-SA 3.0
 *            http://creativecommons.org/licenses/by-sa/3.0/
 * 	      DHT Library from: ladyada
 *=====================================================================*
 *
 * Example for a simple temperature ad humidity logger with a timered out
 *DHT11 connectted to pin 7
 *Relay module on pin 3
*
 * Uses ladyada's DHT library
 ********************************************************************/
#include <SGH.h>
#include <DHT.h>
#include <SD.h>
#include <SerialWriter.h>
//#define SDP 9  		//SD cs pin
#define DHTP 7 		// DHTXX Pin
#define FOGPIN 3        //Relay pin
#define DELAYSECONDS 2 	//Delay between measurements

#define BREAKPOINT while(!Serial.available());
DHT dht(DHTP,DHT11);
Log logger;

DigitalOut fog;
void setup()
{
  logger<<new SerialWriter(); //Hardware seria logger
  //logger.init(SDP,115200); ///Initialize with serial log at 115200 baud (Only use baudare compatible with Serial.begin)
  //logger.init(SDP); ///Initialize without serial

  fog.init(FOGPIN,5000,60000); //Init digital out
  Serial.println("Setup complete"); //After the creation of a SerialWriter you can still use the Serial instance as usual
}
int h,t;
void loop()
{
  ///Read data from DHT
  h=dht.readHumidity();
  t=dht.readTemperature();
  ///Update out status
  fog.commute();

  //Log
  logger<<t; //Temperature
  logger<<h; //And humidity 
  logger<<fog; //And, of course, fogger state
  logger<<";"; //Line end



  delay(DELAYSECONDS*1000l);
}

