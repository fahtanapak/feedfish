 #include"DS1302.h"
 #include "TM1637.h"
#define POINT_ON 1

const int CLK = 17;
const int DIO = 16;
TM1637 sevenSegment(CLK,DIO);
int8_t Digitos[] = {0,1,2,3};

DS1302 rtc(8, 7, 6);
 

void setup() {
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  Serial.begin(9600);
 // rtc.setDOW(TUESDAY);
  //rtc.setTime(15,8,00);    
  //rtc.setDate(23, 6, 2020);  
   sevenSegment.init();
   sevenSegment.set(7);
   sevenSegment.displayStr("v1");

}
Time t;
void loop() {
  
  
 t=rtc.getTime(); 
 //Serial.monitor 
Serial.print("\n");

if(t.hour<10){Serial.print(0);}

 Serial.print(t.hour,DEC);

 Serial.print(":");

 if(t.min<10){Serial.print(0);}

 Serial.print(t.min,DEC);

 Serial.print(":");

 if(t.sec<10){Serial.print(0);}

 Serial.print(t.sec,DEC);

 // Dot blink
  sevenSegment.point(POINT_ON); //Like blink example.
  delay(500);
  sevenSegment.point(POINT_ON); //Like blink example.
  delay(500);

//เวลาบน7-segment
      int8_t Digit0 = t.min %10 ;
      int8_t Digit1 = (t.min % 100) / 10 ;
      int8_t Digit2 = t.hour % 10 ;
      int8_t Digit3 = (t.hour% 100) / 10 ;

      Digitos[3] = Digit0 ;
      Digitos[2] = Digit1 ;
      Digitos[1] = Digit2 ;
      Digitos[0] = Digit3 ;
      sevenSegment.display(Digitos);
//ตั้งเวลา
if((t.hour==12)&&(t.min==25))
 {
   sevenSegment.display(Digitos);
 }
   
}