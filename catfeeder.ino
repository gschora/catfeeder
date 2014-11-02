#include <SerialCommand.h>
#include <Wire.h>
// #include <SPI.h>
#include <RTClib.h>
#include <RTC_DS3231.h>

RTC_DS3231 RTC;
SerialCommand SCmd;

void setup() {
	Serial.begin(57600);

	Wire.begin();
	RTC.begin();
	if (! RTC.isrunning()) {
		Serial.println("RTC is NOT running!");
	}

	// commands
	SCmd.addDefaultHandler(unrecognized);
	SCmd.addCommand("setDate",setDate);
	SCmd.addCommand("getDate",getDate);

}

void loop() {

	SCmd.readSerial();

	// int incomingByte;

	// if (HWSERIAL.available() > 0) {
	// 	incomingByte = HWSERIAL.read();
	// 	Serial.print("rfid received: ");
	// 	Serial.println(incomingByte, DEC);
	// }
}


void setDate(){
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

void getDate(){
	DateTime now = RTC.now();
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

void unrecognized()
{
  Serial.println("command not understood! try something else like");
  Serial.println("setDate");
  Serial.println("getDate"); 
}