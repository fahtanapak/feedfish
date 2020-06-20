#include "DS1302.h"


// Init the DS1302
// DS1302 rtc([CE/RST], [I/O], [CLOCK]);
DS1302 rtc( 7, 6,5);
Time t;

void setup()

{

  

  rtc.halt(false);
  rtc.writeProtect(false);
  // Setup Serial connection
  Serial.begin(9600);
  int hour,min,sec;
 // rtc.setDOW(SATURDAY);        
  rtc.setTime(16,10 ,20 );     
 // rtc.setDate(13, 6, 2020);   
 
  }

 
int ti;
void loop()

{ 

   
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  RTC.read(tm)

}
