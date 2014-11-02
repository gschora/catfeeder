catfeeder
=========

This will be an automatic cat feeding machine with rfid.

Hardware used:

- teensy 3.1 as microcontroler
	https://www.pjrc.com/teensy/index.html
- chronodot 2.1 as timekeeping device
	http://www.adafruit.com/product/255
- i2c fram for storing things
	http://www.adafruit.com/products/1895
- 125Khz rfid uart module from seeedstudio for tracking when the cat wants to feed
	http://www.seeedstudio.com/depot/125Khz-RFID-module-UART-p-171.html
- rfid tags from seeedstudio
	http://www.seeedstudio.com/depot/RFID-tag-combo-125khz-5-pcs-p-700.html
- ultra tiny glass rfidtags
	http://www.exp-tech.de/Shields/Wireless/RFID/RFID-Glass-Capsule-125kHz.html
- level shifters for shifting 5v levels to 3v of teensy
	http://www.watterott.com/de/Level-Shifter
- servo from the fritzing starter kit
- rostock max v2 from seemecnc for 3d printing parts
	http://seemecnc.com/products/rostock-max-complete-kit

Software used:
- teensy 1.20
- arduino ide 1.0.5
- SublimeText 3
- Stino for Sublime text
	https://github.com/Robot-Will/Stino

Libraries used:
- rtclib
	https://github.com/mizraith/RTClib
- fram lib from adafruit
	https://github.com/adafruit/Adafruit_FRAM_I2C
- rfid library
	https://github.com/johannrichard/SeeedRFIDLib
	Here I had to make some changes to use the hardwareserialport from Teensy not the Softserial-lib.
- arduino serialcommand for parsing commands over serial
	https://github.com/scogswell/ArduinoSerialCommand