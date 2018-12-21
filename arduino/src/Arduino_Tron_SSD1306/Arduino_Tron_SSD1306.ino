/********************
  - Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)
  - Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM
  - Arduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using Arduino Tron AI-IoTBPM Processing
  - Executive Order Corporation
  - Copyright © 1978, 2018: Executive Order Corporation, All Rights Reserved
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
const char* ssid     = "Executive Order"; //  your network SSID (name)
const char* password = "SL550eodas"; // your network password

// Set web server port number to 80
WiFiClient client;
WiFiServer webserver(80);

String ver = "1.03E";
int loopCounter = 1; // loop counter

#define OLED_RESET 1 // define SSD1306 OLED reset (TX pin)
Adafruit_SSD1306 display(OLED_RESET);

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
  //Serial.println("- Arduino Tron Agent SSD1306 ver " + ver);
  //Serial.println("Copyright © 1978, 2018: Executive Order Corporation, All Rights Reserved");

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
  //Serial.println("Arduino Tron Agent SSD1306 started");

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
  display.println("Tron SSD1306 ver " + ver);
  display.display();
}

void loop() {
  // Check if a client has connected
  client = webserver.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  loopCounter++;

  int clientAvail = 0; // client.available() count
  // Wait 1 seconds for server to respond then read response
  while ((!client.available()) && (clientAvail < 1000)) {
    delay(1); // wait 1 seconds
    clientAvail++;
  }
  arduinoWebserver();
}

void arduinoWebserver() {
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
            int iget = header.indexOf("GET");
            String str = header.substring(iget + 5);
            int c1 = str.indexOf(','); //first place to cut string
            int c2 = str.indexOf(',', c1 + 1); //second place
            int c3 = str.indexOf(' ', c2 + 1); //second place
            String red = str.substring(0, c1);
            String green = str.substring(c1 + 1, c2);
            String blue = str.substring(c2 + 1, c3);
            red.replace('_', ' ');
            blue.replace('_', ' ');
            green.replace('_', ' ');

            // Clear the buffer.
            display.clearDisplay();

            // text display tests
            display.setTextSize(1);
            display.setCursor(0, 0);
            display.setTextColor(WHITE);
            display.println(red);
            display.println(green);

            display.setTextColor(BLACK, WHITE); // 'inverted' text
            display.println(blue);
            //display.println("AI-IoTBPM Drools-jBPM");
            display.setTextColor(WHITE);

            display.print("OLED Arduino Tron ");
            display.print(loopCounter);
            display.display();
          }
          // Display the HTML web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><title>Arduino Tron IoT Agent SSD1306</title>");
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
