#include"DS1302.h"
#include "TM1637.h"
#include "IRremote.h"

//7-segment
unsigned long previousMillis;
const int CLK = 17;
const int DIO = 16;
TM1637 sevenSegment(CLK,DIO);
int8_t Digitos[] = {0,1,2,3};
//Clock
DS1302 rtc(8, 7, 6);
//IRREMOTE
int receiver = 2; 
IRrecv irrecv(receiver);    
decode_results results; 

//STEP MOTOR
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
int step_number = 0;
//Water
int sensorPin = A0;  
int sensorValue = 0; 

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
   sevenSegment.displayStr("On");

pinMode(STEPPER_PIN_1, OUTPUT);
pinMode(STEPPER_PIN_2, OUTPUT);
pinMode(STEPPER_PIN_3, OUTPUT);
pinMode(STEPPER_PIN_4, OUTPUT);
   
   irrecv.enableIRIn(); // Start the receiver
}
Time t;
void loop()
{
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
     /* int8_t Digit0 = t.min %10 ;
      int8_t Digit1 = (t.min % 100) / 10 ;
      int8_t Digit2 = t.hour % 10 ;
      int8_t Digit3 = (t.hour% 100) / 10 ;

      Digitos[3] = Digit0 ;
      Digitos[2] = Digit1 ;
      Digitos[1] = Digit2 ;
      Digitos[0] = Digit3 ;
      sevenSegment.display(Digitos);*/

//Remote
  String newTime = "-----"; 
  for(int i = 0; i<5; i++)
  {
    byte temp;
    if (irrecv.decode(&results)) // have we received an IR signal?
    {
      switch(results.value)
      {
        case 0xFF9867: newTime.setCharAt(i, '0'); temp = 0; break;
        case 0xFFA25D: newTime.setCharAt(i, '1'); temp = 1; break; 
        case 0xFF629D: newTime.setCharAt(i, '2'); temp = 2; break;
        case 0xFFE21D: newTime.setCharAt(i, '3'); temp = 3; break;  
        case 0xFF22DD: newTime.setCharAt(i, '4'); temp = 4; break;  
        case 0xFF02FD: newTime.setCharAt(i, '5'); temp = 5; break; 
        case 0xFFC23D: newTime.setCharAt(i, '6'); temp = 6; break;  
        case 0xFFE01F: newTime.setCharAt(i, '7'); temp = 7; break;
        case 0xFFA857: newTime.setCharAt(i, '8'); temp = 8; break; 
        case 0xFF906F: newTime.setCharAt(i, '9'); temp = 9; break;

      } 
      //กด# --> ตั้งเวลา
      if(results.value == 0xFFB04F)
    {
      sevenSegment.displayStr("Hour");
      delay(1000);
      sevenSegment.stop();
      delay(100);
    }

    
      irrecv.resume(); // receive the next value
    }
    
    if(newTime.charAt(i)=='-'){
      i--;
    }
    //A Time Check can be placed here to see if valid times are being input.
    delay(500);
    //sevenSegment.displayNum(results.value);
    Serial.println(newTime);
  } 


   if (irrecv.decode(&results)) // have we received an IR signal?
  {   
     if(results.value == 0xFFB04F)
    {
      sevenSegment.displayStr("Hour");
      delay(1000);
      sevenSegment.stop();
      delay(100);
      
      int8_t Digit0 = 'code1' ;
      int8_t Digit1 = 'code2' ;
      int8_t Digit2 = 'code3' ;
      int8_t Digit3 = 'code4' ;

      Digitos[3] = Digit0 ;
      Digitos[2] = Digit1 ;
      Digitos[1] = Digit2 ;
      Digitos[0] = Digit3 ;
      sevenSegment.display(Digitos);
    }
    translateIR(); 
    irrecv.resume(); // receive the next value
    if(results.value == 0xFF5AA5)
    {
        sevenSegment.displayStr("----");
        
        
    //water    
        sensorValue = analogRead(sensorPin);    
        delay(1000);          
        Serial.print("sensor = " );                       
       Serial.println(sensorValue);     

       if(sensorValue <= 0)
     {
      sevenSegment.displayStr ("0P");
     }
     else if(sensorValue <= 65)
    {
      sevenSegment.displayStr ("10P");
    }
     else if(sensorValue <= 130)
    {
     sevenSegment.displayStr ("20P");
    }
    else if(sensorValue <= 195)
    {
     sevenSegment.displayStr ("30P");
    }
     else if(sensorValue <= 260)
    {
      sevenSegment.displayStr ("40p");
    }
     else if(sensorValue <= 325)
    {
      sevenSegment.displayStr ("50P");
    }
    else if(sensorValue <= 390)
    {
      sevenSegment.displayStr ("60P");
    }
    else if(sensorValue <= 455)
    {
      sevenSegment.displayStr ("70P");
    }
    else if(sensorValue <= 520)
    {
      sevenSegment.displayStr ("80P");
     }
     else if(sensorValue <= 585)
    {
      sevenSegment.displayStr ("90P");
    }
     else if(sensorValue <= 650)
    {
      sevenSegment.displayStr ("100P");
    }
      delay(500);
     }
  }  
  else if(!irrecv.decode(&results))
  {
      int8_t Digit0 = t.min %10 ;
      int8_t Digit1 = (t.min % 100) / 10 ;
      int8_t Digit2 = t.hour % 10 ;
      int8_t Digit3 = (t.hour% 100) / 10 ;

      Digitos[3] = Digit0 ;
      Digitos[2] = Digit1 ;
      Digitos[1] = Digit2 ;
      Digitos[0] = Digit3 ;
      sevenSegment.display(Digitos);

  }
}


void translateIR() 
{
  switch(results.value)

  {
  case 0xFFA25D: 1;   break;
  case 0xFF629D: 2;   break;
  case 0xFFE21D: 3;   break;
  case 0xFF22DD: 4;   break;
  case 0xFF02FD: 5;   break;
  case 0xFFC23D: 6;   break;
  case 0xFFE01F: 7;   break;
  case 0xFFA857: 8;   break;
  case 0xFF906F: 9;   break;
  case 0xFF9867: Serial.println(" 0");    break;
  case 0xFF6897: Serial.println(" *");    break;
  case 0xFFB04F: Serial.println(" #");    break;
  case 0xFF10EF: Serial.println("Left");    break;
  case 0xFF5AA5: Serial.println("Right");    break;
  case 0xFF18E7: Serial.println("UP");    break;
  case 0xFF4AB5: Serial.println("DOWN");    break;
  case 0xFF38C7: Serial.println("OK");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
   Serial.println(" other button   ");

  }// End Case

delay(500); // Do not get immediate repeat

String code1,code2,code3,code4;
code1 = results.value;
code2 = results.value;
code3 = results.value;
code4 = results.value;
if(t.hour == 'code1'+'code2'&& t.min == 'code3'+'code4')
{
    OneStep(false);
    delay(2);
}

}
void OneStep(bool dir){
    if(dir)
 {
   switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
  }
  else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
 
  
} 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}
