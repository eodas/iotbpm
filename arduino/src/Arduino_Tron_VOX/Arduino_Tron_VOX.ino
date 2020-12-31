/********************
  - Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)
  - Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM
  - Arduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using Arduino Tron AI-IoTBPM Processing
  - Executive Order Corporation
  - Copyright © 1978, 2021: Executive Order Corporation, All Rights Reserved
********************/

// VOX for Serial MP3 Player (YX5300 chip)
// Hardware: Serial MP3 Player *1
// Board: Arduino MP3 YX5300 Player

// Load Wi-Fi library
#include <ESP8266WiFi.h>

// | RX     VCC
// A GPIO0  RST
// N GPIO2  CH_PD
// T GRD    TX

// Replace these with WiFi network credentials
const char* ssid     = "your-ssid"; //  your network SSID (name)
const char* password = "your-password"; // your network password

// Set web server port number to 80
WiFiClient client;
WiFiServer webserver(80);

String ver = "1.03E";
int loopCounter = 1; // loop counter

static int8_t Send_buf[8] = {0}; // Buffer for Send commands.  // BETTER LOCALLY
static uint8_t ansbuf[10] = {0}; // Buffer for the answers.    // BETTER LOCALLY

String mp3Answer;           // Answer from the MP3.

// MP3 Command byte
#define CMD_NEXT_SONG     0X01  // Play next song.
#define CMD_PREV_SONG     0X02  // Play previous song.
#define CMD_PLAY_W_INDEX  0X03
#define CMD_VOLUME_UP     0X04
#define CMD_VOLUME_DOWN   0X05
#define CMD_SET_VOLUME    0X06

#define CMD_SNG_CYCL_PLAY 0X08  // Single Cycle Play.
#define CMD_SEL_DEV       0X09
#define CMD_SLEEP_MODE    0X0A
#define CMD_WAKE_UP       0X0B
#define CMD_RESET         0X0C
#define CMD_PLAY          0X0D
#define CMD_PAUSE         0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F

#define CMD_STOP_PLAY     0X16
#define CMD_FOLDER_CYCLE  0X17
#define CMD_SHUFFLE_PLAY  0x18 //
#define CMD_SET_SNGL_CYCL 0X19 // Set single cycle.

#define CMD_SET_DAC       0X1A
#define DAC_ON            0X00
#define DAC_OFF           0X01

#define CMD_PLAY_W_VOL        0X22
#define CMD_PLAYING_N         0x4C
#define CMD_QUERY_STATUS      0x42
#define CMD_QUERY_VOLUME      0x43
#define CMD_QUERY_FLDR_TRACKS 0x4e
#define CMD_QUERY_TOT_TRACKS  0x48
#define CMD_QUERY_FLDR_COUNT  0x4f

// Opitons
#define DEV_TF            0X02

// Required for LIGHT_SLEEP_T delay mode
extern "C" {
#include "user_interface.h"
}

void setup(void) {

  // Arduino IDE Serial Monitor window to emulate what Arduino Tron sensors are reading
  Serial.begin(115200); // Serial connection from ESP-01 via 3.3v console cable

  // Connect to WiFi network
  Serial.println("Executive Order Corporation - Arduino Tron ESP8266 MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)");
  Serial.println("Arduino Tron Drools-jBPM :: Executive Order Arduino Tron Sensor Processor MQTT AI-IoTBPM Client using AI-IoTBPM Drools-jBPM");
  Serial.println("- Arduino Tron VOX ESP-01 ver " + ver);
  Serial.println("Copyright © 1978, 2021: Executive Order Corporation, All Rights Reserved");

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

  // Start the arduino tron vox
  webserver.begin();
  Serial.println("Arduino Tron VOX ESP-01 started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  Serial.flush(); // MP3 CD Player Module to serial
  delay(500);
  Serial.end();
  Serial.begin(9600); // Initialize serial for MP3 CD Player Module
  delay(500);

  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(500);
}

void loop(void) {
  // Check if a client has connected
  client = webserver.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  // Serial.print("New client connection, loop ");
  // Serial.println(loopCounter);
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
      // Serial.write(c); // print it on the serial monitor
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

          // Display the HTML web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><title>Arduino Tron IoT VOX ESP-01</title>");
          client.println("Arduino Tron VOX AI-IoTBPM :: Internet of Things using AI-IoTBPM Drools-jBPM</head><br>");
          client.println("<body>Loop Counter ");
          client.println(loopCounter);
          client.println("<br><br>");

          char mp3_cmd = ' ';
          String mp3_file = "";
          int8_t mp3_index = 0;

          mp3_cmd = header.charAt(5);

          if (mp3_cmd == 'i') {
            mp3_file = header.substring(6, 8);
            mp3_index = mp3_file.toInt();
          }

          sendMP3Command(mp3_cmd, mp3_index); // If there a char on Serial call sendMP3Command to sendCommand

          delay(1000);
          client.println(decodeMP3Answer());
          client.println("<br>");

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

// Function sendMP3Command: seek for a 'c' command and send it to MP3
// Parameter: c. Code for the MP3 Command, 'h' for help.
// Return: void
void sendMP3Command(char c, int8_t mp3_index) {
  switch (c) {
    case '?':
    case 'h':
      client.println("HELP<br>");
      client.println(" p = Play<br>");
      client.println(" P = Pause<br>");
      client.println(" > = Next<br>");
      client.println(" < = Previous<br>");
      client.println(" + = Volume UP<br>");
      client.println(" - = Volume DOWN<br>");
      client.println(" c = Query current file<br>");
      client.println(" q = Query status<br>");
      client.println(" v = Query volume<br>");
      client.println(" x = Query folder count<br>");
      client.println(" t = Query total file count<br>");
      client.println(" i = Play index xx<br>");
      client.println(" 1 = Play folder 1, play file 1<br>");
      client.println(" 2 = Play folder 2<br>");
      client.println(" 3 = Play index 0x0001<br>");
      client.println(" S = Sleep<br>");
      client.println(" W = Wake up<br>");
      client.println(" r = Reset<br>");
      break;

    case 'p':
      client.println("Play");
      sendCommand(CMD_PLAY, 0);
      break;

    case 'P':
      client.println("Pause");
      sendCommand(CMD_PAUSE, 0);
      break;

    case '>':
      client.println("Next");
      sendCommand(CMD_NEXT_SONG, 0);
      sendCommand(CMD_PLAYING_N, 0x0000); // ask for the number of file is playing
      break;

    case '<':
      client.println("Previous");
      sendCommand(CMD_PREV_SONG, 0);
      sendCommand(CMD_PLAYING_N, 0x0000); // ask for the number of file is playing
      break;

    case '+':
      client.println("Volume Up");
      sendCommand(CMD_VOLUME_UP, 0);
      break;

    case '-':
      client.println("Volume Down");
      sendCommand(CMD_VOLUME_DOWN, 0);
      break;

    case 'c':
      client.println("Query current file");
      sendCommand(CMD_PLAYING_N, 0);
      break;

    case 'q':
      client.println("Query status");
      sendCommand(CMD_QUERY_STATUS, 0);
      break;

    case 'v':
      client.println("Query volume");
      sendCommand(CMD_QUERY_VOLUME, 0);
      break;

    case 'x':
      client.println("Query folder count");
      sendCommand(CMD_QUERY_FLDR_COUNT, 0);
      break;

    case 't':
      client.println("Query total file count");
      sendCommand(CMD_QUERY_TOT_TRACKS, 0);
      break;

    case 'i':
      client.println("Play index");
      sendCommand(CMD_PLAY_W_INDEX, mp3_index);
      break;

    case '1':
      client.println("Play folder file 0x0101");
      sendCommand(CMD_PLAY_FOLDER_FILE, 0x0101);
      break;

    case '2':
      client.println("Play folder 2");
      sendCommand(CMD_FOLDER_CYCLE, 0x0201);
      break;

    case '3':
      client.println("CMD_PLAY_W_INDEX 0x0001");
      sendCommand(CMD_PLAY_W_INDEX, 0x0001);
      break;

    case 'S':
      client.println("Sleep");
      sendCommand(CMD_SLEEP_MODE, 0x00);
      break;

    case 'W':
      client.println("Wake up");
      sendCommand(CMD_WAKE_UP, 0x00);
      break;

    case 'r':
      client.println("Reset");
      sendCommand(CMD_RESET, 0x00);
      break;
  }
}

// Function decodeMP3Answer: Decode MP3 answer.
// Parameter:-void
// Return: decodedMP3Answer
String decodeMP3Answer() {
  String decodedMP3Answer = "";

  decodedMP3Answer += sanswer();

  switch (ansbuf[4]) { // was 3
    case 0x3A:
      decodedMP3Answer += " -> Memory card inserted.";
      break;

    case 0x3D:
      decodedMP3Answer += " -> Completed play num " + String(ansbuf[7], DEC); // was 6
      break;

    case 0x40:
      decodedMP3Answer += " -> Error";
      break;

    case 0x41:
      decodedMP3Answer += " -> Data recived correctly. ";
      break;

    case 0x42:
      decodedMP3Answer += " -> Status playing: " + String(ansbuf[7], DEC);
      break;

    case 0x48:
      decodedMP3Answer += " -> File count: " + String(ansbuf[7], DEC);
      break;

    case 0x4C:
      decodedMP3Answer += " -> Playing: " + String(ansbuf[7], DEC);
      break;

    case 0x4E:
      decodedMP3Answer += " -> Folder file count: " + String(ansbuf[7], DEC);
      break;

    case 0x4F:
      decodedMP3Answer += " -> Folder count: " + String(ansbuf[7], DEC);
      break;
  }
  return decodedMP3Answer;
}

// Function: Send command to the MP3
// Parameter:-int8_t command
// Parameter:-int16_ dat  parameter for the command
void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e;   //
  Send_buf[1] = 0xff;   //
  Send_buf[2] = 0x06;   // Len
  Send_buf[3] = command;//
  Send_buf[4] = 0x01;   // 0x00 NO, 0x01 feedback
  Send_buf[5] = (int8_t)(dat >> 8);  //datah
  Send_buf[6] = (int8_t)(dat);       //datal
  Send_buf[7] = 0xef;   //
  client.print("Sending: ");
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.write(Send_buf[i]) ;
    client.print(sbyte2hex(Send_buf[i]));
  }
  client.println("<br>");
}

// Function: sbyte2hex. Returns a byte data in HEX format.
// Parameter:- uint8_t b. Byte to convert to HEX.
// Return: String
String sbyte2hex(uint8_t b)
{
  String shex;

  shex = "0X";

  if (b < 16) shex += "0";
  shex += String(b, HEX);
  shex += " ";
  return shex;
}

// Function: sanswer. Returns a String answer from mp3 UART module.
// Parameter:- uint8_t b. void.
// Return: String. If the answer is well formated answer.
String sanswer(void)
{
  uint8_t i = 0;
  String mp3answer = "";

  // Get only 10 Bytes
  while (Serial.available() && (i < 10))
  {
    uint8_t b = Serial.read();
    ansbuf[i] = b;
    i++;

    mp3answer += sbyte2hex(b);
  }

  // if the answer format is correct.
  if ((ansbuf[1] == 0x7E) && (ansbuf[9] == 0xEF))
  {
    return mp3answer;
  }

  return mp3answer; // "???: " + mp3answer;
}
