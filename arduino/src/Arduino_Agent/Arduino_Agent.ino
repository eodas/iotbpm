/********************
  - Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)
  - Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM
  - Arduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using Arduino Tron AI-IoTBPM Processing
  - Executive Order Corporation
  - Copyright (c) 1978, 2021: Executive Order Corporation, All Rights Reserved
********************/

#include <ESP8266WiFi.h>

#define LED0 D0 // NodeMCU pin GPIO16 (D0)
#define LED1 D1 // NodeMCU pin GPIO5 (D1)
#define LED2 D2 // NodeMCU pin GPIO4 (D2)
#define LED3 D3 // NodeMCU pin GPIO0 (D3)
#define LED4 D4 // NodeMCU pin GPIO2 (D4-onboard)
#define LED5 D5 // NodeMCU pin GPIO14 (D5)
#define LED6 D6 // NodeMCU pin GPIO12 (D6)
#define LED7 D7 // NodeMCU pin GPIO13 (D7)
#define LED8 D8 // NodeMCU pin GPIO15 (D8)
#define LED9 D9 // NodeMCU pin GPIO3 (D9-RXD0)
#define LED10 D10 // NodeMCU pin GPIO1 (D10-TXD0)

// Update these with WiFi network values
const char* ssid     = "your-ssid"; //  your network SSID (name)
const char* password = "your-password"; // your network password

WiFiClient client;
WiFiServer server(80);

String ver = "1.03E";
int loopCounter = 1; // loop counter

void setup() {
  pinMode(LED0, OUTPUT); // LED pin as output
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  digitalWrite(LED0, LOW); // turn the LED off
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  // Arduino IDE Serial Monitor window to see what EOSPY code is doing
  Serial.begin(115200); // Serial connection from ESP-01 via 3.3v console cable

  // Connect to WiFi network
  Serial.println("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)");
  Serial.println("Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM");
  Serial.println("- Arduino Tron Agent ver " + ver);
  Serial.println("Copyright (c) 1978, 2021: Executive Order Corporation, All Rights Reserved");

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the arduino tron agent
  server.begin();
  Serial.println("Arduino Tron Agent started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // Check if a client has connected
  client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.print("new client connection, loop ");
  Serial.println(loopCounter);
  loopCounter++;

  while (!client.available()) {
    delay(1);
  }
  arduinoWebserver();
}

void arduinoWebserver()
{
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Set ledPin according to the request digitalWrite(ledPin, value);
  int value0 = LOW;
  if (request.indexOf("/LED0=ON") != -1)  {
    digitalWrite(LED0, HIGH);
    value0 = HIGH;
  }
  if (request.indexOf("/LED0=OFF") != -1)  {
    digitalWrite(LED0, LOW);
    value0 = LOW;
  }

  // Set ledPin according to the request digitalWrite(ledPin, value);
  int value1 = LOW;
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(LED1, HIGH);
    value1 = HIGH;
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(LED1, LOW);
    value1 = LOW;
  }

  // Set ledPin according to the request digitalWrite(ledPin, value);
  int value2 = LOW;
  if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(LED2, HIGH);
    value2 = HIGH;
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(LED2, LOW);
    value2 = LOW;
  }

  // Set ledPin according to the request digitalWrite(ledPin, value);
  int value3 = LOW;
  if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(LED3, HIGH);
    value3 = HIGH;
  }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(LED3, LOW);
    value3 = LOW;
  }

  // Set ledPin according to the request digitalWrite(ledPin, value);
  int value4 = LOW;
  if (request.indexOf("/LED4=ON") != -1)  {
    digitalWrite(LED4, HIGH);
    value4 = HIGH;
  }
  if (request.indexOf("/LED4=OFF") != -1)  {
    digitalWrite(LED4, LOW);
    value4 = LOW;
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one

  client.println("<!DOCTYPE HTML>");
  client.println("<html><title>Arduino Tron Agent</title>");
  client.println("<h3>Arduino Tron Agent MQTT AI-IoTBPM :: Internet of Things Drools-jBPM</h3>");
  client.print("LED PIN-1 is now: ");
  if (value1 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED0=ON\"\"><button>Turn LED-0 On </button></a>");
  client.println("<a href=\"/LED0=OFF\"\"><button>Turn LED-0 Off </button></a><br>");
  client.println("<a href=\"/LED1=ON\"\"><button>Turn LED-1 On </button></a>");
  client.println("<a href=\"/LED1=OFF\"\"><button>Turn LED-1 Off </button></a><br>");
  client.println("<a href=\"/LED2=ON\"\"><button>Turn LED-2 On </button></a>");
  client.println("<a href=\"/LED2=OFF\"\"><button>Turn LED-2 Off </button></a><br>");
  client.println("<a href=\"/LED3=ON\"\"><button>Turn LED-3 On </button></a>");
  client.println("<a href=\"/LED3=OFF\"\"><button>Turn LED-3 Off </button></a><br>");
  client.println("<a href=\"/LED4=ON\"\"><button>Turn LED-4 On </button></a>");
  client.println("<a href=\"/LED4=OFF\"\"><button>Turn LED-4 Off </button></a><br>");
  client.println("<img src=""http://www.iotbpm.com/wp-content/uploads/2018/05/Arduino_Logotype-763x354.jpg"" alt=""Arduino Tron"">");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
