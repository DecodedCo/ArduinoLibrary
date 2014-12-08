

#include "Decoded.h"
#define DHTTYPE DHT11 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAF };
String server = "futuretech.decoded.com";
// IPAddress server(54,217,228,120);
IPAddress ip(172,16,0,177);
EthernetClient client;
SoftwareSerial *rfid;
String value;
/* Decoded library for controlling external peripherals for TiaD */
Decoded::Decoded(HardwareSerial &print, uint8_t failLed) : failPin(failLed) {
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
int Decoded::readFlameSensor(uint8_t flamePin) {
	return analogRead(flamePin);
}
bool Decoded::checkFlameSensor(uint8_t flamePin, int tolerance) {
	if (analogRead(flamePin) < tolerance) {
		flameSent = false;
	}
	if (flameSent) {
		return false;
	}
	if (analogRead(flamePin) > tolerance) {
		printer->println("flame TRUE");
		flameSent = true;
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
int Decoded::readJoyStick(uint8_t x) {
	return analogRead(x);
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
float Decoded::getFarenheit(){
	return dht->readTemperature(true);
}
float Decoded::getHumidity(){
	dht->readHumidity();
}
/*
int Decoded::readPotentiometer(int pin, int min, int max) { //return a value between 0 and 180 (servo angles)
  return map(analogRead(knobPin), 0, 1023, min, max); 
}
*/

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
			//printer->print(rfid->read()); // send character to serial monitor
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
    Ethernet.begin(mac, ip);
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
	printer->print("string: ");
	Serial.println(serverPointer);
	
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
    printer->println("finished...");
    
  } 
  else {
    printer->println("connection failed");
    hitTriggerUrl(url, value, ++count);

  }
  if (!client.connected()) {
		client.stop();
	}

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