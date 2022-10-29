#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//lib ota
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>

#include "keys.h"

int ledState;
char* ledToggle[] = {"OFF", "ON"};

int otaState;



ESP8266WebServer server(80);

String indexPageContent(){
  String indexPage ="<html>";
         indexPage += "<body><center>";
         indexPage += "<h1>ApaITU-LAMPU Loteng</h1>";
         indexPage += "<a href=\"/on\">[ledOn]</a> ";
         indexPage += "<a href=\"/off\">[ledOff]</a> ";
         indexPage += "<a href=\"/otaE\">[Start OTA]</a> ";
         indexPage += "<a href=\"/otaD\">[Stop OTA]</a>";
         indexPage += "<a href=\"/reboot\">[reboot]</a>";
         indexPage += "<br>LedState : " + String(ledToggle[ledState]);
         indexPage += "<br>OtaState : " + startStop(otaState);
         indexPage += "</center></body>";        
         indexPage += "</html>"; 
         return indexPage;
}

String startStop(int status){
  String x;
  if(status==0){
    x="Stopped";
  }else{
    x="Started";
  }
  return x;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.begin(115200);
  dashLine(60);
  Serial.println("Serial Monitor");
  dashLine(60);
  delay(1000);
  WiFi.disconnect();
  EEPROM.begin(512); //Initializing EEPROM
  wifiSetup();

  // webserver
  server.on("/",indexhtml);
  server.on("/on",ledOn);
  server.on("/off",ledOff);
  server.on("/otaE",otaStart);
  server.on("/otaD",otaStop);
  server.on("/reboot",reBoot);
  server.begin();
  dashLine(60);
  Serial.println(WiFi.localIP());
  Serial.print("http://");  Serial.print(WiFi.localIP()); Serial.println("/on");
  Serial.print("http://");  Serial.print(WiFi.localIP()); Serial.println("/off");
  Serial.print("http://");  Serial.print(WiFi.localIP()); Serial.println("/otaE");
  Serial.print("http://");  Serial.print(WiFi.localIP()); Serial.println("/otaD");
  Serial.print("http://");  Serial.print(WiFi.localIP()); Serial.println("/reboot");
  dashLine(60);
  
  //oTA
 // otaSetup();
  

}

void reBoot(){
  Serial.print("rebooting  the System : ");
  for(int i=0; i<100; i++){
      Serial.println(".");
      delay(50);
  }
  Serial.println("NOW");
  ESP.restart();
}
void otaStart(){
  otaState=1;
  otaSetup();
  Serial.println("OTA Started!!!");
  server.send(200,"text/html",indexPageContent());
}

void otaStop(){
  otaState=0;
  ArduinoOTA.end();
  Serial.println("OTA Stopped!!!");
  server.send(200,"text/html",indexPageContent());
  reBoot();
}
void indexhtml(){
  Serial.println("root / directory panggil");
  //server.send(200,"text/plain","ApaITU Oyeee!!!");
  server.send(200,"text/html",indexPageContent());
}

String command;
void loop() {
  
  server.handleClient();
  if(otaState == 1)ArduinoOTA.handle();
      if(Serial.available()){
        command = Serial.readStringUntil('\n');
         
        if(command.equals("on")){
            ledOn();
        }
        else if(command.equals("off")){
            ledOff();
        }
        else if(command.equals("ota")){
            otaStart();
        }
        else if(command.equals("otaoff")){
            otaStop();
        }
        else if(command.equals("reboot")){
            reBoot();
        }
        else if(command.equals("ip")){
            Serial.println(WiFi.localIP());
        }
        else{
            Serial.println("Invalid command");
        }
    }

}
