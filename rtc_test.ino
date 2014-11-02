// // Date and time functions using a DS1307 RTC connected via I2C and Wire lib
// #include <Wire.h>
// #include <SPI.h>
// #include <RTClib.h>
// #include <RTC_DS3231.h>
// RTC_DS3231 RTC;
// void setup () {
// 	Serial.begin(57600);
// 	Wire.begin();
// 	RTC.begin();
// 	if (! RTC.isrunning()) {
// 		Serial.println("RTC is NOT running!");
// // following line sets the RTC to the date & time this sketch was compiled
// RTC.adjust(DateTime(__DATE__, __TIME__));
// }
// }
// void loop () {

// 	if(Comp("setDate")==0){
// 		setDate();
// 	}


// 	DateTime now = RTC.now();
// 	Serial.print(now.year(), DEC);
// 	Serial.print('/');
// 	Serial.print(now.month(), DEC);
// 	Serial.print('/');
// 	Serial.print(now.day(), DEC);
// 	Serial.print(' ');
// 	Serial.print(now.hour(), DEC);
// 	Serial.print(':');
// 	Serial.print(now.minute(), DEC);
// 	Serial.print(':');
// 	Serial.print(now.second(), DEC);
// 	Serial.println();
// 	Serial.println(RTC.getTempAsFloat());
// 	Serial.println(RTC.getTempAsWord());
// 	delay(3000);
// }

// void setDate(){
// //	RTC.adjust(DateTime(2014,10,24,0,16,0));
// }

// char inData[20]; // Allocate some space for the string
// char inChar=-1; // Where to store the character read
// byte index = 0; // Index into array; where to store the character

// char Comp(char* This) {
//     while (Serial.available() > 0) // Don't read unless
//                                    // there you know there is data
//                                    {
//         if(index < 19) // One less than the size of the array
//         {
//             inChar = Serial.read(); // Read a character
//             inData[index] = inChar; // Store it
//             index++; // Increment where to write next
//             inData[index] = '\0'; // Null terminate the string
//         }
//     }

//     if (strcmp(inData,This)  == 0) {
//     	for (int i=0;i<19;i++) {
//     		inData[i]=0;
//     	}
//     	index=0;
//     	return(0);
//     }
//     else {
//     	return(1);
//     }
// }


