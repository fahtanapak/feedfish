#include "DS1302.h"


// Init the DS1302
// DS1302 rtc([CE/RST], [I/O], [CLOCK]);
DS1302 rtc(8, 7, 6);

void clockdate() 

{

       

       

}
 
void setup()

{

  Serial.begin(9600);

  // ตั้งเวลาครั้งแรก เอา comment นี้ออก ถ้าตั้งเสร็จแล้ว comment นี้ไว้เพื้อให้เวลาเดินต่อ

  rtc.halt(false);

  rtc.writeProtect(false);

  rtc.setDOW(SATUARDAY);         

  rtc.setTime(16, 36,00);      

  rtc.setDate(13, 6, 2020);    

  rtc.writeProtect(true);
  }

 

void loop()

{ 

  clockdate();

  delay(1000);

}