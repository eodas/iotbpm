/********************
  - Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)
  - Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM
  - Arduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using Arduino Tron AI-IoTBPM Processing
  - Executive Order Corporation
  - Copyright © 1978, 2020: Executive Order Corporation, All Rights Reserved
********************/

#include <SimpleDHT.h> // Temperature sensor DHT Library
// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2

// Load Wi-Fi library
#include <ESP8266WiFi.h> // WiFi Shield ESP8266 ESP-12f Library
#include <time.h> // Time setting library

const int timezone = -5; // Timezone (New Your)

// | RX     VCC
// A GPIO0  RST
// N GPIO2  CH_PD
// T GRD    TX

// TB:IoT-MCU ESP-01S-Relay-v1.0 send digitalWrite(RELAY) to GPIO0
#define LED0 0 //GPIO0 (SPI_CS2)
#define LED1 1 //GPIO1 on board LED ESP-01 (U0TXD) 
#define LED2 2 //GPIO2 on board LED ESP-01S 
#define LED3 3 //GPIO3 (U0RXD)

// Update these with WiFi network values
const char* ssid     = "your-ssid"; //  your network SSID (name)
const char* password = "your-password"; // your network password

// Set web server port number to 80
WiFiClient client;
WiFiServer webserver(80);

String days[] = {"", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat", "Sun"};
String months[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

// Update these with Arduino Tron service IP address and unique unit id values
byte server[] = { 10, 0, 0, 2 }; // Set EOSpy server IP address as bytes
String id = "100111"; // Arduino Tron Device unique unit id

// Update these with your LAT/LON GPS position values
// You can find LAT/LON from an address https://www.latlong.net/convert-address-to-lat-long.html
String address = "National_Air_Space_Museum_600_Independence_Ave_Washington_DC_20560";
String lat = "38.888160"; // position LAT National Air Space Museum
String lon = "-77.019868"; // position LON

// Above are all the fields you need to provide values, the remaining fields are used in the Arduino Tron application
const bool sendArduinoTron = false; // Arduino Tron transmit values to IoTBPM Server
const int httpPort = 5055; // Arduino Tron server is running on default port 5055
// OpenStreetMap Automated Navigation Directions is a map and navigation app for Android default port 5055

// Values ?id=334455&timestamp=1521212240&lat=38.888160&lon=-77.019868&speed=0.0&bearing=0.0&altitude=0.0&accuracy=0.0&batt=98.7
String datetime = ""; // Values for message and time clock
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

// Values to send in &textMessage= filed
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

// DHT11 digital temperature and humidity sensor pin Vout (sense)
// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2; // 2-GPIO2 for IoTDHT11
SimpleDHT11 dht11; // <-- for DHT11

// Values for the DHT11 digital temperature/humidity sensor; &temp= and &humidity= fields
byte celsius = 0;
byte fahrenheit = 0;
byte humidity = 0;
byte celsius_prev = 0;
byte humidity_prev = 0;
int err = 0;

String irkey = "1.0";

// Set response jBPM Global Variable List
// kcontext.getKnowledgeRuntime().setGlobal("response", "");
String response = "";

// Required for LIGHT_SLEEP_T delay mode
extern "C" {
#include "user_interface.h"
}

void setup(void) {
  //pinMode(LED0, OUTPUT); // Initialize Arduino GPIO pins as outputs
  //pinMode(LED1, OUTPUT);
  //pinMode(LED2, OUTPUT);
  //pinMode(LED3, OUTPUT);
  //digitalWrite(LED0, HIGH); // TB:IoT-MCU ESP-01S-Relay-v1.0 send digitalWrite(RELAY) to GPIO0
  //digitalWrite(LED1, HIGH);
  //digitalWrite(LED2, HIGH);
  //digitalWrite(LED3, HIGH);

  // Arduino IDE Serial Monitor window to emulate what Arduino Tron sensors are reading
  Serial.begin(115200); // Serial connection from ESP-01 via 3.3v console cable

  // Connect to WiFi network
  Serial.println("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)");
  Serial.println("Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM");
  Serial.println("- Arduino Tron Web Automation DHT11 ver " + ver);
  Serial.println("Copyright © 1978, 2020: Executive Order Corporation, All Rights Reserved");
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
  Serial.println("Arduino Tron Web Automation DHT11 started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  configureTime();
}

void loop(void) {
  timeCounter++;

  time_t now = time(nullptr);
  datetime = buildDateTime(now);
  timestamp = String(now);

  if (timeCounter > 900) {
    timeCounter = 0;
    readDHT11(); // read DHT11 digital temperature and humidity sensor

    if ((celsius != 0) && (humidity != 0)) {
      if ((celsius != celsius_prev) || (humidity != humidity_prev)) {
        arduinoTronSend(); // <-- arduinoTronSend for dht11
      }
      Serial.print((int)celsius); Serial.print(" *C, ");
      Serial.print((int)humidity); Serial.println(" H");
    }

    // DHT11 sampling rate is 1HZ.
    delay(10);

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
}

void arduinoTronSend()
{
  //digitalWrite(LED2, LOW); // turn the LED on
  celsius_prev = celsius;
  humidity_prev = humidity;

  if (!sendArduinoTron) {
    return;
  }

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

  // switchState NodeMCU gpio pinMode()
  client.print("&keypress=" + TYPE_KEYPRESS_1);

  // int tempF = (temp * 9 / 5) + 32;
  client.print("&temp=" + String(fahrenheit));
  client.print("&humidity=" + String(humidity));

  // digitalRead GPIO15(D8) send values for web server DHT11
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
  delay(10); //
  // client.stop();

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
  //digitalWrite(LED2, HIGH); // turn the LED off
  Serial.println("");
}

// Arduino values for the DHT11 digital temperature/humidity sensor; &temp= and &humidity= fields
// DHT11 digital temperature and humidity sensor pin Vout (sense)
void readDHT11() {
  byte t_celsius = 0;
  byte t_humidity = 0;
  err = SimpleDHTErrSuccess; // DHT11 error wait for start low signal
  if ((err = dht11.read(pinDHT11, &t_celsius, &t_humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, error = ");
    Serial.println(err);
    return;
  }
  celsius = t_celsius;
  humidity = t_humidity;
  // convert to Fahrenheit
  fahrenheit = (celsius * 9 / 5) + 32;
}

void arduinoWebserver() {
  String line = ""; // Store incoming data from client
  String header = ""; // Store the HTTP webserver request
  while (client.connected()) { // loop while the client's connected
    if (client.available()) { // if there's bytes to read from the client,
      char c = client.read(); // read a byte, then
      Serial.write(c); // print it on the serial monitor
      header += c;

      if (c == '\n') { // if the byte is a newline character
        // if the current line is blank, you got two newline characters in a row.
        // that is the end of the client HTTP request, so send a response:
        if (line.length() == 0) {
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          // turns relay GPIOs on and off
          if (header.indexOf("/DEV0=ON") >= 0) {
          }

          if (header.indexOf("favicon") >= 0) {
            Serial.print("Google Chrome crap");
          }

          // Display the HTML web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><title>Arduino Tron IoTDHT11 Temp</title>");
          client.println("Arduino Tron IoTDHT11 Temp AI-IoTBPM<br>");
          client.println("Internet of Things using AI-IoTBPM &nbsp; loop ");
          client.println(loopCounter);
          client.println("</head><br><br><body>");
          client.println(datetime);

          // values for the DHT11 digital temperature/humidity sensor
          client.println("<br><br>DHT11 Temperature ");
          client.print((int)celsius); client.print(" *C, &nbsp; ");

          // convert to Fahrenheit - tempF = (temp * 9 / 5) + 32;
          client.print((int)fahrenheit);
          client.println(" *F &nbsp; /  &nbsp; Humidity ");
          client.print((int)humidity); client.println(" H");
          client.println("</body></html>");

          // The HTTP response ends with another blank line
          client.println();
          // Break out of the while loop
          break;
        } else { // if a newline, then clear currentLine
          line = "";
        }
      } else if (c != '\r') { // if anything else but a carriage return character,
        line += c; // add it to the end of the currentLine
      }
    }
  }
  header = ""; // Clear the header variable
  // client.stop(); // Close the connection
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

// Gets date/time info for an specific timezone
void configureTime() {
  configTime(timezone * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("\nWaiting for time");

  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Time configured.");
  Serial.println("");
}

// Builds date/time information.
// returns: date/time string information in 'yyyy-MM-ddTHH:mm:ssZ' format.
String buildDateTime(time_t now) {
  struct tm * timeinfo;
  timeinfo = localtime(&now);
  String c_month = (String) (timeinfo->tm_mon + 1);
  String c_day = (String) (timeinfo->tm_mday);
  String c_year = (String) (timeinfo->tm_year + 1900);
  String c_hour = (String) (timeinfo->tm_hour);
  String c_min = (String) (timeinfo->tm_min);
  String c_sec = (String) (timeinfo->tm_sec);
  //String datetime = "Date " + c_month + "-" + c_day + "-" + c_year + ", &nbsp; Time " + c_hour + ":" + c_min + ":" + c_sec;
  String datetime = "Today: " + days[timeinfo->tm_wday] + ", " + months[timeinfo->tm_mon + 1] + " " + c_day + ", " + c_year + " &nbsp; Time: " + c_hour + ":" + c_min + ":" + c_sec;


  if (timezone < 0) {
    datetime += "-0" + (String)(timezone * -100);
  } else {
    datetime += "0" + (String)(timezone * 100);
  }
  return datetime;
}
