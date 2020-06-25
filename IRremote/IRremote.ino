 #include "IRremote.h"

int receiver = 2; 
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup()   
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

}


 void loop()   
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}


void translateIR() 
{
  switch(results.value)

  {
  case 0xFFA25D: Serial.println(" 1");    break;
  case 0xFF629D: Serial.println(" 2"); break;
  case 0xFFE21D: Serial.println(" 3");    break;
  case 0xFF22DD: Serial.println(" 4");    break;
  case 0xFF02FD: Serial.println(" 5");    break;
  case 0xFFC23D: Serial.println(" 6");   break;
  case 0xFFE01F: Serial.println(" 7");    break;
  case 0xFFA857: Serial.println(" 8"); break;
  case 0xFF906F: Serial.println("9");    break;
  case 0xFF6897: Serial.println(" *");    break;
  case 0xFF9867: Serial.println(" 0");    break;
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


}
//ทดสอบรหัส
 /* #include "IRremote.h"

const int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
}
*/ 
