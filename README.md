# AI-IoTBPM :: IoT Internet of Things Drools-BPM (Business Process Management) engine for IoT Device Orchestration

![alt tag](http://iotbpm.com/wp-content/uploads/2018/03/preview-42-768x449.jpg "AI-IoTBPM")

Executive Order Corp – AI-IoTBPM server is IoT Internet of Things Drools-BPM (Business Process Management) engine for IoT Device Orchestration and IoT device ontology (AI-IoT device awareness, state of being, knowledge of real-world objects, events, situations, and abstract concepts).
Executive Order Corp - AI-IoTBPM MQTT Telemetry Transport Machine-to-Machine(M2M) / Internet of Things (IoT)
AI-IoTBPM :: Executive Order AI-IoTBPM Tron Sensor Processor MQTT AI-IoTBPM Client using EOSpy AI-IoTBPM Drools-jBPM

The power of the IoT (Internet of Things) device increases greatly when business process (jBPM) can use them to provide information
about our real-world as well as execute IoT devices as part of our business process. The jBPM-BPMN modular allow us to define 
both the business processes and IoT devices behavior at the same time using one diagram. With Arduino Tron adding Drools-jBPM to IoT,
we make the IoT devices "smart". Moving beyond just collecting IoT data and transitioning, to leveraging the new wealth of IoT data, 
to improving the SMART decision making is the key. The Executive Order Arduino Tron AI-IoTBPM will help these IoT devices, environments, 
and products to self-monitor, self-diagnose and eventually, self-direct.

Arduino Tron allows you to send IoT sensor data and information directly to the AI-IoTBPM Drools-jBPM Expert System from the Arduino device.
This provides a very lite streamline IoT to Drools-jBPM (Business Process Management) application process with sensor and GPS positioning information.
Executive Order Arduino Tron - This quick guide will help you install and configure the Arduino Tron - Executive Order Sensor Processor System components.

Executive Order Arduino Tron has several components:
1. The Arduino Tron AI-IoTBPM (Java), the Internet of Things Drools-jBPM Expert System for controlling the IoT devices.
2. The Arduino Tron (Arduino Sensor), the MQTT Telemetry Transport application to send sensor and environment information.
3. The Arduino Tron Agent (Arduino), the software to control external Arduino connected IoT devices that perform action in our world.
4. The Arduino Tron Web Server (Arduino), the lightweight Web Server is an interface for controlling IoT Internet-connected devices.

You can have an unlimited number and combination of Arduino Tron IoT Devices and/or EOSPY GPS Client tracking devices in use with Arduino Tron AI-IoTBPM.
(Optionally, download EOSPY server from our website http://www.eospy.com and Download EOSPY GPS client from the Google Store, standard or TI-SensorTag version.)

(1) Arduino Tron AI-IoTBPM - To install the Arduino Tron AI-IoTBPM program on your windows computer, download and install the "Eclipse IDE for Java Developers."
Use the Eclipse feature to add new software, available on the Eclipse menu "Help -> Install New Software". Select the "Add" option and install these packages:
1. Drools + jBPM Update Site 7.43.0 - http://downloads.jboss.org/jbpm/release/7.43.0.Final/updatesite/
2. BPMN2-Modeler 1.5.1 - http://download.eclipse.org/bpmn2-modeler/updates/photon/1.5.1/
3. GIT the Arduino Tron from the source code repository, and Import Existing Maven project.

(2) Arduino Tron Sensor - To install the Arduino Tron application on your Arduino device, download the Arduino Tron Sensor application from GIT.
Update the with WiFi network values for network SSID (name) and network password. Update the Arduino Tron Sensor IP address and unique unit ID values.
Also, you may use a DHT11 digital temperature and humidity sensor, or other sensors (see the Arduino Tron Sensor sketch for more details and information).

Arduino Tron IoT (Sensor Emulator) - Prototype an Arduino-based low-power WiFi Internet of Things (IoT) device with built-in sensors emulation that could be used to
deliver sensor data from any location in the world, and potentially control connected devices such as thermostats, lights, door locks, and other automation products.
Use a serial monitor to emulate sensor input values to Arduino Tron. This will allow you to prototype the final IoT device before custom-designing PCB-printed circuit board.

(3) Arduino Tron Agent - To install the Arduino Tron application on your Arduino Device, download the Arduino Tron Agent application from GIT.
The Arduino Tron Agent AI-IoTBPM software interface allows you to send commands with the Arduino Tron AI-IoTBPM software to control external Arduino connected devices.
The AI-IoTBPM Arduino Tron Agent software uses a WiFi wireless transceiver interface to control and interact with module sensors and remote controls devices. You can 
control any device form the Arduino Tron AI-IoTBPM software or stream any interface over the WiFi Internet. With the Arduino Tron AI-IoTBPM Arduino Tron Agent software
you can automatically turn on lights, appliances, cameras, and open doors from the Drools-jBPM Expert System processing model.

(4) Arduino Tron Web Server provides an IoT dashboard, management and control for remote manage of your Internet-Enabled IoT devices. The Arduino Tron lightweight 
Web Server operates completely on an Arduino ESP-01, integrated low power 32-bit CPU RISC processor, on chip memory and integrated WiFi 802.11 b/g/n. The ESP-01 
Arduino Tron smart micro device is about the size of a quarter and costs around $1.50 per unit. The beauty of the Arduino Tron Web Server is that the IoT device 
technology becomes interactive with humans. With the Arduino Tron Web Server getting your IoT project working in the cloud is a fast-easy solution.

[] The Arduino Tron AI-IoTBPM Drools-jBPM Expert System provides sophisticated jBPM and drools processing. i.e. On a monitoring application, take an action if the temperature 
on the server room increases X degrees in Y minutes, where sensor readings are usually denoted by events example drools.drl file:

<pre><code>
declare TemperatureThreshold 
        windowTime : String = "30s" 
        max : long = 70 
end 

declare SensorReading 
        @role( event ) 
        temperature : String = "40" 
end 

rule "Sound the alarm in case temperature rises above threshold" 
when 
   TemperatureThreshold( $max : max, $windowTime : windowTime ) 
   Number( doubleValue > $max ) from accumulate( 
   SensorReading( $temp : temperature ) over window:time( $windowTime ), 
   average( $temp ) ) 
then 
   // sound the alarm 
end 
</code></pre>

For testing messages syntax to the IoTBPM server, use the cURL command line tool for transferring data specified with URL. Read the curl MANUAL document for command syntax, and how to install Curl. <pre><code> \curl\bin\curl -X GET "http://localhost:5055/?id=100111&timestamp=1521212240&event=keypress1.0&protocol=osmand&outdated=false&valid=true&textMessage=Message_Sent&light=91.0&alarm=Temperature&motion=false" -H "accept: application/xml"
</code></pre>

- Executive Order Corporation
- Copyright - 1978, 2021: Executive Order Corporation, All Rights Reserved
