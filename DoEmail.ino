#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <math.h>

#include <AccelStepper.h>

#include "contents.h"



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

const int MAXSPEED = 100;  // in steps/sec
const int MAXACCEL = 8;  // in steps/sec²

int positions[5] = {0,0,0,0,0}; // originally long

float proporcao[5] = {1,1,1,1,1};

 
// Replace with your network credentials
const char* ssid = "cpti";
const char* password = "3domingos";
ESP8266WebServer server(4212);   //instantiate server at port 80 (http port)


AccelStepper stepper1(AccelStepper::DRIVER, STEP_X, DIR_X);
AccelStepper stepper2(AccelStepper::DRIVER, STEP_Y, DIR_Y);
AccelStepper stepper3(AccelStepper::DRIVER, STEP_Z, DIR_Z);
AccelStepper stepper4(AccelStepper::DRIVER, STEP_A, DIR_A);
AccelStepper stepper5(AccelStepper::DRIVER, STEP_C, DIR_C);


 
 //////////////////////////////////
 
//String page = "";
String text = "";
double data;
Servo myservo;
int pos = 0;


void prepareMove(){
	//int maiorDistancia = max(positions);//for some reason arduino does not accept that max()
	int maiorDistancia = 0;
	for (int i = 0; i<5; i++){
		if(maiorDistancia<positions[i]){
			maiorDistancia = positions[i];
		}
	}

	
	for(int i = 0; i< 5; i++){
		proporcao[i] = (float)(positions[i]/maiorDistancia);
	}

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


	for(int i = 0; i< 5; i++){
		positions[i] = 0;
	}
}

 
void setup(void){
	Serial.begin(115200);
	WiFi.begin(ssid, password); //begin WiFi connection
	Serial.println("");
	
	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	
	
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	server.on("/data.txt", [](){
	text = (String)pos;
	server.send(200, "text/html", text);
	});
	server.on("/data_update.js", [](){
	server.send(200, "text/html", data_update_js_str);
	});
	server.on("/", [](){
	server.send(200,"text/html", index_html_str);
	});
	server.begin();
	Serial.println("Web server started!");
}
 
void loop(void){
	server.handleClient();
}
