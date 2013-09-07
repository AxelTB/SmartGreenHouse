SmartGreenHouse
===============

Smart Greenhouse designed for urban garden.
The new version is projected to be easier to personalize.
Using any sensor and any analog or digital output with the given controller is possible to create a fully modular greenhouse.


Documentation
=============
The full documentation is in the Doc/rtf/rtfman.rtf file.
Doxyfile is on the main path of the repo, using it you can obtain the html version.

Install Doxygen and run it in the main path to generate documentation". A new directory named Doc should be created containing the HTML version of the codumentation

Principle of Use
================
Setup:
- Create a loop (DigitalLoop o AnalogLoop according to the actuators)
- Create a controller (For you must use Comparator and PID for Analog)
- Link the controller to the loop (e.g. digitalloop<<controller)
Loop:
- Read your sensors
- Input the error to the loop (If you want a Fan keeping a temperature of 30° you need "analogloop<<(30-temperature)" )
The control purpouse is to reduce to 0 the given Error. Since all loop class simulate a negative feedback loop the sign of the command given to the controller will be different from the given error. Since most of the actuator used in this applications are only positive commanded a simple assumption is:
The Output is active if the given error is below 0. (eg. The same example with aheater will be "digitalloop<<(temperature-30)" because we want the heater to be active if temperature is below 30°C).
- Control the actuator just using the function control() of the loop

Hardware
========
- Any Arduino (should work with Energia too but I haven't tested yet)
- A gennehouse
- A sensor (And the code to read from iit)

Something, something, something...
~ An SD Interface with SD card Fat Formatted
~ A bluetooth to serial converter
~ Heater, Humidifier, Mist maker, Heating Cable...

Code
====
The code should be self-explanatory. I'll always add the sketch(s) I'm currently using on my greenhouse.


For something more:
http://axengineering.wordpress.com/
