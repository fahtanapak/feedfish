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
String code1,code2,code3,code4;
int Hour =0;
int Min = 0;
void loop()
{
  t=rtc.getTime(); 
 
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
     
      if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }
}   
  
//Remote
 String changetime()
 { delay(500);
  irrecv.resume(); 
  String newTime = "----"; 
  for(int i = 0; i<4; i++)
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
        case 0xFFB04F: Serial.println(" #");    break;
       case 0xFF10EF: Serial.println("Left");    break;
       case 0xFF5AA5: Serial.println("Right");    break;
       case 0xFF38C7: Serial.println("OK");    break;
       case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

      } 
      //กด# --> ตั้งเวลา
      if(results.value == 0xFFB04F||results.value == 0xFF10EF)
    {
      sevenSegment.displayStr("Hour");
      sevenSegment.displayNum(Hour);
    
      delay(1000); 
      sevenSegment.displayStr("Min");
      sevenSegment.displayNum(Min);
      delay(100);
        
    }
    //กดok
    if(results.value ==0xFF38C7 ){
      sevenSegment.displayStr("Sure");
      sevenSegment.display(Digitos);
    }
    //กด> -->water
    if(results.value == 0xFF5AA5)
    {
        sevenSegment.displayStr("----");   
        water();
     }

      irrecv.resume(); // receive the next value
    }
    
    if(newTime.charAt(i)=='-'){
      i--;
    }
    delay(500);
    Serial.println(newTime);
  } 

    return newTime; 
      if(t.hour == Hour&& t.min == Min)
      {
         OneStep(false);
         delay(2);
      }
}

void translateIR() 
{
  switch(results.value)

  {
  
  case 0xFFB04F: Serial.println(" #");  
    String newTime = changetime();
    Hour = (newTime.substring(0,2)).toInt();
    Min = (newTime.substring(2)).toInt();
    int sec = 0;
 break; 

  default: 
    Serial.println("Error" + results.value );
  }
  delay(500);
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


void water(){
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
