//this is your specific end point.
String url= "|/api/?uid=[YOUR IDENTIFIER]&trigger=t8myh&value=";  
//this is the object that handles all communication with the arduino
Decoded decoded(Serial, computer);

uint8_t buttonPin = 4; //pin that button is connected to

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting up");
  decoded.setupInternet();  
  decoded.addButton(buttonPin);
}

void loop()
{
    if (decoded.isButtonPressed(buttonPin)) {
      Serial.println("btn prssd");
      String checkChar = "ALERT";
      decoded.hitTriggerUrl(url, checkChar);
      delay(250);
    }
  
}
