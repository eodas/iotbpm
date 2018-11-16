/********************
  - Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)
  - Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM
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
int clientAvail = 0; // client.available() count
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
  Serial.println("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)");
  Serial.println("Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM");
  Serial.println("- Arduino Tron Web Server Automation ver " + ver);
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
  Serial.println("Arduino Tron Web Server Automation started");

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

  clientAvail = 0; // client.available()) count
  // Wait 1 seconds for server to respond then read response
  while ((!client.available()) && (clientAvail < 1000)) {
    delay(1); // wait 1 seconds
    clientAvail++;
  }
  arduinoWebserver();
  if ((irkey.indexOf("HTTP") == -1) && (irkey.length() > 0)) {
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
  Serial.print("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT) ");
  Serial.println(loopCounter);

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
  Serial.println("");
}

void arduinoWebserver() {
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int ind1 = request.indexOf('='); // find location of first =
  int ind2 = request.indexOf(' ', ind1); //find location of first &
  irkey = request.substring(ind1 + 1, ind2); // captures keypress string

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println(""); //  do not forget this one

  String web = "<!DOCTYPE HTML>\
  <html>\
  \
  <head>\
  <title>Arduino Tron IoT Automation</title>\
  <style type = ""text/css"">\
  \
    body {background-image : url(""http://www.iotbpm.com/wp-content/uploads/2018/05/Arduino_Logotype-763x354.jpg""); background-repeat : no-repeat; background-color : powderblue;}\
    h1{color:black; font-family : arial;}\
    p{color:yellow; font-family : verdana;}\
  </style>\
  Arduino Tron Automation AI-IoTBPM :: Arduino Tron MQTT Web Server using AI-IoTBPM Drools-jBPM\
  </head>\
  \
  <body>\
  \
  <form action=""#"" method=""GET"">\
    <br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>\
    Arduino Tron Automation Command\
    <select name=""keypress"">\
      <option value=""1.0"">Lock Office Doors</option>\
      <option value=""2.0"">Activate Security Alarm</option>\
      <option value=""3.0"">Turn ON Office Lights</option>\
      <option value=""4.0"">Lower Office Thermostats</option>\
      <option value=""5.0"">Open Office Window Shades</option>\
      <option value=""6.0"">After Hours Answer Service</option>\
    </select>&nbsp;&nbsp;&nbsp;\
    <input type=submit value=Send>\
  \
  </form>\
  </body>\
  </html>";
  client.println(web);

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

