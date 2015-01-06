/*
Decoded.cpp 
Author: Alex Walker
(c) Decoded ltd 2014
*/

#include "Decoded.h"
#define DHTTYPE DHT11 

byte mac[6];

String server = "futuretech.decoded.com";
// IPAddress server(54,217,228,120);
//IPAddress ip(172,16,0,random(50, 200));
EthernetClient client;
SoftwareSerial *rfid;
String value;
/* Decoded library for controlling external peripherals for TiaD */
Decoded::Decoded(HardwareSerial &print, byte computer) : failPin(7) {
	mac[0] = 0xDE;
	mac[1] = 0xAD;
	mac[2] = 0xBE;
	mac[3] = 0xEF;
	mac[4] = 0xFE;
	mac[5] = computer;
	// readyToSend = false;
	// res = new char[13];
	// successPin = 8;
	// failPin = 9;
	// pinMode(successPin, OUTPUT);
	// pinMode(failPin, OUTPUT);
	// digitalWrite(successPin, LOW);
	// digitalWrite(failPin, LOW);
	// value = "";
	printer = &print; //operate on the adress of print
	temperatureSent = false;

    joySent = false;
    humiditySent = false;
    soundSent = false;
    touchSent = false;
    potSent = false;
     // printer->begin(9600);
}

void Decoded::addLed(uint8_t pin){
	 pinMode(pin, OUTPUT);
	 printer->println(F("led setup"));
}
void Decoded::ledOn(uint8_t pin){
	digitalWrite(pin, HIGH);
}
void Decoded::ledOff(uint8_t pin){
	digitalWrite(pin, LOW);
}
void Decoded::setLed(uint8_t pin, bool set){
	digitalWrite(pin, set);
}
/*
void Decoded::addServo(int pin){
	servo.attach(pin);  
	Serial.println(F("Servo setup"));
}
void Decoded::setServo(int pin, int angle){
	servo.write(angle);
}
*/
void Decoded::addButton(uint8_t pin) {
	pinMode(pin, INPUT);
	printer->println(F("button setup"));
}
bool Decoded::isButtonPressed(uint8_t pin){ //is it boolean or bool???
	
	return (digitalRead(pin) == HIGH) ? true : false;
}
int Decoded::readSoundSensor(uint8_t soundPin) {
	return analogRead(soundPin);
}
bool Decoded::checkSoundSensor(uint8_t soundPin, int tolerance) {
	if (analogRead(soundPin) < tolerance) {
		soundSent = false;
	}
	if (soundSent) {
		return false;
	}
	if (analogRead(soundSent) > tolerance) {
		printer->println("sound TRUE");
		soundSent = true;
		return true;
	}
	return false;
}
int Decoded::readTouchSensor(uint8_t touchPin) {
	return analogRead(touchPin);
}
bool Decoded::checkTouchSensor(uint8_t touchPin, int tolerance) {
	if (analogRead(touchPin) > tolerance) {
		touchSent = false;
	}
	if (touchSent) {
		return false;
	}
	if (analogRead(touchPin) < tolerance) {
		printer->println("touch TRUE");
		touchSent = true;
		return true;
	}
	return false;
}
int Decoded::readKnockSensor(uint8_t knockPin) {
	return analogRead(knockPin);
}
bool Decoded::checkKnockSensor(uint8_t knockPin, int tolerance) {
	if (analogRead(knockPin) > tolerance) {
		touchSent = false;
	}
	if (touchSent) {
		return false;
	}
	if (analogRead(knockPin) < tolerance) {
		printer->println("touch TRUE");
		touchSent = true;
		return true;
	}
	return false;
}

void Decoded::addTiltSensor(uint8_t tiltPin) {
	pinMode(tiltPin, INPUT);
}
bool Decoded::checkIfTilted(uint8_t tiltPin) {
	if (digitalRead(tiltPin) == HIGH) {
		return true;
	}
	return false;
}
bool Decoded::readJoyStick(uint8_t x, int tolerance) {
	if (analogRead(x) < tolerance) {
		joySent = false;
	}
	if (joySent) {
		return false;
	}
	if (analogRead(x) > tolerance) {
		joySent = true;
		printer->println("joy check TRUE");
		return true;
	}
	return false;
}
void Decoded::addTemperatureAndHumidity(uint8_t pin) {
	dht = new DHT(pin, DHTTYPE);
	dht->begin();
}
float Decoded::getCelsius(){
	return dht->readTemperature();
}
bool Decoded::checkCelsius(float tolerance) {
	if (dht->readTemperature() < tolerance) {
		temperatureSent = false;
	}
	if (temperatureSent) {
		return false;
	}
	if (dht->readTemperature() > tolerance) {
		temperatureSent = true;
		printer->println("temperature check TRUE");
		return true;
	}
	return false;

}
bool Decoded::checkHumidity(float tolerance) {
	if (dht->readHumidity() < tolerance) {
		humiditySent = false;
	}
	if (humiditySent) {
		return false;
	}
	if (dht->readHumidity() > tolerance) {
		humiditySent = true;
		printer->println("temperature check TRUE");
		return true;
	}
	return false;

}
float Decoded::getFarenheit(){
	return dht->readTemperature(true);
}
float Decoded::getHumidity(){
	dht->readHumidity();
}

bool Decoded::checkPotentiometer(uint8_t pin, int tolerance) { //return a value between 0 and 180 (servo angles)
  if (analogRead(pin) < tolerance) {
		potSent = false;
	}
	if (potSent) {
		return false;
	}
	if (analogRead(pin) > tolerance) {
		potSent = true;
		printer->println("pot check TRUE");
		return true;
	}
	return false; 
}


void Decoded::addRFID(uint8_t pin){
	rfid = new SoftwareSerial(pin, 100);
	rfid->begin(9600);
	printer->println("RFID configured");
}

String Decoded::checkForRFID(){

		int8_t len = 0;
		 // char res[13];
		String res;
		//rfidDataExists = false;
		bool found = false;
		while(rfid->available()) {
			// printer->print(rfid->read()); // send character to serial monitor
			found = true;
			 res += rfid->read();
			  //rfidDataExists = true;
		}	
		//printer->println();
		// if (rfidDataExists) { //send internet request
		// 	rfidDataExists = false;
		// 	return true;
		// }

		return res;
}

  void Decoded::setupInternet(){
  if (Ethernet.begin(mac) == 0) {
    printer->println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
   // Ethernet.begin(mac, ip);
    // setupInternet();
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  printer->println("connected to internet");
}

void Decoded::hitTriggerUrl(String url, String value, uint8_t count){
	
	String s = "GET " + url + value + " HTTP/1.1";
	
	
	char serverPointer[23];
    server.toCharArray(serverPointer, sizeof(serverPointer));
    char urlPointer[s.length()+1];
    s.toCharArray(urlPointer, sizeof(urlPointer));

	if (count > 5) {
		count = 0;
		ledOn(failPin);
	    delay(1000);
	    ledOff(failPin);
		return;
	}
	printer->println("Attempting connection");
	
		// if you get a connection, report back via serial:
  if (client.connect(serverPointer, 80)) {
    printer->println("connected");
    // Make a HTTP request:
    // printer->print("URL: ");
    // printer->println(urlPointer);
    client.println(urlPointer);
    client.println("Host: "+server);
    client.println("Connection: close");
    client.println();
    delay(500);
    printer->println("finished...");
    
  } 
  else {
    printer->println("connection failed");
    hitTriggerUrl(url, value, ++count);

  }
		client.stop();

}
void Decoded::recoverData() {
	printer->println("recovering...");
	while (client.available()) {
		char c = client.read();
		printer->print(c);
	}
}

void Decoded::checkStillConnected() {
	if (!client.connected()) {
		client.stop();
	}
}
// char *Decoded::setValue(float f) {
// 	value = new char[20];
// 	sprintf(value, "%f", f);
// 	return value;
// }
// void Decoded::setValue(int d) {
// 	sprintf(value, "%d", d);
// }
// void Decoded::setValue(char * c) {
// 	value = c;
// }
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