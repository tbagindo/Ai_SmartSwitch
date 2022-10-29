#include <WiFiManager.h>

void wifiSetup(){
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  /*
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostName);
  WiFi.begin(ssid,password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  */
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP Addess  : ");
  Serial.println(WiFi.localIP());
  Serial.print("hostname : ");
  Serial.println(WiFi.hostname());
}
