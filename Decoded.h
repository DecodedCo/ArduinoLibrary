/*
Decoded.cpp Created by Alex Walker 2014
*/

#ifndef DECODED_H
#define DECODED_H
#include "Arduino.h"
#include "Servo.h"
// #include "Device.h"
#include <Ethernet.h>
#include <SPI.h>
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
    Decoded();
    void addLed(int pin);
    void ledOn(int pin);
    void ledOff(int pin);
    void setLed(int pin, bool set);

    void addButton(int pin);
    bool isButtonPressed(int pin);

    int readPotentiometer(int pin, int min, int max);
    
    void addServo(int pin);
    void setServo(int pin, int angle);
    
    void setupInternet();
    void hitTriggerUrl(char getRequest[]);
    void recoverData();
    void checkStillConnected();

    void addTemperatureAndHumidity(int pin);
    float getCelsius();
    float getFarenheit();
    float getHumidity();

    void addRFID(int pin);
    char *checkForRFID();

    void setValue(float f);
    void setValue(int d);
    void setValue(char * c);
    // Device addAnalogInput(bool pin);
    // Device addDigitalInput(bool pin);
    // Device addDigitalOutput(bool pin);
    // Device addPWMDevice(bool pin);

    // void addEthernet(){} //ethernet requires pins...

 
  private:
    int successPin;
    int failPin;
    int ledPin;
    int buttonPin;
    int knobPin;
    bool rfidDataExists;
    char *res;
    char *value;
    Servo servo;  // create servo object to control a servo 
    EthernetClient client;
    IPAddress ip;
    bool readyToSend;
    DHT *dht;
    SoftwareSerial *rfid;
};

#endif