/********************
  - Executive Order Corporation - Arduino Tron - Arduino ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)
  - Arduino Tron Drools-jBPM :: Executive Order Sensor Processor System - Arduino Tron MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM
  - Arduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using Arduino Tron AI-IoTBPM Processing
  - Executive Order Corporation
  - Copyright © 1978, 2018: Executive Order Corporation, All Rights Reserved
********************/

//#include <SimpleDHT.h> // <-- uncommit for dht11
//#include <IRrecv.h> // <-- uncommit for IR VS1838

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define ADC0 A0 // NodeMCU pin Analog ADC0 (A0)

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

#define BUTTON0 D0 // NodeMCU pin GPIO16 (D0)
#define BUTTON1 D1 // NodeMCU pin GPIO5 (D1)
#define BUTTON2 D2 // NodeMCU pin GPIO4 (D2)
#define BUTTON3 D3 // NodeMCU pin GPIO0 (D3)
#define BUTTON4 D4 // NodeMCU pin GPIO2 (D4)
#define BUTTON5 D5 // NodeMCU pin GPIO14 (D5)
#define BUTTON6 D6 // NodeMCU pin GPIO12 (D6)
#define BUTTON7 D7 // NodeMCU pin GPIO13 (D7)
#define BUTTON8 D8 // NodeMCU pin GPIO15 (D8)
#define BUTTON9 D9 // NodeMCU pin GPIO3 (D9-RXD0)
#define BUTTON10 D10 // NodeMCU pin GPIO1 (D10-TXD0)

// Update these with WiFi network values
const char* ssid     = "your-ssid"; //  your network SSID (name)
const char* password = "your-password"; // your network password

WiFiClient client;
WiFiServer webserver(80);

// Update these with Arduino Tron service IP address and unique unit id values
byte server[] = { 10, 0, 0, 2 }; // Set EOSpy server IP address as bytes
String id = "100111"; // Arduino Tron Device unique unit id

// Update these with your LAT/LON GPS position values
// You can find LAT/LON from an address https://www.latlong.net/convert-address-to-lat-long.html
String address = "National_Air_Space_Museum_600_Independence_Ave_Washington_DC_20560";
String lat = "38.888160"; // position LAT National Air Space Museum
String lon = "-77.019868"; // position LON

// Above are all the fields you need to provide values, the remaining fields are used in the Arduino Tron application
const bool readPushButton = false; // Values for the digitalRead value from gpiox button
const bool readDHT11Temp = false; // Values for the DHT11 digital temperature/humidity sensor
const bool readLDRLight = false; // Values for the LDR analog photocell light sensor
const bool readIRSensor = false; // Arduino values for IR sensor connected to GPIO2

const int httpPort = 5055; // Arduino Tron server is running on default port 5055
// OpenStreetMap Automated Navigation Directions is a map and navigation app for Android default port 5055

// Values ?id=334455&timestamp=1521212240&lat=38.888160&lon=-77.019868&speed=0.0&bearing=0.0&altitude=0.0&accuracy=0.0&batt=98.7
String timestamp = "1521212240"; // timestamp
String speeds = "0.0";
String bearing = "0.0";
String altitude = "0.0";
String accuracy = "0.0"; // position accuracy
String batt = "89.7"; // battery value
String light = "53.4"; // photocell value

// Arduino Tron currently supports these additional data fields in the Server Event data model:

// id=6&event=allEvents&protocol=osmand&servertime=<date>&timestamp=<date>&fixtime=<date>&outdated=false&valid=true
// &lat=38.85&lon=-84.35&altitude=27.0&speed=0.0&course=0.0&address=<street address>&accuracy=0.0&network=null
// &batteryLevel=78.3&textMessage=Message_Sent&temp=71.2&ir_temp=0.0&humidity=0.0&mbar=79.9
// &accel_x=-0.01&accel_y=-0.07&accel_z=9.79&gyro_x=0.0&gyro_y=-0.0&gyro_z=-0.0&magnet_x=-0.01&magnet_y=-0.07&magnet_z=9.81
// &light=91.0&keypress=0.0&alarm=Temperature&distance=1.6&totalDistance=3.79&motion=false

// You can add more additional fields to the data model and transmit via any device to the Arduino Tron Drools-jBPM processing

// Values for the DHT11 digital temperature/humidity sensor; &temp= and &humidity= fields
String temp = "0.0";
String humidity = "0.0";

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
int timeCounter = 901; // time counter
int actionState = 0; // actionState result received command
int switchState = 0; // digitalRead value from gpiox button
char readKeyboard = 0; // read serial command

// Arduino Time Sync from NTP Server using ESP8266 WiFi module
unsigned int localPort = 2390; // local port to listen for UDP packets
IPAddress timeServerIP;
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];
WiFiUDP udp;

unsigned long milsec = 0;
unsigned long epoch = 0;

// DHT11 digital temperature and humidity sensor pin Vout (sense)
int pinDHT11 = 2; // GPIO2
//SimpleDHT11 dht11; <-- uncommit for dht11

// LDR Photocell light interface for NodeMCU
int photocellChange = 10; // LDR and 10K pulldown resistor are connected to A0
float photocellLight; // Variable to hold last analog light value

// Arduino values for IR sensor connected to GPIO2
uint16_t RECV_PIN = D5; // D5 GPIO2
//IRrecv irrecv(RECV_PIN); // <-- uncommit for IR VS1838
//decode_results results; // <-- uncommit for IR VS1838
String irkey = "1.0";

// Set response jBPM Global Variable List
// kcontext.getKnowledgeRuntime().setGlobal("response", "");
String response = "";

// Required for LIGHT_SLEEP_T delay mode
extern "C" {
#include "user_interface.h"
}

void setup(void) {
  pinMode(LED0, OUTPUT); // Declaring Arduino LED pin as output
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED0, LOW); // turn the LED off

  pinMode(BUTTON5, INPUT); // Declaring Arduino pins as an inputs
  pinMode(BUTTON6, INPUT);
  pinMode(BUTTON7, INPUT);
  pinMode(BUTTON8, INPUT);

  // Arduino IDE Serial Monitor window to emulate what Arduino Tron sensors are reading
  Serial.begin(115200); // Serial connection from ESP-01 via 3.3v console cable

  // Connect to WiFi network
  Serial.println("Executive Order Corporation - Arduino Tron - Arduino ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)");
  Serial.println("Arduino Tron Drools-jBPM :: Executive Order Sensor Processor System - Arduino Tron MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM");
  Serial.println("- Arduino Tron Web Server ver " + ver);
  Serial.println("Copyright © 1978, 2018: Executive Order Corporation, All Rights Reserved");
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

  // Start the arduino tron webserver
  webserver.begin();
  Serial.println("Arduino Tron Web Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop(void) {
  // Check if a client has connected
  client = webserver.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.print("New client connection, loop ");
  Serial.println(loopCounter);
  loopCounter++;

  int ca1 = 0;
  // Wait up to 2 seconds for server to respond then read response
  while ((!client.available()) && (ca1 < 500)) {
    delay(1); // was 2 seconds
    ca1++;
  }
  arduinoWebserver();
  if ((irkey.indexOf("HTTP") == -1) && (alarm.indexOf("HTTP") == -1) &&
      (irkey.length() > 0) && (alarm.length() > 0)) {
    arduinoTronSend();
  }
}

void arduinoTronSend()
{
  digitalWrite(LED0, HIGH); // turn the LED on
  getTimeClock(); // get time clock for event timestamp

  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rExecutive Order Corporation - Arduino Tron Web Server - Arduino ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT) ");
  Serial.println(timestamp);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.print("Connected to ");
  Serial.print(ssid);
  Serial.print(" IP address: ");
  Serial.print(WiFi.localIP());
  Serial.print(" ESP8266 Chip Id ");
  Serial.print(ESP.getChipId());
  Serial.print(" gpio ");
  Serial.print(irkey); // switchState
  Serial.print(" loop ");
  Serial.println(loopCounter);

  if (!client.connect(server, httpPort)) { // http server is running on default port 5055
    Serial.print("Connection Failed Status: ");
    Serial.println(WiFi.status());
    return;
  }

  Serial.println("Connected");
  client.print("GET /?id=" + id);
  client.print("&timestamp=" + timestamp);
  // client.print("&lat=" + lat); <-- no GPS location needed in demo
  // client.print("&lon=" + lon);
  // client.print("&speed=" + speeds);
  // client.print("&bearing=" + bearing);
  // client.print("&altitude=" + altitude);
  // client.print("&accuracy=" + accuracy);
  client.print("&batt=" + batt);

  if (readDHT11Temp) {
    client.print("&temp=" + temp);
    client.print("&humidity=" + humidity);
  }

  // digitalRead GPIO15(D8) send values for web server
  client.print("&textMessage=" + textMessage);
  client.print("&keypress=" + irkey); // keypress=irkey
  client.print("&alarm=" + alarm);

  client.println(" HTTP/1.1");

  client.println("User-Agent: Arduino Tron ver " + ver);
  client.println("Content-Length: 0");

  client.println(); // empty line for apache server

  int ca2 = 0;
  // Wait up to 2 seconds for server to respond then read response
  while ((!client.available()) && (ca2 < 1000)) {
    delay(1); // was 2 seconds
    ca2++;
  }

  int ca3 = 0;
  response = "";
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    if ((line.indexOf("HTTP") == -1) && (ca3 == 0)) {
      response = line;
    }
    Serial.print(line);
    ca3++;
  }
  client.stop();

  Serial.print("Connection Status: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected Ok");
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
}

void arduinoWebserver() {
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int ind1 = request.indexOf('='); // find location of first =
  int ind2 = request.indexOf('&', ind1); //find location of first &
  irkey = request.substring(ind1 + 1, ind2); // captures keypress string

  ind1 = request.indexOf('=', ind2); //find location of second =
  ind2 = request.indexOf('&', ind1); //find location of second &
  alarm = request.substring(ind1 + 1, ind2); // captures alarm string

  ind1 = request.indexOf('=', ind2); //find location of third =
  ind2 = request.indexOf(' ', ind1); //find location of third
  textMessage = request.substring(ind1 + 1, ind2); // captures textMessage string

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println(""); //  do not forget this one

  client.println("<!DOCTYPE HTML>");
  client.println("<html><head><title>Arduino Tron Web Server</title><style type = ""text/css"">");

  client.println("body{background-color : powderblue;}");
  client.println("h1{color:black; font-family : arial;}");
  client.println("p{color:yellow; font-family : verdana;}");

  client.println("</style>Arduino Tron Web Server AI-IoTBPM :: Internet of Things Drools-jBPM</head><body>");
  //client.println("<h4>Arduino Tron Web Server MQTT AI-IoTBPM Drools-jBPM</h4>");
  client.println("<form action=""#"" method=""GET"">");

  client.print("<p>Connected to ");
  client.print(ssid);
  client.print(" ESP8266 Chip Id ");
  client.print(ESP.getChipId());
  client.println("</p>");

  client.println("Arduino Tron Event Condition ");
  client.println("<select name=""keypress"">");
  client.println("<option value=""1.0"">Power</option>");
  client.println("<option value=""2.0"">Mode</option>");
  client.println("<option value=""3.0"">Mute</option>");
  client.println("<option value=""4.0"">Forward</option>");
  client.println("<option value=""5.0"">Backward</option>");
  client.println("<option value=""6.0"">Swap</option>");
  client.println("<option value=""7.0"">U/SD</option>");
  client.println("<option value=""8.0"">Proximity</option>");
  client.println("<option value=""9.0"">Update</option>");
  client.println("</select>");
  client.println("<br>");

  client.println("Arduino Tron Event Send Alarm ");
  client.println("<select name=""alarm"">");
  client.println("<option value=""general"">General</option>");
  client.println("<option value=""sos"">S.O.S.</option>");
  client.println("<option value=""vibration"">Vibration</option>");
  client.println("<option value=""movement"">Movement</option>");
  client.println("<option value=""overspeed"">Overspeed</option>");
  client.println("<option value=""geofenceEnter"">Geo Fence Enter</option>");
  client.println("<option value=""geofenceExit"">Geo Fence Exit</option>");
  client.println("<option value=""temperature"">Temperature</option>");
  client.println("<option value=""tampering"">Tampering</option>");
  client.println("</select>");
  client.println("<br>");

  client.println("Arduino Tron Web Server Message ");
  client.println("<select name=""textMessage"">");
  client.println("<option value=""IoT_Device_Send_Message"">IoT Device Send Message</option>");
  client.println("<option value=""Server_Room_Temperature"">Server Room Temperature</option>");
  client.println("<option value=""Movement_Security_Alarm"">Movement Security Alarm</option>");
  client.println("<option value=""Illuminance_Alert_Message"">Illuminance Alert Message</option>");
  client.println("<option value=""IoT_Environment_Conditions"">IoT Environment Conditions</option>");
  client.println("<option value=""Too_Warm_Temp_Raise_Alarm"">Too Warm Temp Raise Alarm</option>");
  client.println("</select>");
  client.println("<br><br>");

  client.println("Send Arduino Tron Server Message <input type=submit value=Send><br><br>");
  client.println("<img src=""http://www.iotbpm.com/wp-content/uploads/2018/05/Arduino_Logotype-763x354.jpg"" alt=""Arduino Tron"">");
  client.println("</form></body></html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

// Arduino Time Sync from NTP Server using ESP8266 WiFi module
void getTimeClock()
{
  if ((milsec == 0) || (epoch == 0) || ((millis() - milsec) > 3600000)) {
    setNTPServerTime(); // get time clock for event timestamp
    milsec = millis();
    return;
  }
  unsigned long mpoch = epoch + ((millis() - milsec) / 1000);
  timestamp = String(mpoch);
}

void setNTPServerTime()
{
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  udp.begin(localPort);
  WiFi.hostByName(ntpServerName, timeServerIP);

  sendNTPpacket(timeServerIP);
  delay(500);

  int cb = udp.parsePacket();
  if (!cb) {
    delay(1);
  }
  else {
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    const unsigned long seventyYears = 2208988800UL;
    epoch = secsSince1900 - seventyYears; // Unix epoch number of seconds since midnight 1-1-70
    // Serial.print("UNX");
    // Serial.println(epoch);
    timestamp = String(epoch);
  }
  udp.stop();
}

unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("Sending NTP packet...");
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011; // LI, Version, Mode
  packetBuffer[1] = 0; // Stratum, or type of clock
  packetBuffer[2] = 6; // Polling Interval
  packetBuffer[3] = 0xEC; // Peer Clock Precision
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  udp.beginPacket(address, 123);
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

