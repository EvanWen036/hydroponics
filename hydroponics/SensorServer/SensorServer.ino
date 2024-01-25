#include <WiFi.h>
#include "aWOT.h"
#include "StaticFiles.h"
#include "WebServer.h"
#include <GravityTDS.h>
#define WIFI_SSID "iPhone (163)"
#define WIFI_PASSWORD "3dx8ahepxxzu2"

Application app;
#define TdsSensorPin 34

GravityTDS gravityTds;
float temperature = 25;
double pH = 0.0;
float tdsValue = 0;
WiFiServer server(80);

void readPH(Request &req, Response &res){
  res.set("Access-Control-Allow-Origin", "*"); // Allow requests from any origin

  res.print(pH);
}
void readTDS(Request &req, Response &res){
  res.set("Access-Control-Allow-Origin", "*"); // Allow requests from any origin

  res.print(tdsValue);
}
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(3.3);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(4096);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  app.get("/tds", &readTDS);
  app.get("/ph", &readPH);
  app.use(staticFiles());
  //server.enableCORS(true); //This is the magic

  server.begin();

}

void loop() {
  WiFiClient client = server.available();

  gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
  gravityTds.update();  //sample and calculate 
  tdsValue = gravityTds.getTdsValue();  // then get the value
    
  Serial.print(tdsValue,0);
  Serial.println("ppm");
  Serial.print("pH: ");
  pH = Serial2.readString().toDouble();
  Serial.println(pH);
  Serial.print("Status: ");
  Serial.println(Serial2.available());
  if(Serial2.available()){
    Serial.print("it works");
  }
  Serial.println(WiFi.localIP());
  delay(1000);

  if (client.connected()) {
    app.process(&client);
  }
}