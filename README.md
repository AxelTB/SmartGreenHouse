SmartGreenHouse
===============

Smart Greenhouse designed for urban garden.
Created for Arduino using a DHT temperature and humidity sensor.
A fan, a humidifier and two heater (With a relay pack) are currently working of the full version.

Documentation
=============
The full documentation is in the Doc/rtf/rtfman.rtf file.
Doxyfile is on the main path of the repo, using it you can obtain the html version.

Branches
========
The master contains the prototype code.
The alpha version is for public use. Only log function is available. More feature will be soon added.

Documentation
=============
Install Doxygen and run it in the main path to generate documentation". A new directory named Doc should be created containing the HTML version of the codumentation"

Principle of Use
================
- Configure all sensors and actuators
- Run the SGH.update() function on the main loop

Log Example
===========
Simple SD Temperature & Humidity Logger. Prints on the serial line all data too.

Needs:
==
Hardware:

- Any Arduino
- An SD Interface with SD card Fat Formatted
- DHT11/DHT22 (And a pull-up resistors)
Software:
- Arduino SDK (Or any other stuff you like to use)
- SD Library (Included in the Arduino SDK)
- Adafruit's DHTXX Library

Everything you should know about DHTXX sensors (And the library) is here: http://learn.adafruit.com/dht

Code
====
The code should be in your Examples under SGH->SGHLog.

Defines:
- DHTP 		- DHTXX pin
- SDP		- SD CS pin
- DELAYSECONDS 	- Second between measurements

LogFiles:
- Temp.txt
	Raw Data
	Temperature, HR, ...
- Log.txt
Errors and log

Stats View
==========
Copy the TEMP.TXT file in the Same Folder as SGHStats.m
The file should be run by any Matlab-like interpreter. It shows all statistics, in this example the only nonzero data should be about temperature and humidity.
Statistics comprehend all fully integrated sensors and actuators in the prototype.



=======
Climatic control and log for urban garden automation.

Simply connect a DHTXX sensor to an Arduino, the core is done!
What do you need?
- SD Card module for temperature humidity log
- Digital actuators for heating cable o standard heater
- Light sensor
- Humidifier module with water level sensor
