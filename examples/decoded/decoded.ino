#include <DHT.h> //temperature and humidity library
#include <Decoded.h> //Our library
#include <Servo.h> //Servo motor library
#include <Ethernet.h> //internet library
#include <SPI.h> //communication library
#include <SoftwareSerial.h>
Decoded decoded;

int ledPin = 13;
int buttonPin = 4;
int potPin = 0;
int servoPin = 11;
int humTempPin = 2;
int RFIDPin = 3;

char domain[] = "futuretech.decoded.com"; 
char getRequest[] = "GET /api/?uid=65ece577b258d898a0ea7f3039569e40&trigger=1 HTTP/1.1";
void setup()
{
  Serial.begin(9600);
  decoded.addLed(ledPin);
  decoded.addButton(buttonPin);
  decoded.addServo(servoPin);
  decoded.addTemperatureAndHumidity(humTempPin);
  decoded.addRFID(3);
  decoded.setupInternet();  
  

}

void loop()
{
//  if (decoded.isButtonPressed(buttonPin)) {
//    decoded.ledOn(ledPin);
//    delay(300);
//    decoded.ledOff(ledPin);
//    delay(100);
//  }
//  Serial.print("Celsius ");
//  Serial.println(decoded.getCelsius());
//  Serial.print("Fahrenheit ");
//  Serial.println(decoded.getFarenheit());
//  Serial.print("Humidity ");
//  Serial.println(decoded.getHumidity());
//  int potValue = decoded.readPotentiometer(potPin, 0, 179);
//  decoded.setServo(servoPin, potValue);
  
  decoded.checkForRFID(domain, getRequest);
  delay(250);

}