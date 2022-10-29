/*  channel ApaITU smartSwitch
 *   web based smartswitch control
 * v0.1
 * 1) basic webbased led switching
 * 2) ArduinoOTA
 * 3) EEPROM stored ssid
 * 4) serial command :
 * on       > ledOn
 * off      > ledOff
 * ota      > endable ota
 * otastop  > disable ota
 * reboot   > reboot
 * ip       > show ip address
 * erase    > erase eeprom
 * wifi     > store ssid/password to eeprom
 * file : 
 * main
 * Serial.ino
 * keys.h
 * ota.ino
 * pernik.ino
 * webserver.ino
 * wifi.ino
 * 
 * 
 * todo :
 * v0.2 
 * 1) wmPortal : if connection failed to stored ssid launch wmPortal
 * 2) dht11 integration
 * 3) ajax : dynamic page 
 * 
 * 
 * 
 */

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
  serverSetup();
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

 



void loop() {
  
  server.handleClient();
  if(otaState == 1)ArduinoOTA.handle();
  serialCMD();    

}





  
