#include <SerialCommand.h>
#include <Wire.h>
#include <RTClib.h>
#include <RTC_DS3231.h>
#include <SeeedRFIDLib.h>
#include <Servo.h>


RTC_DS3231 RTC;
SeeedRFIDLib RFID(0, 0);
RFIDTag tag;
SerialCommand SCmd;
Servo feedServo;

void setup() {
	Serial.begin(57600);

	Wire.begin();
	RTC.begin();
	if (! RTC.isrunning()) {
		Serial.println("RTC is NOT running!");
	}

	feedServo.attach(20);

	// commands
	SCmd.addDefaultHandler(unrecognized);
	SCmd.addCommand("setDate", cmdSetDate);
	SCmd.addCommand("getDate",cmdGetDate);
	SCmd.addCommand("moveServo", cmdMoveServo);

}

void loop() {

	SCmd.readSerial();

	if(RFID.isIdAvailable()) {
	    tag = RFID.readId();
	    Serial.print("ID:       ");
	    Serial.println(tag.id);
	  }
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

void unrecognized()
{
  Serial.println("command not understood! try something else like");
  Serial.println("setDate");
  Serial.println("getDate"); 
}