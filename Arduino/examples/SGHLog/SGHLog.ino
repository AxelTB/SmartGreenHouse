#include <SGH.h>
#include <DHT.h>
#include <SD.h>

#define SDP 9  		//SD cs pin
#define DHTP 8 		// DHTXX Pin
#define DELAYSECONDS 2 	//Delay between measurements (Set SGHStats.m accordingly if changed)

SGH sgh; //Create new empty SmartGreenHouse

void setup()
{
	sgh.logInit(SDP); //Init log module 
	sgh.attachDHT(DHTP,DHT11); //Initialize DHTXX Sensor
	//sgh.attachDHT(DHTP,DHT22); //DHT22 Version
}

void loop()
{
	sgh.update(); //Update defined sensor and save data on SD
	delay(DELAYSECONDS*1000l);
}
