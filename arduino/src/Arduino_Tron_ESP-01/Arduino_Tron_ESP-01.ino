/********************
  - Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)
  - Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM
  - Arduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using Arduino Tron AI-IoTBPM Processing
  - Executive Order Corporation
  - Copyright © 1978, 2018: Executive Order Corporation, All Rights Reserved
********************/

// Load WiFi library
#include <ESP8266WiFi.h>

// | RX     VCC
// A GPIO0  RST
// N GPIO2  CH_PD
// T GRD    TX

// TB:IoT-MCU ESP-01S-Relay-v1.0 send digitalWrite(RELAY) to GPIO0
#define LED0 0 //GPIO0 (SPI_CS2)
#define LED1 1 //GPIO1 on board LED ESP-01 (U0TXD) 
#define LED2 2 //GPIO2 on board LED ESP-01S 
#define LED3 3 //GPIO3 (U0RXD)

#define BUTTON0 0 // NodeMCU pin GPIO16 (D0)
#define BUTTON1 1 // NodeMCU pin GPIO5 (D1)
#define BUTTON2 2 // NodeMCU pin GPIO4 (D2)
#define BUTTON3 3 // NodeMCU pin GPIO0 (D3)

// Update these with WiFi network credentials
const char* ssid     = "your-ssid"; //  your network SSID (name)
const char* password = "your-password"; // your network password

WiFiClient client;

// Update these with Arduino Tron service IP address and unique unit id values
byte server[] = { 10, 0, 0, 2 }; // Set EOSpy server IP address as bytes
String id = "100111"; // Arduino Tron Device unique unit id

// Update these with Arduino Tron Agent_ESP-01 IP address
byte agent[] = { 10, 0, 0, 2 }; // Set Arduino Tron Agent_ESP-01 IP address as bytes
const int httpAgent = 80; // Arduino Tron Agent_ESP-01 Server is running on default port 80

// Update these with your LAT/LON GPS position values
// You can find LAT/LON from an address https://www.latlong.net/convert-address-to-lat-long.html
String address = "National_Air_Space_Museum_600_Independence_Ave_Washington_DC_20560";
String lat = "38.888160"; // position LAT National Air Space Museum
String lon = "-77.019868"; // position LON

// Above are all the fields you need to provide values, the remaining fields are used in the Arduino Tron application
const bool initConsole = true; // Values for display of console information
const bool sendArduino = true; // Values for send AI-IoTBPM Drools-jBPM post

const int httpPort = 5055; // Arduino Tron server is running on default port 5055
// OpenStreetMap Automated Navigation Directions is a map and navigation app for Android default port 5055

// Values ?id=334455&timestamp=1521212240&lat=38.888160&lon=-77.019868&speed=0.0&bearing=0.0&altitude=0.0&accuracy=0.0&batt=98.7
// String timestamp = "1521212240"; // timestamp
// String speeds = "0.0";
// String bearing = "0.0";
// String altitude = "0.0";
// String accuracy = "0.0"; // position accuracy
// String batt = "89.7"; // battery value
// String light = "53.4"; // photocell value

// Arduino Tron currently supports these additional data fields in the Server Event data model:

// id=6&event=allEvents&protocol=osmand&servertime=<date>&timestamp=<date>&fixtime=<date>&outdated=false&valid=true
// &lat=38.85&lon=-84.35&altitude=27.0&speed=0.0&course=0.0&address=<street address>&accuracy=0.0&network=null
// &batteryLevel=78.3&textMessage=Message_Sent&temp=71.2&ir_temp=0.0&humidity=0.0&mbar=79.9
// &accel_x=-0.01&accel_y=-0.07&accel_z=9.79&gyro_x=0.0&gyro_y=-0.0&gyro_z=-0.0&magnet_x=-0.01&magnet_y=-0.07&magnet_z=9.81
// &light=91.0&keypress=0.0&alarm=Temperature&distance=1.6&totalDistance=3.79&motion=false

// You can add more additional fields to the data model and transmit via any device to the Arduino Tron Drools-jBPM processing

// Values for the DHT11 digital temperature/humidity sensor; &temp= and &humidity= fields
// String temp = "0.0";
// String humidity = "0.0";

// Values to send in &textMessage= filed
String textMessage = "text_message";

// Values to send in &keypress= field
const String TYPE_ALLEVENTS = "allEvents"; // allEvents
const String TYPE_KEYPRESS_1 = "1.0"; // keypress_1
const String TYPE_KEYPRESS_2 = "2.0"; // keypress_2
const String TYPE_REED_RELAY = "4.0"; // reedRelay
const String TYPE_PROXIMITY = "8.0"; // proximity

// Values to send in &alarm= field
String alarm = "general";

// Values to send in &alarm= field
const String ALARM_GENERAL = "general";
const String ALARM_SOS = "sos";
const String ALARM_VIBRATION = "vibration";
const String ALARM_MOVEMENT = "movement";
const String ALARM_LOW_SPEED = "lowspeed";
const String ALARM_OVERSPEED = "overspeed";
const String ALARM_FALL_DOWN = "fallDown";
const String ALARM_LOW_POWER = "lowPower";
const String ALARM_LOW_BATTERY = "lowBattery";
const String ALARM_FAULT = "fault";
const String ALARM_POWER_OFF = "powerOff";
const String ALARM_POWER_ON = "powerOn";
const String ALARM_DOOR = "door";
const String ALARM_GEOFENCE = "geofence";
const String ALARM_GEOFENCE_ENTER = "geofenceEnter";
const String ALARM_GEOFENCE_EXIT = "geofenceExit";
const String ALARM_GPS_ANTENNA_CUT = "gpsAntennaCut";
const String ALARM_ACCIDENT = "accident";
const String ALARM_TOW = "tow";
const String ALARM_ACCELERATION = "hardAcceleration";
const String ALARM_BRAKING = "hardBraking";
const String ALARM_CORNERING = "hardCornering";
const String ALARM_FATIGUE_DRIVING = "fatigueDriving";
const String ALARM_POWER_CUT = "powerCut";
const String ALARM_POWER_RESTORED = "powerRestored";
const String ALARM_JAMMING = "jamming";
const String ALARM_TEMPERATURE = "temperature";
const String ALARM_PARKING = "parking";
const String ALARM_SHOCK = "shock";
const String ALARM_BONNET = "bonnet";
const String ALARM_FOOT_BRAKE = "footBrake";
const String ALARM_OIL_LEAK = "oilLeak";
const String ALARM_TAMPERING = "tampering";
const String ALARM_REMOVING = "removing";

String ver = "1.03E";
int loopCounter = 1; // loop counter
int clientAvail = 0; // client.available() count
int switchState = 10; // value to send Arduino Tron Agent_ESP-01

String irkey = "1.0";

// Set response jBPM Global Variable List
// kcontext.getKnowledgeRuntime().setGlobal("response", "");
String response = "";
String agentCount = "";

// Required for LIGHT_SLEEP_T delay mode
extern "C" {
#include "user_interface.h"
}

void initConsoleMessage(void) {
  Serial.println("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)");
  Serial.println("Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM");
  Serial.println("- Arduino Tron_ESP-01 ver " + ver);
  Serial.println("Copyright © 1978, 2018: Executive Order Corporation, All Rights Reserved");
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
}

void setup(void) {
  //pinMode(LED0, OUTPUT); // Declaring Arduino LED pin as output
  //pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  //pinMode(LED3, OUTPUT);
  //pinMode(LED4, OUTPUT);
  digitalWrite(LED2, LOW); // turn the LED on

  // Arduino IDE Serial Monitor window to emulate what Arduino Tron sensors are reading
  Serial.begin(115200); // Serial connection from ESP-01 via 3.3v console cable

  if (initConsole) { // Values for display of console information
    initConsoleMessage();
  }

  // Establish a WiFi connection with router
  arduinoAgentSend();
  if (sendArduino) { // Values for send AI-IoTBPM Drools-jBPM post
    arduinoTronSend();
  }
  digitalWrite(LED2, HIGH); // turn the LED off

  // Deep sleep mode until RESET pin is connected to a LOW signal (pushbutton is pressed)
  ESP.deepSleep(0);
}

void loop(void) {
  Serial.println("sleeping..."); // Sleeping so will not get here
}

void arduinoAgentSend() {
  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT) ");
  Serial.println(loopCounter);
  //loopCounter++;

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.print("WiFi connected in: ");
  Serial.print(millis());
  Serial.print(", IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");


  if (!client.connect(agent, httpAgent)) { // http server is running on default port 80
    Serial.print("Connection Failed Status: ");
    Serial.println(WiFi.status());
    return;
  }

  Serial.println("Connected");

  switch (switchState) {
    case 1:
      client.print("GET"); // DTIM -  DTIM (Delivery Traffic Indication Message) beacon,
      break;
    case 2:
      client.print("GET /DEV0=ON");
      break;
    case 3:
      client.print("GET /DEV0=OFF");
      break;
    case 4:
      client.print("GET /DEV1=ON");
      break;
    case 5:
      client.print("GET /DEV1=OFF");
      break;
    case 6:
      client.print("GET /DEV2=ON");
      break;
    case 7:
      client.print("GET /DEV2=OFF");
      break;
    case 8:
      client.print("GET /DEV3=ON");
      break;
    case 9:
      client.print("GET /DEV3=OFF");
      break;
    case 10:
      client.print("GET /TONE1");
      break;
  }

  client.println(" HTTP/1.1");

  client.println("User-Agent: Arduino Tron_ESP-01 ver " + ver);
  client.println("Content-Length: 0");

  client.println(); // empty line for apache server

  clientAvail = 0;
  // Wait 1 seconds for server to respond then read response
  while ((!client.available()) && (clientAvail < 1000)) {
    delay(1); // wait 1 seconds
    clientAvail++;
  }

  response = "";
  agentCount = "";
  clientAvail = 0;
  while ((client.available()) && (clientAvail < 18))
  {
    String line = client.readStringUntil('\r');
    if (line.indexOf("Loop Counter") > 0) {
      response = client.readStringUntil('\r');
      agentCount = response.substring(1);
    }
    if (line.indexOf("</html>") > 0) {
      clientAvail = 19;
    }
    Serial.print(line);
    clientAvail++;
  }
  // delay(10); //
  client.stop();

  Serial.print("Connection Status: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Ok");
  } else {
    Serial.print("Error ");
    Serial.println(WiFi.status());
  }
  // WL_NO_SHIELD = 255
  // WL_IDLE_STATUS = 0
  // WL_NO_SSID_AVAIL = 1
  // WL_SCAN_COMPLETED = 2
  // WL_CONNECTED = 3
  // WL_CONNECT_FAILED = 4
  // WL_CONNECTION_LOST = 5
  // WL_DISCONNECTED = 6

  // WiFi.disconnect(); // DO NOT DISCONNECT WIFI IF YOU WANT TO LOWER YOUR POWER DURING LIGHT_SLEEP_T DELLAY !
  // wifi_set_sleep_type(LIGHT_SLEEP_T);
  if (response.length() > 0) {
    arduinoTronAction();
  }
  Serial.println("");
}

void arduinoTronSend() {
  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT) ");
  Serial.println(loopCounter);
  loopCounter++;

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  if (!client.connect(server, httpPort)) { // http server is running on default port 5055
    Serial.print("Connection Failed Status: ");
    Serial.println(WiFi.status());
    return;
  }

  Serial.println("Connected");
  client.print("GET /?id=" + id);
  // client.print("&timestamp=" + timestamp);
  // client.print("&lat=" + lat); <-- no GPS location needed in demo
  // client.print("&lon=" + lon);
  // client.print("&speed=" + speeds);
  // client.print("&bearing=" + bearing);
  // client.print("&altitude=" + altitude);
  // client.print("&accuracy=" + accuracy);
  // client.print("&batt=" + batt);

  client.print("&agentCount=" + agentCount);
  client.print("&keypress=" + TYPE_KEYPRESS_1);

  client.println(" HTTP/1.1");

  client.println("User-Agent: Arduino Tron ver " + ver);
  client.println("Content-Length: 0");

  client.println(); // empty line for apache server

  clientAvail = 0;
  // Wait 1 seconds for server to respond then read response
  while ((!client.available()) && (clientAvail < 1000)) {
    delay(1); // wait 1 seconds
    clientAvail++;
  }

  response = "";
  clientAvail = 0;
  while ((client.available()) && (clientAvail < 5))
  {
    String line = client.readStringUntil('\r');
    if ((line.indexOf("HTTP") == -1) && (clientAvail == 0)) {
      response = line;
    }
    if (line.length() == 1) {
      clientAvail = 6;
    }
    Serial.print(line);
    clientAvail++;
  }
  delay(10); //
  client.stop();

  Serial.print("Connection Status: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Ok");
  } else {
    Serial.print("Error ");
    Serial.println(WiFi.status());
  }
  // WL_NO_SHIELD = 255
  // WL_IDLE_STATUS = 0
  // WL_NO_SSID_AVAIL = 1
  // WL_SCAN_COMPLETED = 2
  // WL_CONNECTED = 3
  // WL_CONNECT_FAILED = 4
  // WL_CONNECTION_LOST = 5
  // WL_DISCONNECTED = 6

  // WiFi.disconnect(); // DO NOT DISCONNECT WIFI IF YOU WANT TO LOWER YOUR POWER DURING LIGHT_SLEEP_T DELLAY !
  // wifi_set_sleep_type(LIGHT_SLEEP_T);
  digitalWrite(LED0, LOW); // turn the LED off
  if (response.length() > 0) {
    arduinoTronAction();
  }
  Serial.println("");
}

void arduinoTronAction() {
}
