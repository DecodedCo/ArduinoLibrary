/*
Decoded.cpp 
Author: Alex Walker
(c) Decoded ltd 2014
*/

#ifndef DECODED_H
#define DECODED_H
#include "Arduino.h"
// #include "Servo.h"
// #include "Device.h"
#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#include <stdio.h>
/*
A simple library to abstract away the low level arduino stuff that we dont want to have to explain to a student...

010A5C924A8F
4B00DD7C6A80

*/


class Decoded
{
  public:
    Decoded(HardwareSerial &print, byte computer);
    
    void addLed(uint8_t pin);
    void ledOn(uint8_t pin);
    void ledOff(uint8_t pin);
    void setLed(uint8_t pin, bool set);
    
    void addButton(uint8_t pin);
    bool isButtonPressed(uint8_t pin);
    bool checkPotentiometer(uint8_t pin, int tolerance);
    /*
    void addServo(uint8_t pin);
    void setServo(uint8_t pin, uint8_t angle);
    */
    void setupInternet();
    void hitTriggerUrl(String url, String value, uint8_t count = 0);

    void recoverData();
    void checkStillConnected();

    void addTemperatureAndHumidity(uint8_t pin);
    float getCelsius();
    bool checkCelsius(float tolerance);
    float getFarenheit();
    float getHumidity();
    bool checkHumidity(float tolerance);

    int readSoundSensor(uint8_t soundPin);
    bool checkSoundSensor(uint8_t soundPin, int tolerance);

    bool checkTouchSensor(uint8_t touchPin, int tolerance);
    int readTouchSensor(uint8_t touchPin);

    int readKnockSensor(uint8_t knockPin);
    bool checkKnockSensor(uint8_t knockPin, int tolerance);
    void addTiltSensor(uint8_t tiltPin);
    bool checkIfTilted(uint8_t tiltPin);

    bool readJoyStick(uint8_t x, int tolerance);

    void addRFID(uint8_t pin);
    String checkForRFID();

    char *setValue(float f);
    void setValue(uint8_t d);
    void setValue(char * c);
    
    // Device addAnalogInput(bool pin);
    // Device addDigitalInput(bool pin);
    // Device addDigitalOutput(bool pin);
    // Device addPWMDevice(bool pin);

    // void addEthernet(){} //ethernet requires pins...

 
  private:
    HardwareSerial* printer;
    // int successPin;
    int failPin;
    // int ledPin;
    // int buttonPin;
    // int knobPin;
    // bool rfidDataExists;
    // char *res;
    
    // Servo servo;  // create servo object to control a servo 
    // EthernetClient client;
    // IPAddress ip;
    // bool readyToSend;
    bool temperatureSent;
    bool joySent;
    bool humiditySent;
    bool soundSent;
    bool touchSent;
    bool potSent;
    DHT *dht;
    // SoftwareSerial *rfid;
};

#endif