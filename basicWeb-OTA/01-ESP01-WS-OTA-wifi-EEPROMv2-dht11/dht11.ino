#include <DHT.h>
DHT dht(0, DHT11);

float Temperature;
float Humidity;

void dhtSetup(){
  dht.begin();
}

String getDHT() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  String  s ="<p>";
          s+="Temperature : " + String(Temperature) + " C";
          s+="</p>";
          s+="<p>";
          s+="Humidity : " + String(Humidity) + " %";
          s+="</p>";
  return s;
}
