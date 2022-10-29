void wifiSetup(){

  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostName);
  WiFi.begin(ssid,password);
  Serial.println("");
  testWifi();

}

bool testWifi(void)
{
  int c = 0;
  Serial.println("Waiting for WiFi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP Addess  : ");
      Serial.println(WiFi.localIP());
      Serial.print("hostname : ");
      Serial.println(WiFi.hostname());
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connection timed out, opening AP or Hotspot");
  return false;
}
