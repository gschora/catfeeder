catfeeder
=========

This will be an automatic cat feeding machine with rfid.

Hardware used:

x teensy 3.1 as microcontroler
	https://www.pjrc.com/teensy/index.html
x chronodot 2.1 as timekeeping device
	http://www.adafruit.com/product/255
x i2c fram for storing things
	http://www.adafruit.com/products/1895
x 125Khz rfid uart module from seeedstudio for tracking when the cat wants to feed
	http://www.seeedstudio.com/depot/125Khz-RFID-module-UART-p-171.html
x rfid tags from seeedstudio
	http://www.seeedstudio.com/depot/RFID-tag-combo-125khz-5-pcs-p-700.html
x ultra tiny glass rfidtags
	http://www.exp-tech.de/Shields/Wireless/RFID/RFID-Glass-Capsule-125kHz.html
x level shifters for shifting 5v levels to 3v of teensy
	http://www.watterott.com/de/Level-Shifter
x servo from the fritzing starter kit
x rostock max v2 from seemecnc for 3d printing parts
	http://seemecnc.com/products/rostock-max-complete-kit

Software used:
x teensy 1.20
x arduino ide 1.0.5
x SublimeText 3
x Stino for Sublime text
	https://github.com/Robot-Will/Stino

Libraries used:
x rtclib
	https://github.com/mizraith/RTClib
x fram lib from adafruit
	https://github.com/adafruit/Adafruit_FRAM_I2C
x rfid library
	https://github.com/johannrichard/SeeedRFIDLib
	Here I had to make some changes to use the hardwareserialport from Teensy not the Softserial-lib.
x arduino serialcommand for parsing commands over serial
	https://github.com/scogswell/ArduinoSerialCommand