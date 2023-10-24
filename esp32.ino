#include <WiFi.h>
#include <WebServer.h>
//SSID and password of Wifi connection:
const char* ssid = “TYPE_YOUR_SSID_HERE”;
const char* password = “TYPE_YOUR_PASSWORD_HERE”;

WebServer server(80);

webpage = “<HTML>.sdkifslj\
lskdjlksdj\
</HTML>”

webpage = webpage_1 + String(random(100)) + webpage_2;

int interval   1000;
Unsigned long previousMillis = 0;

void setup( )	(
Serial.begin(115200);
	WiFi.begin(ssid, password);
	Serial.printIn(“Establishing connection to WiFi with SSID: “ + String(ssid) ) ;

	while	(WiFi.status()	!=WL_CONNECTED)    (
delay(1000) ;
Serial.print(“.”) ;
	)
Serial.print(“Connected to network with IP address: “) ;
Serial.println(WiFi.localIP( ) ) ;


Server.on (“/”,  [ ] ( )	(
	server.send(200,  “text\hetml”, webpage) ;
      )
)

void loop( )	(
server.handleClient( ) ; 
unsigned long now = millis( ) ;
if(now - previousMillis > interval)	(
		webpage = webpage_1 + String(random(100)) + webpage_2;
)
		previousMillis = now;
<
