# EUFS Dashboard 2016/2017

Designed to output the current RPM, gear, shift indicator and engine warnings of the car.

Hardware:
--------------------------------
- PCB design was made with Altium Designer and is revolving around the Atmega328p chip by Atmel.
- As we were not sure how we would supply the PCB, we left 2 options - TLV1117 or MC34063. The TLV proved capable of supplying enough current thus the second option was not implemented and tested. It is worth noting that it is not needed to solder the whole MC34063 power supply module.  That includes R5, R7, R13, R14, R15, C11, D17, L2 and U5.
- Data to the dashboard is sent via UART by the used at the time TI myRio but other possible headers have also been left out in case they are needed.
- As the whole steering wheel needs to be detachable the connection from the dashboard to the car hub is detachable via a standard stereo jack. Due to its limitation it was not possible to fit both data lines of UART. Thus the dashboard is not capable of transmitting information. Pinout of the headphone jack is VCC - Signal - GND (tip - middle - casing). Color coding for that is followed through.
- The dashboard itself is also equipped with a LED driver TC5947 which is essentially a shift register which is capable of whistanding large current and can also control brightness on the fly.


*ATTENTION: On the manufactured PCBs there are 2 errors:*
- Ressistor R16 is not connected to ground. I suggest scraping off the ground plane around it and connecting it via that.
- GND test pad on the bottom side of the PCB is not connected to ground as well. If needed employ the technique mentioned above.


Software:
-------------------------------
I have tried tried to objectify the whole dashboard software. The only dependencies it has is simply the arduino libraries. Speaking of which the whole software is basically made possible because of the Arduino libraries and compatabilities. It is centred around the .ino file with supporting .cpp class files. The initial idea was to make it as simple as possible without any speed compromises

How to flash:
------------------------------
1. Plug in AVR programmer into Dashboard ICSP headers
2. Flash with avrdude (downloadable from the web) with command:
avrdude -p m328p -P [COMport] -c avrisp -b 19200 -u -U lfuse:w:0xff:m -U flash:w:"[.ino.hex file location]":i
NOTE: You typically get incorrect signature at first try.
