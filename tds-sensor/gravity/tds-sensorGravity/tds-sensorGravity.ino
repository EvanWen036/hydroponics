#include <WiFi.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <WebServer.h>

#include "GravityTDS.h"
#define TdsSensorPin 34
#define CONNECTION_TIMEOUT 10
GravityTDS gravityTds;
float temperature = 25;
float tdsValue = 0;
#define RXp2 16
#define TXp2 17
char ssid[] = "DukeVisitor";
WiFiServer server(80);
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial2.begin(9600);
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(3.3);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(4096);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization
  /**
  WiFi.begin(ssid);
  
	Serial.println("Establishing connection to WiFi with SSID: " + String(ssid) ) ;
  int timeout = 0;
	while	(WiFi.status()	!= WL_CONNECTED)    {
    delay(1000) ;
    Serial.println(":) Connecting to WIFI") ;
    timeout++;
    if(timeout >= CONNECTION_TIMEOUT * 5){
      ESP.restart();
    }
  }
    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP IP: ");
    Serial.println(WiFi.localIP()); 

    server.begin();
    **/
}

void loop() {

    // put your main code here, to run repeatedly:
    
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate 
    tdsValue = gravityTds.getTdsValue();  // then get the value
    
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    //Serial.print("pH: ");
    Serial.println(Serial2.readString());
    delay(1000);

    

}
