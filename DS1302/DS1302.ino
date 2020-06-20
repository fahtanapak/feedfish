#include "DS1302.h"

long lastTimeStateChange =0;
String state = "on";
// Init the DS1302
// DS1302 rtc([CE/RST], [I/O], [CLOCK]);
DS1302 rtc(8, 7, 6);
Time t;
Time before;
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
long currenTime = millis();
   if(state =="on" && currenTime - lastTimeStateChange >= 1000){
       state ="off";
       lastTimeStateChange = currenTime ;
   }
   else if(state =="off" && currenTime - lastTimeStateChange >= 1000){
       state ="on";
       lastTimeStateChange = currenTime ; 
   }
  //Serial.print(rtc.getDOWStr());
  //Serial.print(" ");
  // Send date
  //Serial.print(rtc.getDateStr());
  //Serial.print(" -- ");
 if (state =="off") 
 {
     Serial.println(rtc.getTimeStr());
 }
  

}
