

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


void serverSetup(){
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
}

void indexhtml(){
  Serial.println("root / directory panggil");
  //server.send(200,"text/plain","ApaITU Oyeee!!!");
  server.send(200,"text/html",indexPageContent());
}

void ledOn(){
  ledState=1;
  digitalWrite(LED_BUILTIN,LOW);
  Serial.println("ledOn");
  //server.send(200,"text/plain","ledOn");
  server.send(200,"text/html",indexPageContent());
}

void ledOff(){
  ledState=0;
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("ledOff");
  //server.send(200,"text/plain","ledOff");
  server.send(200,"text/html",indexPageContent());
}
