
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include "index.h"

//variable
int spState=0; // 0 webserver, 1 wifimanager
String page = FPSTR(MAIN_PAGE);
float t;
float h;
int dhtPin = 0;

//constructor
WiFiManager wm;
ESP8266WebServer server(80);
DHT dht(dhtPin, DHT22);


void setup() {
  WiFi.setOutputPower(5);                                                                                                                                                                                                                                                              
  Serial.begin(115200);

  //wm.setSTAStaticIPConfig(IPAddress(192,168,1,222), IPAddress(192,168,1,1), IPAddress(255,255,255,0),IPAddress(192,168,1,1));
  //start wm portal ssid :
  
  wm.autoConnect("ApaITU-SmartSwitch");
  

  Serial.println("connected ...");
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  pinMode(dhtPin,INPUT);
  dht.begin();
  
  //webserver  request handler
  server.on("/", indexHTML);
  server.on("/on", ledOn);
  server.on("/off", ledOff);
  server.on("/Temp",getTemp);
  server.on("/Humid",getHumid);
  server.on("/wifiPortal", startPortal);
  server.on("/reset",[](){wm.resetSettings();Serial.println("Reboot...");for(int i=0;i<20; i++){Serial.print("*"); delay(10);ESP.restart();}});
  server.on("/reboot", [](){Serial.println("Reboot...");for(int i=0;i<20; i++){Serial.print("*"); delay(10);ESP.restart();}});
  
  //start webserver
  server.begin();
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
  
}
void getTemp(){
  float tempT = dht.readTemperature();
  if (isnan(tempT)) {
      Serial.println("Failed to read from DHT sensor!");
      t=1000.0;
  }
  else {
      t = tempT;
      Serial.println(t);
  }
  String s =  String(t);
  server.send(200,"text/plain",s);
}

void getHumid(){
  float tempH = dht.readHumidity();
  if (isnan(tempH)) {
      Serial.println("Failed to read from DHT sensor!");
  }
  else {
      h= tempH;
      Serial.println(h);
  }
  String s =  String(h);
  server.send(200,"text/plain",s);
}

void indexHTML(){
  server.send(200,"text/html",page);
}

void ledOn(){
  digitalWrite(2,LOW);
  server.send(200,"text/html","ON");
}

void ledOff(){
  digitalWrite(2,HIGH);
  server.send(200,"text/html","OFF");
}

void startPortal(){
  Serial.println("Stop webserver ");
  server.stop();
  Serial.println("Start wmPortal");
  wm.startWebPortal();
  spState =1;
}

void loop() {
  if(spState == 0){
    server.handleClient();
  } else {
    wm.process();
  }

}
