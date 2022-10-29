String command;
void serialCMD(){
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
        else if(command.equals("otastop")){
            otaStop();
        }
        else if(command.equals("reboot")){
            reBoot();
        }
        else if(command.equals("ip")){
            Serial.println(WiFi.localIP());
        }
        else if(command.equals("wifi")){
          serialWifi();
        }
        else if(command.equals("erase")){
            eraseEEPROM();
            ESP.restart();
        }
        else{
            Serial.println("Invalid command");
        }
    }
}


void eraseEEPROM(){
  Serial.println("Erase EEPROM");
  for(int i=0; i<96; i++){
    EEPROM.write(i,0);
  }
  EEPROM.commit();
}

void serialWifi(){
  //erase eeprom
  eraseEEPROM();
  Serial.println("WiFi Configuration over Serial");
  wifiScan();
  Serial.println("Type Network number");
  delay(100);
  while(Serial.available() == 0);
  int n = Serial.parseInt();
  Serial.read();
  String ssidSerial = WiFi.SSID(n);
  Serial.println("Write ssid : " + ssidSerial + " to EEPROM");
    for(int i=0; i<ssidSerial.length(); i++){
    EEPROM.write(i,ssidSerial[i]);
  }
  Serial.println();
  Serial.println("Type password : ");
  delay(100);
  while(Serial.available() ==  0);
  String passSerial = Serial.readStringUntil('\n');
  Serial.println("Write pass : " + passSerial = " to EEPROM");


  for(int i=0; i<passSerial.length(); i++){
    EEPROM.write(32+i,passSerial[i]);
    Serial.print(passSerial[i]);
    delay(10);
  }
  Serial.println();
  EEPROM.commit();
  ESP.restart();
}
