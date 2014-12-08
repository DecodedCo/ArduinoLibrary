#include <DHT.h> //temperature and humidity library
#include <Decoded.h> //Our library
#include <Servo.h> //Servo motor library
#include <Ethernet.h> //internet library
#include <SPI.h> //communication library
#include <SoftwareSerial.h>
uint8_t failLed = 6;
Decoded decoded(Serial, failLed);
String url= "/api/?uid=8a7827b9813f7a054484109a28905793&trigger=t8myh&value=";   
uint8_t buttonPin = 4;
uint8_t ledPin = 5;
uint8_t rfidPin = 3;
uint8_t tempPin = 2;
uint8_t flamePin = A0; //analog
uint8_t touchPin = A0;
uint8_t tiltPin = 7;
uint8_t knockPin = A0; //not working

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting up");
  decoded.setupInternet();	
//  decoded.addTiltSensor(tiltPin);
//  	decoded.setupInternet();
//    decoded.addRFID(rfidPin);
//    decoded.hitTriggerUrl(url, "");
  decoded.addButton(buttonPin);
//  decoded.addLed(5);
//  decoded.hitTriggerUrl(url);
//  decoded.recoverData();
//  decoded.addTemperatureAndHumidity(tempPin);

}

/*
Notes:
 - check Celsius works. fix other temp *things*
 - cant currently send a value
 - cant currently have dynamic urls.
*/
void loop()
{
//  Serial.println(decoded.checkForRFID());
//    if(decoded.checkCelsius(24.0)) {
//      if(decoded.checkTouchSensor(touchPin, 500)){
//      if(decoded.checkIfTilted(tiltPin)) {
    if (decoded.isButtonPressed(buttonPin)) {
//    String checkChar = decoded.checkForRFID();
//    if (checkChar.length() != 0) {
//      Serial.print("RFID: ");
//        Serial.println(checkChar);
        Serial.println("btn prssd");
        String checkChar = "ALERT";

      decoded.hitTriggerUrl(url, checkChar);
//      decoded.recoverData();
    }

  delay(250);

}