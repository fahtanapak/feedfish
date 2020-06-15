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

  if(sensorValue <= 400)
  {
    Serial.println("0%");
    delay(200);
  }
   
  else if(sensorValue <= 550)
  {
    Serial.println("50%");
  }
  else if(sensorValue <= 625)
  {
    Serial.println("75%");
  }
  else if(sensorValue <= 700)
  {
    Serial.println("100% ");
  }
  
}