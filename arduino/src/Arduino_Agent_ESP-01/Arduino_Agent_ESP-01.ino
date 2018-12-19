/********************
  - Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)
  - Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM
  - Arduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using Arduino Tron AI-IoTBPM Processing
  - Executive Order Corporation
  - Copyright © 1978, 2018: Executive Order Corporation, All Rights Reserved
********************/

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

const bool autoReset = false; // Values for auto reset 3 second delay, then off

String ver = "1.03E";
int loopCounter = 1; // loop counter
const byte tonepin = 3; // 2-Speaker connected to GPIO2 or 3-2N2222 transistor audio amplifier
unsigned long milsec = 0; // relay millis counter

// LC Technology HEX command Serial.write(relay) to serial open/close relay
byte relay0ON[]  = {0xA0, 0x01, 0x00, 0xA1};
byte relay0OFF[] = {0xA0, 0x01, 0x01, 0xA2};
byte relay1ON[]  = {0xA0, 0x02, 0x00, 0xA3};
byte relay1OFF[] = {0xA0, 0x02, 0x01, 0xA3};

// Auxiliary variables to store the current output state
bool stateRelay0 = false;
bool stateRelay1 = false;
bool stateRelay2 = false;
bool stateRelay3 = false;

// Required for LIGHT_SLEEP_T delay mode
extern "C" {
#include "user_interface.h"
}

void setup(void) {
  pinMode(LED0, OUTPUT); // Initialize Arduino GPIO pins as outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED0, HIGH); // TB:IoT-MCU ESP-01S-Relay-v1.0 send digitalWrite(RELAY) to GPIO0
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);

  // Arduino IDE Serial Monitor window to emulate what Arduino Tron sensors are reading
  Serial.begin(115200); // Serial connection from ESP-01 via 3.3v console cable

  // Connect to WiFi network
  Serial.println("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)");
  Serial.println("Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM");
  Serial.println("- Arduino Tron Agent ESP-01 ver " + ver);
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

  // Start the arduino tron agent
  webserver.begin();
  Serial.println("Arduino Tron Agent ESP-01 started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  //Serial.flush(); // LC Technology HEX command Serial.write(relay) to serial
  //delay(500); // *** NOTE: to use LC Technology HEX commet out Serial.print();
  //Serial.end();
  //Serial.begin(9600); // Initialize serial for LC Technology Relay
}

void loop(void) {
  if (autoReset == true) { // Values for auto reset 3 second delay, then off
    if (stateRelay0 == true) {
      if ((millis() - milsec) > 3000) { // 3 second delay, then off
        stateRelay0 = false;
        Serial.println("GPIO 0 off : milsec delay");
        //Serial.write(relay0OFF, sizeof(relay0OFF)); // LC Technology HEX relay0 OFF
        digitalWrite(LED0, HIGH); // TB:IoT-MCU digitalWrite(RELAY) relay0 OFF
      }
    }
  }

  // Check if a client has connected
  client = webserver.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.print("New client connection, loop ");
  Serial.println(loopCounter);
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
            stateRelay0 = true;
            Serial.println("GPIO 0 on");
            //Serial.write(relay0ON, sizeof(relay0ON)); // LC Technology HEX relay0 ON
            digitalWrite(LED0, LOW); // TB:IoT-MCU digitalWrite(RELAY) relay0 ON
            milsec = millis(); // relay millis counter

          }
          if (header.indexOf("/DEV0=OFF") >= 0) {
            stateRelay0 = false;
            Serial.println("GPIO 0 off");
            //Serial.write(relay0OFF, sizeof(relay0OFF)); // LC Technology HEX relay0 OFF
            digitalWrite(LED0, HIGH); // TB:IoT-MCU digitalWrite(RELAY) relay0 OFF
          }

          if (header.indexOf("/DEV1=ON") >= 0) {
            stateRelay1 = true;
            Serial.println("GPIO 1 on");
            //Serial.write(relay1ON, sizeof(relay1ON)); // LC Technology HEX relay1 ON
            digitalWrite(LED1, LOW); // TB:IoT-MCU digitalWrite(RELAY) relay1 ON
          }
          if (header.indexOf("/DEV1=OFF") >= 0) {
            stateRelay1 = false;
            Serial.println("GPIO 1 off");
            //Serial.write(relay1OFF, sizeof(relay1OFF)); // LC Technology HEX relay1 OFF
            digitalWrite(LED1, HIGH); // TB:IoT-MCU digitalWrite(RELAY) relay1 OFF
          }

          if (header.indexOf("/DEV2=ON") >= 0) {
            stateRelay2 = true;
            Serial.println("GPIO 2 on");
            digitalWrite(LED2, LOW); // TB:IoT-MCU digitalWrite(RELAY) relay2 ON
          }
          if (header.indexOf("/DEV2=OFF") >= 0) {
            stateRelay2 = false;
            Serial.println("GPIO 2 off");
            digitalWrite(LED2, HIGH); // TB:IoT-MCU digitalWrite(RELAY) relay2 OFF
          }

          if (header.indexOf("/DEV3=ON") >= 0) {
            stateRelay3 = true;
            Serial.println("GPIO 3 on");
            digitalWrite(LED3, LOW); // TB:IoT-MCU digitalWrite(RELAY) relay3 ON
          }
          if (header.indexOf("/DEV3=OFF") >= 0) {
            stateRelay3 = false;
            Serial.println("GPIO 3 off");
            digitalWrite(LED3, HIGH); // TB:IoT-MCU digitalWrite(RELAY) relay3 OFF
          }

          if (header.indexOf("/CHIME") >= 0) { // Speaker connected to GPIO2 or GPIO3
            tone(tonepin, 587, 300);
            delay(200);
            tone(tonepin, 392, 300);
          }

          if (header.indexOf("/TONE") >= 0) {
            tone(tonepin, 330, 300); // play e4
            delay(250);
            tone(tonepin, 247, 300); // play b3
            delay(250);
            tone(tonepin, 294, 300); // play d4
            delay(250);
            tone(tonepin, 262, 300); // play c4
            delay(250);
            tone(tonepin, 220, 800); // play a3
            delay(700);
            tone(tonepin, 147, 300); // play d3
            delay(250);
            tone(tonepin, 175, 300); //play f3
            delay(250);
            tone(tonepin, 220, 300); //play a3
            delay(250);
            tone(tonepin, 247, 400); // play b3
          }

          // Display the HTML web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><title>Arduino Tron IoT Agent ESP-01</title>");
          client.println("Arduino Tron Agent AI-IoTBPM :: Internet of Things using AI-IoTBPM Drools-jBPM</head><br>");
          client.println("<body>Loop Counter ");
          client.println(loopCounter);

          // Display current state for GPIO 0
          client.println("<br>GPIO 0 ");
          if (stateRelay0 == true) {
            client.println("on");
          } else {
            client.println("off");
          }

          // Display current state for GPIO 1
          client.println("<br>GPIO 1 ");
          if (stateRelay1 == true) {
            client.println("on");
          } else {
            client.println("off");
          }

          // Display current state for GPIO 2
          client.println("<br>GPIO 2 ");
          if (stateRelay2 == true) {
            client.println("on");
          } else {
            client.println("off");
          }

          // Display current state for GPIO 3
          client.println("<br>GPIO 3 ");
          if (stateRelay3 == true) {
            client.println("on");
          } else {
            client.println("off");
          }
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
