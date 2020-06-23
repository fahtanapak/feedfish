#include "TM1637.h"

const int CLK = 17;
const int DIO = 16;

TM1637 sevenSegment(CLK,DIO);

void setup()
{
    sevenSegment.init();
    sevenSegment.set(7);//bright0-7
    
     //const int DIGITS = 4;
    sevenSegment.displayNum(5);
    sevenSegment.displayStr("v1");
    delay(2000);
   

}
int number = 0;
void loop()
{
    sevenSegment.displayNum(number++);
    delay(100);

}