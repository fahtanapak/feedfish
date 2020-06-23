#include"DS1302.h"
// DS1302 rtc([CE/RST], [I/O], [CLOCK]);
DS1302 rtc(8, 7, 6);
Time t;
void setup() {
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  // Setup Serial connection
  Serial.begin(9600);
 // rtc.setDOW(TUESDAY);        // Set Day-of-Week to WEDNESDAY
  //rtc.setTime(15,8,00);     // Set the time to 12:21:00 (24hr format)
  //rtc.setDate(23, 6, 2020);   // Set the date to January 31th, 2018
  
}
void loop() {
  
  
 t=rtc.getTime(); 
  
  Serial.print("\n");

 if(t.hour<10){Serial.print(0);}

 Serial.print(t.hour,DEC);

 Serial.print(":");

 if(t.min<10){Serial.print(0);}

 Serial.print(t.min,DEC);

 Serial.print(":");

 if(t.sec<10){Serial.print(0);}

 Serial.print(t.sec,DEC);
 
  if((t.hour==12)&&(t.min==25))
 {
  delay(500);
 }
}
