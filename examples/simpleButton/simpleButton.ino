#include <DHT.h> //temperature and humidity library
#include <Decoded.h> //Our library
#include <Servo.h> //Servo motor library
#include <Ethernet.h> //internet library
#include <SPI.h> //communication library
#include <SoftwareSerial.h>

//this is your specific end point.
String url= "/api/?uid=8a7827b9813f7a054484109a28905793&trigger=t8myh&value=";  
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
      Serial.println("btn prssd");
      String checkChar = "ALERT";
      decoded.hitTriggerUrl(url, checkChar);
    }
  delay(250);
}