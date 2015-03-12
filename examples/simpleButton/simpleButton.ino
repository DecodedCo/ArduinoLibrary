//this is your specific end point.
String url= "|/api/?uid=[YOUR IDENTIFIER]&trigger=t8myh&value=";  
//this is to identify your computer
byte computer = 0xAD; //change to your choice...
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
      Serial.println(url);
      Serial.println("button pressed");
      String checkChar = "ALERT";
    }
  delay(250);
}
