

#include "Decoded.h"
#define DHTTYPE DHT11 

/* Decoded library for controlling external peripherals for TiaD */
Decoded::Decoded(){
	readyToSend = false;
	res = new char[13];
	successPin = 8;
	failPin = 9;
	pinMode(successPin, OUTPUT);
	pinMode(failPin, OUTPUT);
	digitalWrite(successPin, LOW);
	digitalWrite(failPin, LOW);
	value = "";
}
void Decoded::addLed(int pin){
	 pinMode(pin, OUTPUT);
	 Serial.println(F("led setup"));
}
void Decoded::ledOn(int pin){
	digitalWrite(ledPin, HIGH);
}
void Decoded::ledOff(int pin){
	digitalWrite(ledPin, LOW);
}
void Decoded::setLed(int pin, bool set){
	digitalWrite(ledPin, set);
}
void Decoded::addButton(int pin) {
	pinMode(pin, INPUT);
	Serial.println(F("button setup"));
}
void Decoded::addServo(int pin){
	servo.attach(pin);  
	Serial.println(F("Servo setup"));
}
void Decoded::setServo(int pin, int angle){
	servo.write(angle);
}
void Decoded::addTemperatureAndHumidity(int pin) {
	dht = new DHT(pin, DHTTYPE);
	dht->begin();
}
float Decoded::getCelsius(){
	return dht->readTemperature();
}
float Decoded::getFarenheit(){
	return dht->readTemperature(true);
}
float Decoded::getHumidity(){
	dht->readHumidity();
}
int Decoded::readPotentiometer(int pin, int min, int max) { //return a value between 0 and 180 (servo angles)
  return map(analogRead(knobPin), 0, 1023, min, max); 
}
bool Decoded::isButtonPressed(int pin){ //is it boolean or bool???
	
	return (digitalRead(buttonPin) == HIGH) ? true : false;
}
void Decoded::addRFID(int pin) {
	rfid = new SoftwareSerial(pin, 4);
	rfid->begin(9600);
}
char *Decoded::checkForRFID(){
		int8_t len = 0;
		rfidDataExists = false;
		while(rfid->available()) {
			res[len++] = rfid->read();
			  res[len] = '\0';
			  rfidDataExists = true;
		}	
		if (rfidDataExists) { //send internet request
			rfidDataExists = false;
			// Serial.println(res);
			return res;

		}
		return NULL;
}
void Decoded::setupInternet(){
	Serial.println("Configuring internet");

	byte tempMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
	if (Ethernet.begin(tempMac) == 0) {
		Serial.println("Failed to configure Ethernet using DHCP");
		for (int i = 0; i < 6; i++) {
			digitalWrite(failPin, HIGH);
			delay(100);
			digitalWrite(failPin, LOW);
			delay(100);
		}
	} else {
		Serial.println("Internet configured!");
		for (int i = 0; i < 6; i++) {
			digitalWrite(successPin, HIGH);
			delay(100);
			digitalWrite(successPin, LOW);
			delay(100);
		}
	}
	delay(1000); //give the ethernet a second to sort itself out....
}

void Decoded::hitTriggerUrl(char getRequest[]){
		char url[] = "futuretech.decoded.com";
		Serial.print("connecting to "); Serial.println(url);
		
			if (client.connect(url, 80)) {
				Serial.println("Connected to the network!");
				readyToSend = true;
			} else {
				Serial.println("connection failed...");
				digitalWrite(failPin, HIGH);
				delay(800);
				digitalWrite(failPin, LOW);
			}
		if (readyToSend) {
			// client.print("GET ");
			client.println(getRequest);
	    	// client.print(10.1);
	    	// client.println(" HTTP/1.1");
	    	client.print("Host: ");
	    	client.println(url);
	    	client.println("Connection: close");
	    	client.println(); //HTTP requests must end in a blank line
	    	Serial.println("Connection made successfully");
	    	
	    	digitalWrite(successPin, HIGH);
			delay(800);
			digitalWrite(successPin, LOW);
	 		checkStillConnected();
	 		readyToSend = false;
		} else {
			Serial.println("you are not connected to the domain");
			hitTriggerUrl(getRequest);
			digitalWrite(failPin, HIGH);
			delay(800);
			digitalWrite(failPin, LOW);
		}
}
void Decoded::recoverData() {
	while (client.available()) {
		char c = client.read();
		Serial.print(c);
	}
}

void Decoded::checkStillConnected() {
	if (!client.connected()) {
		client.stop();
	}
}
void Decoded::setValue(float f) {
	sprintf(value, "%f", f);
}
void Decoded::setValue(int d) {
	sprintf(value, "%d", d);
}
void Decoded::setValue(char * c) {
	value = c;
}
// Device Decoded::addAnalogInput(bool pin){
// 	Device d(pin, Input, Analog);
// 	return d;
// }
// Device Decoded::addDigitalInput(bool pin){
// 	Device d(pin, Input, Digital);
// 	return d;

// }
// void Decoded::addDigitalOutput(bool pin){
// 	Device d(pin, Output, Digital);
// 	return d;
// }
// void Decoded::addPWMDevice(bool pin){
// 	Device d(pin, Output, Analog);
// 	return d;
// }