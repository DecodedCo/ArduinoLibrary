//this is your specific end point.
  String url= "/api/?uid=[YOUR ID]&trigger=t8myh&value=";  
//this is to identify your computer
  byte computer = 0xAD; //change to your choice...
//this is the object that handles all communication with the arduino
  Decoded decoded(Serial, computer);


void setup()
{
  Serial.begin(9600);
  Serial.println("Starting up");

}

void loop()
{

  delay(250);
}
