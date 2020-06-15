#include "DS1302.h"


// Init the DS1302
// DS1302 rtc([CE/RST], [I/O], [CLOCK]);
DS1302 rtc(8, 7, 6);
Time t;

void setup()

{

  

  rtc.halt(false);
  rtc.writeProtect(false);
  // Setup Serial connection
  Serial.begin(9600);
  
 // rtc.setDOW(SATURDAY);        
 // rtc.setTime(17, 50,30 );     
  //rtc.setDate(13, 6, 2020);   
  
  }

 

void loop()

{ 

Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  // Send time
  Serial.println(rtc.getTimeStr());
  // Wait one second before repeating :)
  delay (1000);

 

}

  