/********************
  - Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)
  - Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM
  - Arduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using Arduino Tron AI-IoTBPM Processing
  - Executive Order Corporation
  - Copyright © 1978, 2019: Executive Order Corporation, All Rights Reserved
********************/
/*********************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x64 size display using I2C to communicate
  3 pins are required to interface (2 I2C and one reset)

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
*********************************************************************/

#include <SimpleDHT.h>
// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Load Wi-Fi library
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

// Replace these with WiFi network credentials
const char* ssid     = "your-ssid"; //  your network SSID (name)
const char* password = "your-password"; // your network password

// Set web server port number to 80
WiFiClient client;
WiFiServer webserver(80);

// Update these with Arduino Tron service IP address and unique unit id values
byte server[] = { 10, 0, 0, 2 }; // Set EOSpy server IP address as bytes
String id = "100888"; // Arduino Tron Device unique unit id

const int httpPort = 5055; // Arduino Tron server is running on default port 5055
// OpenStreetMap Automated Navigation Directions is a map and navigation app for Android default port 5055

String days[] = {"", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat", "Sun"};
String months[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

byte temp = 0, humidity = 0;
byte temp_prev = 0, humidity_prev = 0;
int hour = 0, minute = 0, second = 0;
int month = 0, day = 0, year = 0, wday = 0;
String message = ""; // Values for message and time clock

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

String ver = "1.03E";
int loopCounter = 1; // loop counter
int clientAvail = 0; // client.available() count
int messageCount = 0; // message counter
unsigned long milsec = 0;
boolean DHTUpdate = true;
boolean messageUpdate = false;
boolean messageFlash = false;

// DHT11 digital temperature and humidity sensor pin Vout (sense)
// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 1; // was 2-GPIO2, move to pin 1 for IoTDHT11
SimpleDHT11 dht11; // <-- for DHT11

#define OLED_RESET 1 // define SSD1306 OLED reset (TX pin)
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

String irkey = "1.0";

// Set response jBPM Global Variable List
// kcontext.getKnowledgeRuntime().setGlobal("response", "");
String response = "";

// Required for LIGHT_SLEEP_T delay mode
extern "C" {
#include "user_interface.h"
}

void setup() {
  // Arduino IDE Serial Monitor window to emulate what Arduino Tron sensors are reading
  Serial.begin(9600); // Serial connection from ESP-01 via 3.3v console cable

  // Connect to WiFi network
  //Serial.println("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)");
  //Serial.println("Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM");
  //Serial.println("- Arduino Tron IoT ver " + ver);
  //Serial.println("Copyright © 1978, 2019: Executive Order Corporation, All Rights Reserved");

  Wire.begin(2, 0); // set I2C pins (SDA = GPIO2, SCL = GPIO0), default clock is 100kHz
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3D (for the 128x64)
  delay(200);

  // Show image buffer on the display hardware
  // Since the buffer is initalized with an Adafruit splashscreen internally, this will display the splashscreen
  display.display();
  delay(200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    //Serial.print(".");
  }

  // Start the arduino tron agent
  webserver.begin();
  //Serial.println("Arduino Tron IoT started");

  // Clear the buffer
  display.clearDisplay();

  // Print the IP address
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.println("Arduino Tron ^ AI-IoT");
  display.print("WiFi ");
  display.println(ssid);

  display.print("http://");
  display.println(WiFi.localIP());
  display.println("Tron IoT OLED " + ver);
  display.display();

  delay(2000);
  // Clear the buffer
  display.clearDisplay();
}

void loop() {
  readDHT11(); // read DHT11 digital temperature and humidity sensor
  if (((temp != temp_prev) || (humidity != humidity_prev)) && ((temp != 99) && (humidity != 99))) {
    DHTUpdate = true;
  }
  second = second + clockSecond();
  if (second > 59) {
    second = second - 60;
    minute++;
  }
  if (minute > 60) {
    minute = 0;
    hour++;
  }
  if (hour > 23) {
    hour = 0;
  }

  if (DHTUpdate) {
    display.fillRect(70, 45, 128, 64, BLACK);
    displayTemp();
    arduinoTronSend(); // <-- arduinoTronSend for dht11
    DHTUpdate = false;
    temp_prev = temp;
    humidity_prev = humidity;
  }

  //The portion of the screen that shows the time and date are cleared
  display.fillRect(0, 0, 64, 64, BLACK);
  display.fillRect(0, 0, 128, 20, BLACK);

  displayTime(); // display the real-time clock data on the Serial Monitor,
  display.display();
  delay(200);

  // Check if a client has connected
  client = webserver.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  //Serial.print("New client connection, loop ");
  //Serial.println(loopCounter);
  loopCounter++;

  int clientAvail = 0; // client.available() count
  // Wait 1 seconds for server to respond then read response
  while ((!client.available()) && (clientAvail < 1000)) {
    delay(1); // wait 1 seconds
    clientAvail++;
  }
  arduinoWebserver();
}

void arduinoTronSend()
{
  //digitalWrite(LED2, LOW); // turn the LED on
  temp_prev = temp;
  humidity_prev = humidity;

  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  //Serial.print("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT) ");
  //Serial.println(loopCounter);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    //Serial.print(".");
  }

  if (!client.connect(server, httpPort)) { // http server is running on default port 5055
    //Serial.print("Connection Failed Status: ");
    //Serial.println(WiFi.status());
    return;
  }

  //Serial.println("Connected");
  client.print("GET /?id=" + id);
  // client.print("&timestamp=" + timestamp);
  // client.print("&lat=" + lat); <-- no GPS location needed in demo
  // client.print("&lon=" + lon);
  // client.print("&speed=" + speeds);
  // client.print("&bearing=" + bearing);
  // client.print("&altitude=" + altitude);
  // client.print("&accuracy=" + accuracy);
  // client.print("&batt=" + batt);

  // switchState NodeMCU gpio pinMode()
  client.print("&keypress=" + TYPE_KEYPRESS_1);

  // int tempF = (temp * 9 / 5) + 32;
  client.print("&temp=" + String(temp));
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
    //Serial.print(line);
    clientAvail++;
  }
  // client.stop();

  //Serial.print("Connection Status: ");
  if (WiFi.status() == WL_CONNECTED) {
    //Serial.println("Ok");
  } else {
    //Serial.print("Error ");
    //Serial.println(WiFi.status());
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
  //Serial.println("");
}

// Arduino values for the DHT11 digital temperature/humidity sensor; &temp= and &humidity= fields
// DHT11 digital temperature and humidity sensor pin Vout (sense)
void readDHT11() {
  temp = 0;
  humidity = 0;
  int err = SimpleDHTErrSuccess; // DHT11 error wait for start low signal

  if ((err = dht11.read(pinDHT11, &temp, &humidity, NULL)) != SimpleDHTErrSuccess) {
    temp = 99;
    humidity = 99;
    return;
  }
  // convert to Fahrenheit
  temp = (temp * 9 / 5) + 32;
}

void arduinoWebserver() {
  int c1 = 0, c2 = 0;
  String line = ""; // Store incoming data from client
  String header = ""; // Store the HTTP webserver request
  while (client.connected()) { // loop while the client's connected
    if (client.available()) { // if there's bytes to read from the client,
      char c = client.read(); // read a byte, then
      //Serial.write(c); // print it on the serial monitor
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

          if (header.indexOf("favicon") >= 0) {
          } else {
            c1 = header.indexOf("&datetime=");
            if (c1 >= 0) {
              month = header.substring(c1 + 10, c1 + 12).toInt();
              day = header.substring(c1 + 13, c1 + 15).toInt();
              year = header.substring(c1 + 16, c1 + 20).toInt();
              wday = header.substring(c1 + 21, c1 + 22).toInt();

              hour = header.substring(c1 + 23, c1 + 25).toInt();
              minute = header.substring(c1 + 26, c1 + 28).toInt();
              second = header.substring(c1 + 29, c1 + 31).toInt();
            }
            c1 = header.indexOf("&message=");
            if (c1 >= 0) {
              c2 = header.indexOf('&', c1 + 1);
              message = header.substring(c1 + 9, c2);
              message.replace('_', ' ');
              messageUpdate = true;
              messageCount = 0;
            }
            c1 = header.indexOf("&temp=");
            if (c1 >= 0) {
              c2 = header.indexOf('&', c1 + 1);
              //            temp = header.substring(c1 + 6, c2).toInt();
              //            if (temp > 0 ) {
              //              DHTUpdate = true;
              //            }
            }
            c1 = header.indexOf("&humidity=");
            if (c1 >= 0) {
              c2 = header.indexOf('&', c1 + 1);
              //            humidity = header.substring(c1 + 10, c2).toInt();
            }
          }

          // Display the HTML web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><title>Arduino Tron IoT Display</title>");
          client.println("Arduino Tron Agent AI-IoTBPM :: Internet of Things using AI-IoTBPM Drools-jBPM</head><br>");
          client.println("<body>Loop Counter ");
          client.println(loopCounter);
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
  //Serial.println("Client disconnected");
  //Serial.println("");
}

void displayTime() {
  if (messageUpdate) {
    if (messageFlash) {
      display.setTextColor(BLACK, WHITE); // 'inverted' text
    } else {
      display.setTextColor(WHITE);
    }
    messageFlash = !messageFlash;
    display.setCursor(0, 0);
    display.print(message);

    messageCount++;
    if (messageCount > 30) {
      messageUpdate = false;
    }
  } else {
    display.setCursor(70, 0);
    display.print(day < 10 ? "0" + String(day) : String(day)); //dayOfMonth
    display.print(",");

    display.setCursor(91, 0);
    display.print(year);

    display.setCursor(40, 9); // 10
    display.print(hour < 10 ? "0" + String(hour) : String(hour));
    display.print(":");

    display.setCursor(58, 9);
    display.print(minute < 10 ? "0" + String(minute) : String(minute));
    display.print(":");

    display.setCursor(75, 9);
    display.print(second < 10 ? "0" + String(second) : String(second));

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25, 0);
    display.print(days[wday]);

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(50, 0);
    display.print(months[month]);

    display.setCursor(70, 25);
    display.print("Tron IoT");
  }

  float x1, y1, a, b; // hour hand
  const float pi = 3.14;
  a = ((hour - 15) * 30);
  b = (a * pi) / 180;

  x1 = 40 + (9 * cos(b));
  y1 = 41 + (9 * sin(b));
  display.drawLine(40, 41, x1, y1, WHITE);

  //  float x1, y1, a, b;
  //  const float pi = 3.14;
  a = ((minute - 15) * 6); // minute hand
  b = (a * pi) / 180;

  x1 = 40 + (17 * cos(b));
  y1 = 41 + (17 * sin(b));
  display.drawLine(40, 41, x1, y1, WHITE);

  //float x1, y1, a, b;
  a = ((second - 15) * 6); // second hand
  b = (a * pi) / 180;

  x1 = 40 + (19 * cos(b));
  y1 = 41 + (19 * sin(b));
  display.drawLine(40, 41, x1, y1, WHITE);

  // analog clock
  display.drawCircle(40, 41, 22, WHITE);
  display.drawCircle(40, 41, 1, WHITE);

  display.drawLine(40, 20, 40, 25, WHITE); //12
  display.drawLine(40, 63, 40, 58, WHITE); //6
  display.drawLine(62, 41, 57, 41, WHITE); //3
  display.drawLine(19, 41, 24, 41, WHITE); //9
  display.drawLine(50, 24, 47, 28, WHITE); //1
  display.drawLine(57, 31, 53, 34, WHITE); //2
  display.drawLine(60, 51, 54, 48, WHITE); //4
  display.drawLine(51, 58, 48, 54, WHITE); //5
  display.drawLine(29, 58, 32, 54, WHITE); //7
  display.drawLine(21, 51, 25, 48, WHITE); //8

  display.drawLine(22, 31, 27, 33, WHITE); //10
  display.drawLine(30, 23, 32, 28, WHITE); //11
}

void displayTemp() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(70, 45);
  display.print("Temp: ");
  display.print(temp);
  display.print("F");

  display.setCursor(70, 56);
  display.print("Humd: ");
  display.print(humidity);
  display.print("%");
}

int clockSecond() {
  if (milsec == 0) {
    milsec = millis();
  }
  int x = ((millis() - milsec) / 700); // clock seems to always run slow
  if ( x > 0) {
    milsec = millis();
  } return x;
}
