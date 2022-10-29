
ESP8266WebServer wmPortal(80);

void wifiSetup(){
  String essid ="";
  String epass =""; 
  //read ssid from EEPROM

  for(int i=0; i<32; i++){
    essid += char(EEPROM.read(i));
    epass += char(EEPROM.read(32+i));
  }
  Serial.println("essid : " + essid);
  Serial.println("epass : " + epass);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostName);
  WiFi.begin(essid.c_str(),epass.c_str());
  //WiFi.begin(ssid,password);
  Serial.println("");
  if(testWiFi()){
    return;
  }else{
    Serial.println("starting wmPortal");
    //starting AccessPoint
    setupAP();
    //Starting wmPortal
    initwmPortal();
    
    
  }

  
/*
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  */

}

void wifiScan(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  if(n == 0){
    Serial.println("No WiFi Network Available");
  }else{
    for(int i=0; i<n; i++){
      Serial.print(String(i) + " : ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(") ");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
}
void setupAP(){
  //scan SSID network
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  if(n == 0){
    Serial.println("No WiFi Network Available");
  }else{
    for(int i=0; i<n; i++){
      Serial.print(String(i) + " : ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(") ");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
}

void initwmPortal(){
  
}

bool testWiFi(){
  int c=0;
  while(c<20){
    if(WiFi.status() == WL_CONNECTED){
      ipPrint();
      return true;
    } else {
      delay(500);
      Serial.print(".");
      c++;  
    }
  }
  Serial.println("connection  timeout");
  return false;
}

void ipPrint(){
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP Addess  : ");
  Serial.println(WiFi.localIP());
  Serial.print("hostname : ");
  Serial.println(WiFi.hostname());
}
