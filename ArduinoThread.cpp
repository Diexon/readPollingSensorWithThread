#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>

// ThreadController that will controll all threads
ThreadController threadControl = ThreadController();

//His Thread (not pointer)
Thread cardThread = Thread();

// Some globals
String sensorName;


void sensorReader(String& sensorNameIn){
	int randNum = -1;
		while (randNum != 25){
			randNum = random(0,50);
			delay(1);
		}
	sensorNameIn = String("The sensor is: ") + String(randNum);
	return;
}

// callback for cardThread
void sensorCallback(){
	sensorReader(sensorName);

}

void setup(){
	Serial.begin(115200);

	// Configure waiting thread
	cardThread.onRun(sensorCallback);
	cardThread.setInterval(50);

	threadControl.add(&cardThread); // & to pass the pointer to it
}

void loop(){

	sensorName = "";

	threadControl.run();

	// Doing other Tibo's crazyness with read sensor
	Serial.println("Crazy Stuff!");
	if (sensorName == ""){
		Serial.println("No sensor present");
	}
	else{
		Serial.print("Sensor read this time!! ");
	}
	Serial.println(sensorName);
	delay(10);
}
