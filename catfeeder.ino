#include <SerialCommand.h>
#include <Wire.h>
#include <RTClib.h>
#include <RTC_DS3231.h>
#include <SeeedRFIDLib.h>
#include <Servo.h>
#include "Adafruit_FRAM_I2C.h"


RTC_DS3231 RTC;
SeeedRFIDLib RFID(0, 0);
RFIDTag tag;
SerialCommand SCmd;
Servo feedServo;
Adafruit_FRAM_I2C fram  = Adafruit_FRAM_I2C();

void setup() {
	Serial.begin(57600);

	Wire.begin();
	RTC.begin();
	if (! RTC.isrunning()) {
		Serial.println("RTC is NOT running!");
	}

	feedServo.attach(20);

	fram.begin();

	// commands
	SCmd.addDefaultHandler(unrecognized);
	SCmd.addCommand("getConfig", cmdGetConfig);
	SCmd.addCommand("setDate", cmdSetDate);
	SCmd.addCommand("getDate",cmdGetDate);
	SCmd.addCommand("moveServo", cmdMoveServo);
	SCmd.addCommand("setServoOpenDeg", cmdSetServoOpenDeg);
	SCmd.addCommand("setServoCloseDeg", cmdSetServoCloseDeg);
	SCmd.addCommand("setServoKeepOpenTime", cmdSetServoKeepOpenTime);
	SCmd.addCommand("openCloseServo", cmdOpenCloseServo);

}

void loop() {

	SCmd.readSerial();

	if(RFID.isIdAvailable()) {
	    tag = RFID.readId();
	    Serial.print("ID:       ");
	    Serial.println(tag.id);
	  }
}

/*
	commands in fram
addr 	val
0		servo max open degrees
1 		servo min close degrees

 */
void cmdGetConfig(){
	Serial.print("ServoOpenDeg: ");
	Serial.print(fram.read8(0),DEC);
	Serial.println("");
	Serial.print("ServoCloseDeg: ");
	Serial.print(fram.read8(1),DEC);
	Serial.println("");
	Serial.print("setServoKeepOpenTime: ");
	Serial.print(fram.read8(2),DEC);
	Serial.println("");
}

void cmdSetDate(){
	int dd;
	int MM;
	int yyyy;
	int hh;
	int mm;
	int ss;

	char *arg;

	arg = SCmd.next();
	if (arg != NULL) {
    	dd=atoi(arg);    // Converts a char string to an integer
    					// day
	} 
	else {
		Serial.println("Format is: dd MM yyyy hh mm ss");
		return;
	}

	arg = SCmd.next();
	if (arg != NULL) {
    	MM=atoi(arg);    // month
	} 
	else {
		Serial.println("Format is: dd MM yyyy hh mm ss");
		return; 
	}

	arg = SCmd.next();
	if (arg != NULL) {
    	yyyy=atoi(arg);    // year ACHTUNG in SerialComman.h die SERIALCOMMANDBUFFER auf 30 erhöhen!!!!
	} 
	else {
		Serial.println("Format is: dd MM yyyy hh mm ss"); 
		return;
	}

	arg = SCmd.next();
	if (arg != NULL) {
    	hh=atoi(arg);    // hour
	} 
	else {
		Serial.println("Format is: dd MM yyyy hh mm ss"); 
		return;
	}

	arg = SCmd.next();
	if (arg != NULL) {
    	mm=atoi(arg);    // minutes
	} 
	else {
		Serial.println("Format is: dd MM yyyy hh mm ss"); 
		return;
	}

	arg = SCmd.next();
	if (arg != NULL) {
    	ss=atoi(arg);    // seconds
	} 
	else {
		Serial.println("Format is: dd MM yyyy hh mm ss"); 
		return;
	}

	if (! RTC.isrunning()) {
		Serial.println("RTC is NOT running!");
	} else {
		Serial.println("setting time and date: ");
		Serial.print(dd);
		Serial.print(".");
		Serial.print(MM);
		Serial.print(".");
		Serial.print(yyyy);
		Serial.print(" ");
		Serial.print(hh);
		Serial.print(":");
		Serial.print(mm);
		Serial.print(":");
		Serial.print(ss);
		Serial.println("");

		RTC.adjust(DateTime(yyyy,MM,dd,hh,mm,ss));

		getDate();
	}
}

void cmdGetDate(){
	DateTime now = getDate();
	Serial.print(now.day());
	Serial.print(".");
	Serial.print(now.month());
	Serial.print(".");
	Serial.print(now.year());
	Serial.print(" ");
	Serial.print(now.hour());
	Serial.print(":");
	Serial.print(now.minute());
	Serial.print(":");
	Serial.print(now.second());
	Serial.println("");
}

DateTime getDate(){
	return RTC.now();
}

// Serialcommand for moving servo
void cmdMoveServo(){
	char *arg = SCmd.next();
	if (arg != NULL) {
		uint8_t pos = atoi(arg);
		moveServo(pos);
	} 
	else {
		Serial.println("please give degrees from 0 to 180 for moving servo"); 
		return;
	}
	
}

void moveServo(uint8_t pos){
	if (pos >=0 && pos<= 180){
    		feedServo.write(pos);
    } else {
		Serial.println("please give degrees from 0 to 180 for moving servo"); 
		return;
	}
}

void cmdSetServoOpenDeg(){
	char *arg = SCmd.next();
	if (arg != NULL) {
		uint8_t pos = atoi(arg);
		if (pos >=0 && pos<= 180){
    		fram.write8(0, pos);
    		cmdGetConfig();
    	} else {
			Serial.println("please give degrees from 0 to 180 for open servo"); 
			return;
		}
	} 
	else {
		Serial.println("please give degrees from 0 to 180 for open servo"); 
		return;
	}
}
void cmdSetServoCloseDeg(){
	char *arg = SCmd.next();
	if (arg != NULL) {
		uint8_t pos = atoi(arg);
		if (pos >=0 && pos<= 180){
    		fram.write8(1, pos);
    		cmdGetConfig();
    	} else {
			Serial.println("please give degrees from 0 to 180 for close servo"); 
			return;
		}
	} 
	else {
		Serial.println("please give degrees from 0 to 180 for close servo"); 
		return;
	}
}

void cmdSetServoKeepOpenTime(){
	char *arg = SCmd.next();
	if (arg != NULL) {
		uint8_t t = atoi(arg);
		fram.write8(2, t);
		cmdGetConfig();
	} 
	else {
		Serial.println("please the time in 100 millis the door should stay open"); 
		return;
	}
}

void cmdOpenCloseServo(){
	moveServo(fram.read8(0));

	delay(fram.read8(2)*100);

	moveServo(fram.read8(1));
}

void unrecognized()
{
  Serial.println("command not understood!");
	Serial.println("available commands:");
	Serial.println("getConfig");
	Serial.println("setDate");
	Serial.println("getDate");
	Serial.println("moveServo");
	Serial.println("setServoOpenDeg");
	Serial.println("setServoCloseDeg");
	Serial.println("setServoKeepOpenTime");
	Serial.println("openCloseServo");
	Serial.println("---------------------------------------"); 
}