int sensorPin = A0;    // select the input pin for the Soil moisture sensor
int sensorValue = 0;  // variable to store the value coming from the sensor
 
void setup() {
  // declare the ledPin as an OUTPUT:
   Serial.begin(9600);  
}
 
void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  delay(1000);          
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);     

  if(sensorValue <= 0)
  {
    Serial.println("0%");
   
  }
  else if(sensorValue <= 65)
  {
    Serial.println("10%");
  }
  else if(sensorValue <= 130)
  {
    Serial.println("20%");
  }
  else if(sensorValue <= 195)
  {
    Serial.println("30%");
  }
  else if(sensorValue <= 260)
  {
    Serial.println("40%");
  }
  else if(sensorValue <= 325)
  {
    Serial.println("50%");
  }
  else if(sensorValue <= 390)
  {
    Serial.println("60%");
  }
   else if(sensorValue <= 455)
  {
    Serial.println("70%");
  }
  else if(sensorValue <= 520)
  {
    Serial.println("80%");
  }
  else if(sensorValue <= 585)
  {
    Serial.println("90%");
    delay(500);
  }
  else if(sensorValue <= 650)
  {
    Serial.println("100% ");
  }
  delay(500);
}
