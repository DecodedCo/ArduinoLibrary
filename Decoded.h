/*
Decoded.cpp Created by Alex Walker 2014
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
    Decoded(HardwareSerial &print, uint8_t failLed);
    
    void addLed(uint8_t pin);
    void ledOn(uint8_t pin);
    void ledOff(uint8_t pin);
    void setLed(uint8_t pin, bool set);
    
    void addButton(uint8_t pin);
    bool isButtonPressed(uint8_t pin);
    /*
    uint8_t readPotentiometer(uint8_t pin, uint8_t min, uint8_t max);
    
    void addServo(uint8_t pin);
    void setServo(uint8_t pin, uint8_t angle);
    */
    void setupInternet();
    void hitTriggerUrl(char url[], char *value, uint8_t count = 0);

    void recoverData();
    void checkStillConnected();

    void addTemperatureAndHumidity(uint8_t pin);
    float getCelsius();
    bool checkCelsius(float tolerance);
    float getFarenheit();
    float getHumidity();

    int readFlameSensor(uint8_t flamePin);
    bool checkFlameSensor(uint8_t flamePin, int tolerance);

    bool checkTouchSensor(uint8_t touchPin, int tolerance);
    int readTouchSensor(uint8_t touchPin);

    int readKnockSensor(uint8_t knockPin);
    bool checkKnockSensor(uint8_t knockPin, int tolerance);
    void addTiltSensor(uint8_t tiltPin);
    bool checkIfTilted(uint8_t tiltPin);

    int readJoyStick(uint8_t x);

    void addRFID(uint8_t pin);
    char *checkForRFID();

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
    bool flameSent;
    bool touchSent;
    DHT *dht;
    // SoftwareSerial *rfid;
};

#endif