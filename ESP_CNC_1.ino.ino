#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <AccelStepper.h>

#include "contents.h"

/*  ////////wemos d1

const int STEP_X = 16; //0
const int DIR_X = 5; //1
const int STEP_Y = 4; //2
const int DIR_Y = 0; //3
const int STEP_Z = 2; //4
const int DIR_Z = 14; //5

const int STEP_A = 13; //7
const int DIR_A = 15; //8
const int STEP_C = 3; //rx
const int DIR_C = 1; //tx


const int EN   = 12 ; // 6

*/ //node mcu 1.0


const int EN   = 16; //0 

const int STEP_X = 5 ; //1
const int DIR_X = 4; //2
const int STEP_Y = 0; //3
const int DIR_Y = 2; //4
const int STEP_Z = 14; //5
const int DIR_Z = 12; //6
const int STEP_A = 13; //7
const int DIR_A = 15; //8
const int STEP_C = 3;  //rx

const int DIR_C = 1; //tx

const int TRIG = 10; //s3

const int MAXSPEED = 700;  // in steps/sec
const int MAXACCEL =50;  // in steps/sec²


// Replace with your network credentials
const char* ssid = "cpti";
const char* password = "3domingos";
ESP8266WebServer server(2223);   //instantiate server at port 80 (http port) //2222 for wemos //


AccelStepper stepper1(AccelStepper::DRIVER, STEP_X, DIR_X);
AccelStepper stepper2(AccelStepper::DRIVER, STEP_Y, DIR_Y);
AccelStepper stepper3(AccelStepper::DRIVER, STEP_Z, DIR_Z);
AccelStepper stepper4(AccelStepper::DRIVER, STEP_A, DIR_A);
AccelStepper stepper5(AccelStepper::DRIVER, STEP_C, DIR_C);


void prepareMove(int positions[5]){
	float proporcao[5] = {1,1,1,1,1};
/*	int maiorDistancia = 0;
	for (int i = 0; i<5; i++){
		if(maiorDistancia<positions[i]){
			maiorDistancia = positions[i];
		}
	}
	
	for(int i = 0; i< 5; i++){
		proporcao[i] = (float)(positions[i]/maiorDistancia);
	} */

	stepper1.setMaxSpeed((int)(proporcao[0]*MAXSPEED));
	stepper2.setMaxSpeed((int)(proporcao[1]*MAXSPEED));
	stepper3.setMaxSpeed((int)(proporcao[2]*MAXSPEED));
	stepper4.setMaxSpeed((int)(proporcao[3]*MAXSPEED));
	stepper5.setMaxSpeed((int)(proporcao[4]*MAXSPEED));
	
	stepper1.setAcceleration(proporcao[0]*MAXACCEL);
	stepper2.setAcceleration(proporcao[1]*MAXACCEL);
	stepper3.setAcceleration(proporcao[2]*MAXACCEL);
	stepper4.setAcceleration(proporcao[3]*MAXACCEL);
	stepper5.setAcceleration(proporcao[4]*MAXACCEL);
	
	digitalWrite(EN,HIGH);
	
	stepper1.move(positions[0]);
	stepper2.move(positions[1]);
	stepper3.move(positions[2]);
	stepper4.move(positions[3]);
	stepper5.move(positions[4]);


}

 
void setup(void){
	Serial.begin(115200);
	WiFi.begin(ssid, password); //begin WiFi connection
	Serial.println("trying to connect");
	
	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	pinMode(TRIG,OUTPUT);
	digitalWrite(TRIG,LOW);

	stepper1.setMaxSpeed(MAXSPEED);
	stepper1.setAcceleration(MAXACCEL);
	stepper2.setMaxSpeed(MAXSPEED);
	stepper2.setAcceleration(MAXACCEL);
	stepper3.setMaxSpeed(MAXSPEED);
	stepper3.setAcceleration(MAXACCEL);
	stepper4.setMaxSpeed(MAXSPEED);
	stepper4.setAcceleration(MAXACCEL);
	stepper5.setMaxSpeed(MAXSPEED);
	stepper5.setAcceleration(MAXACCEL);
	
	
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	
	stepper1.setMaxSpeed(20);
	server.on("/data_update.js", [](){
		server.send(200, "text/html", data_update_js_str);
	});
	server.on("/", [](){
		server.send(200,"text/html", index_html_str);
	});

	
	server.on("/move_test", [](){
		int positions[5] = {10000,1000,100,100,100};
		//stepper1.move(100);
		prepareMove(positions);
		
		//Serial.println("preraring moves");		
		server.send(200,"text/html","ok");
	});
	
	server.on("/move", [](){
		int positions[5];
		for(int i = 0; i < server.args(); i++){
   			positions[i] = server.arg(i).toInt();
   			Serial.println(positions[i]);
		}
		prepareMove(positions);
  		server.send(200, "text/html", "ok");
  				
 	});

	server.on("/trig", [](){
		digitalWrite(TRIG,HIGH);
		delayMicroseconds(100);
		delay(500);
		digitalWrite(TRIG,LOW);
		server.send(200, "text/html", "ok");
  				
 	});
	
	server.begin();
	Serial.println("Web server started!");
}
 
void loop(void){

	server.handleClient();
	
	stepper1.run();	
	stepper2.run();	
	stepper3.run();	
	stepper4.run();	
	stepper5.run();	

	
}
