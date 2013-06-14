#include <SGH.h>
#include <DHT.h>
#include <SD.h>

#define SDP 9
#define DHTP 8
#define DELAYSECONDS 5
SGH sgh;
void setup()
{
	sgh.logInit(SDP);
	sgh.attachDHT(DHTP,DHT11);
}

void loop()
{
	sgh.updateDHT();
	sgh.saveStats();
	delay(DELAYSECONDS*1000l)
}
