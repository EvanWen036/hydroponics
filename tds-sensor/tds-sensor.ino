#include <WiFi.h>
#include <WebServer.h>

#define CONNECTION_TIMEOUT 10
#define TdsSensorPin 27
#define VREF 3.3      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point
int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0, copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;

char ssid[] = "DukeVisitor";
char pass[] = ""; 
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  
  pinMode(TdsSensorPin, INPUT);
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

void loop()
{

  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint > 40U)  //every 40 milliseconds,read the analog value from the ADC
  {
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
    Serial.println(analogBuffer[analogBufferIndex]);
    analogBufferIndex++;
    if (analogBufferIndex == SCOUNT)
      analogBufferIndex = 0;
  }
  static unsigned long printTimepoint = millis();
  if (millis() - printTimepoint > 800U)
  {
    printTimepoint = millis();
    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    float compensationVolatge = averageVoltage / compensationCoefficient; //temperature compensation
    tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; //convert voltage value to tds value
    Serial.print("voltage:");
    Serial.print(averageVoltage,2);
    Serial.print("V   ");
    Serial.print("TDS----Value:");
    Serial.print(tdsValue, 0);
    Serial.println("ppm");
  } 
/**
WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected");
    while (client.connected()) {
      if (client.available()) {
        // Respond to the client's request with HTTP headers
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();

        // Send your HTML content here
        client.println("<!DOCTYPE html>");

        client.println("<html><body>");
        client.println("<h1>ESP32 Web Server</h1>");
        client.println("<p>TDS Value: ppm</p>");
        client.println("</body></html>");


      }

  }
    client.stop();
    }
  **/
}
int getMedianNum(int bArray[], int iFilterLen)
{
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++)
  {
    for (i = 0; i < iFilterLen - j - 1; i++)
    {
      if (bTab[i] > bTab[i + 1])
      {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}