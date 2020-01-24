#!/usr/bin/env python
"""
Executive Order Corporation - Raspberry Pi Tron MQTT Telemetry Transport Machine-to-Machine(M2M)/Internet of Things(IoT)
Raspberry Pi Tron Drools-jBPM :: Executive Order Raspberry Pi Tron Sensor AI-IoTBPM Client using AI-IoTBPM Drools-jBPM
Raspberry Pi Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using Raspberry Pi Tron AI-IoTBPM Processing
Executive Order Corporation
Copyright © 1978, 2020: Executive Order Corporation, All Rights Reserved
"""
import time
import serial
# importing the requests library 
import requests

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)  # Open Serial port - COM3,COM11,/dev/ttyACM0,/dev/ttyUSB0

# fix permission problem in Ubuntu /dev/ttyACM0
# sudo su //type password
# cd /
# cd dev
# chown <username> ttyACM0

# Update these with Raspberry Pi Tron service IP address and unique unit id values
URL = "http://10.0.0.2:5055/"  # Set EOSpy server IP address
id = "100111"  # Raspberry Pi Tron Device unique unit id

# Above are all the fields you need to provide values, the remaining fields are used in the RPi Tron application
counter = 10  # Used to serverSendPost HTML every 20s

# $GPGGA GPS Log header
utc = "0"  # UTC time status of position (hours/minutes/seconds/decimal seconds)
# Update these with your LAT/LON GPS position values
# You can find LAT/LON from an address https://www.latlong.net/convert-address-to-lat-long.html
address = "National_Air_Space_Museum_600_Independence_Ave_Washington_DC_20560"
latstr = "38.888160"  # lat Latitude
lngstr = "-77.019868"  # lng Longitude
speed = "0"  # speed Km - Speed over ground, knots
course = "0.00"  # track true - Track made good, degrees True as bearing
altitude = "0"  # altitude Antenna altitude above/below mean sea level
message = "0"  # total number of messages in this transmission
accuracy = "0.0"  # GPS device accuracy
valid = "V"  # data status - Data status: A = Data valid, V = Data invalid
batt = "89.7"  # GPS device batteryLevel
light = "53.4"  # photocell value

# Raspberry Pi Tron currently supports these additional data fields in the Server Event data model:

# id=6&event=allEvents&protocol=osmand&servertime=<date>&timestamp=<date>&fixtime=<date>&outdated=false&valid=true
# &lat=38.85&lon=-84.35&altitude=27.0&speed=0.0&course=0.0&address=<street address>&accuracy=0.0&network=null
# &batteryLevel=78.3&textMessage=Message_Sent&temp=71.2&ir_temp=0.0&humidity=0.0&mbar=79.9
# &accel_x=-0.01&accel_y=-0.07&accel_z=9.79&gyro_x=0.0&gyro_y=-0.0&gyro_z=-0.0&magnet_x=-0.01&magnet_y=-0.07&magnet_z=9.81
# &light=91.0&keypress=0.0&alarm=Temperature&distance=1.6&totalDistance=3.79&motion=false

# You can add more additional fields to the data model and transmit via any device to the Raspberry Pi Tron Drools-jBPM processing

# Values for the DHT11 digital temperature/humidity sensor; &temp= and &humidity= fields
temp = "0.0"
humidity = "0.0"

# Values to send in &textMessage= filed
textMessage = "text_message"

# Values to send in &keypress= field
TYPE_ALLEVENTS = "allEvents"  # allEvents
TYPE_KEYPRESS_1 = "1.0"  # keypress_1
TYPE_KEYPRESS_2 = "2.0"  # keypress_2
TYPE_REED_RELAY = "4.0"  # reedRelay
TYPE_PROXIMITY = "8.0"  # proximity

# Values to send in &alarm= field
alarm = "general"

# Values to send in &alarm= field
ALARM_GENERAL = "general"
ALARM_SOS = "sos"
ALARM_VIBRATION = "vibration"
ALARM_MOVEMENT = "movement"
ALARM_LOW_SPEED = "lowspeed"
ALARM_OVERSPEED = "overspeed"
ALARM_FALL_DOWN = "fallDown"
ALARM_LOW_POWER = "lowPower"
ALARM_LOW_BATTERY = "lowBattery"
ALARM_FAULT = "fault"
ALARM_POWER_OFF = "powerOff"
ALARM_POWER_ON = "powerOn"
ALARM_DOOR = "door"
ALARM_GEOFENCE = "geofence"
ALARM_GEOFENCE_ENTER = "geofenceEnter"
ALARM_GEOFENCE_EXIT = "geofenceExit"
ALARM_GPS_ANTENNA_CUT = "gpsAntennaCut"
ALARM_ACCIDENT = "accident"
ALARM_TOW = "tow"
ALARM_ACCELERATION = "hardAcceleration"
ALARM_BRAKING = "hardBraking"
ALARM_CORNERING = "hardCornering"
ALARM_FATIGUE_DRIVING = "fatigueDriving"
ALARM_POWER_CUT = "powerCut"
ALARM_POWER_RESTORED = "powerRestored"
ALARM_JAMMING = "jamming"
ALARM_TEMPERATURE = "temperature"
ALARM_PARKING = "parking"
ALARM_SHOCK = "shock"
ALARM_BONNET = "bonnet"
ALARM_FOOT_BRAKE = "footBrake"
ALARM_OIL_LEAK = "oilLeak"
ALARM_TAMPERING = "tampering"
ALARM_REMOVING = "removing"


def serverSendPost():
    bvalid = 'false'
    bearing = "0"
    if len(course) == 0:
        bearing = "0.00"

    if valid == "V":
        bvalid = 'true'

    # defining a params dict for the parameters to be sent to the API 
    PARAMS = {'id': id,
              'timestamp': utc,
              'lat': latstr,
              'lon': lngstr,
              'speed': speed,
              'bearing': bearing,
              'altitude': altitude,
              'accuracy': accuracy,
              'valid': bvalid}

    # Raspberry Pi Tron currently supports these additional data fields in the Server Event data model:
    # 'batt': batt,
    # 'temp': temp,
    # 'humidity': humidity,
    # 'keypress': TYPE_KEYPRESS_1
    # 'textMessage: textMessage,
    # 'alarm': ALARM_TEMPERATURE,
    # 'light': light,

    # sending get request and saving the response as response object 
    resp = requests.get(url=URL, params=PARAMS)

    print(">>> Connection Status:", resp.status_code)
    return


def readString():
    while 1:
        while ser.read().decode("utf-8") != '$':  # Wait for the begging of the string
            pass  # Do nothing
        line = ser.readline().decode("utf-8")  # Read the entire string
        return line


def getTime(string, format, returnFormat):
    global utc
    # utc = int(string)
    utc = int(time.time())
    return time.strftime(returnFormat,
                         time.strptime(string, format))  # Convert date and time to a nice printable format


def latitude2Decimal(lat, NS):
    global latstr
    minutes = lat[:2]
    degree = str(float(lat[2:]) * 1.0 / 60.0)
    latitudeDegrees = minutes + "." + degree[2:10]
    if NS == 'S':
        latitudeDegrees = "-" + latitudeDegrees
    latstr = latitudeDegrees
    return latitudeDegrees


def longitude2Decimal(lng, WE):
    global lngstr
    minutes = lng[:3]
    if minutes[0] == "0":
        minutes = minutes[1:]
    degree = str(float(lng[3:]) * 1.0 / 60.0)
    longitudeDegrees = minutes + "." + degree[2:10]
    if WE == 'W':
        longitudeDegrees = "-" + longitudeDegrees
    lngstr = longitudeDegrees
    return longitudeDegrees


# GPRMC - GPS specific information
def printRMC(lines):
    global counter
    global speed
    global course
    print("========================================RMC========================================")
    # print(lines, '\n')

    print("Fix taken at:", getTime(lines[1], "%H%M%S.%f", "%H:%M:%S"), "UTC")
    print("Status (A=OK,V=KO):", lines[2])
    lat = latitude2Decimal(lines[3], lines[4])
    lng = longitude2Decimal(lines[5], lines[6])
    print("Lat,Long: ", lat, lines[4], ", ", lng, lines[6], sep='')
    print("Speed (knots):", lines[7])
    speed = lines[7]
    print("Track angle (deg):", lines[8])
    course = lines[8]
    print("Fix date at:", lines[9])  # "%H%M%S.%f%d%m%y", "%a %b %d %H:%M:%S %Y"), "UTC")
    print("Magnetic variation: ", lines[10], end='')
    if len(
            lines) == 13:  # The returned string will be either 12 or 13 - it will return 13 if NMEA standard used is above 2.3
        print(lines[11])
        print("Mode (A=Autonomous, D=Differential, E=Estimated, N=Data not valid):", lines[12].partition("*")[0])
    else:
        print(lines[11].partition("*")[0])

    counter += 1
    if counter > 20:  # Send serverSendPost HTML every 20s
        counter = 0
        serverSendPost()
    return


# GPGGA - GPS fix data and undulation
def printGGA(lines):
    global altitude
    print("========================================GGA========================================")
    # print(lines, '\n')

    print("Fix taken at:", getTime(lines[1], "%H%M%S.%f", "%H:%M:%S"), "UTC")
    lat = latitude2Decimal(lines[2], lines[3])
    lng = longitude2Decimal(lines[4], lines[5])
    print("Lat,Long: ", lat, lines[3], ", ", lng, lines[5], sep='')
    print("Fix quality (0 = invalid, 1 = fix, 2..8):", lines[6])
    print("Satellites:", lines[7].lstrip("0"))
    print("Horizontal dilution:", lines[8])
    print("Altitude: ", lines[9], lines[10], sep="")
    altitude = lines[9]
    print("Height of geoid: ", lines[11], lines[12], sep="")
    print("Time in seconds since last DGPS update:", lines[13])
    print("DGPS station ID number:", lines[14].partition("*")[0])
    return


# GPGSA - GPS DOP and active satellites
def printGSA(lines):
    print("========================================GSA========================================")
    # print(lines, '\n')

    print("Selection of 2D or 3D fix (A=Auto,M=Manual):", lines[1])
    print("3D fix (1=No fix,2=2D fix, 3=3D fix):", lines[2])
    print("PRNs of satellites used for fix:", end='')
    for i in range(0, 12):
        prn = lines[3 + i].lstrip("0")
        if prn:
            print(" ", prn, end='')
    print("\nPDOP", lines[15])
    print("HDOP", lines[16])
    print("VDOP", lines[17].partition("*")[0])
    return


# GPGSV - GPS satellites in view
def printGSV(lines):
    if lines[2] == '1':  # First sentence
        print("========================================GSV========================================")
    else:
        print("===================================================================================")
    # print(lines, '\n')

    print("Number of sentences:", lines[1])
    print("Sentence:", lines[2])
    print("Satellites in view:", lines[3].lstrip("0"))
    for i in range(0, int(len(lines) / 4) - 1):
        print("Satellite PRN:", lines[4 + i * 4].lstrip("0"))
        print("Elevation (deg):", lines[5 + i * 4].lstrip("0"))
        print("Azimuth (deg):", lines[6 + i * 4].lstrip("0"))
        print("SNR (higher is better):", lines[7 + i * 4].partition("*")[0])
    return


# GPGLL - Geographic position
def printGLL(lines):
    print("========================================GLL========================================")
    # print(lines, '\n')

    lat = latitude2Decimal(lines[1], lines[2])
    lng = longitude2Decimal(lines[3], lines[4])
    print("Lat,Long: ", lat, lines[2], ", ", lng, lines[4], sep='')
    print("Fix taken at:", getTime(lines[5], "%H%M%S.%f", "%H:%M:%S"), "UTC")
    print("Status (A=OK,V=KO):", lines[6])
    if lines[7].partition("*")[0]:  # Extra field since NMEA standard 2.3
        print("Mode (A=Autonomous, D=Differential, E=Estimated, N=Data not valid):", lines[7].partition("*")[0])
    return


# GPVTG - Track made good and ground speed
def printVTG(lines):
    global speed
    global course
    print("========================================VTG========================================")
    # print(lines, '\n')

    print("True Track made good (deg):", lines[1], lines[2])
    course = lines[1]
    print("Magnetic track made good (deg):", lines[3], lines[4])
    print("Ground speed (knots):", lines[5], lines[6])
    print("Ground speed (km/h):", lines[7], lines[8].partition("*")[0])
    speed = lines[7]
    if lines[9].partition("*")[0]:  # Extra field since NMEA standard 2.3
        print("Mode (A=Autonomous, D=Differential, E=Estimated, N=Data not valid):", lines[9].partition("*")[0])
    return


# GPTXT - GPS message transfers various information on the receiver
def printTXT(lines):
    global message
    print("========================================TXT========================================")
    # print(lines, '\n')

    print("Total number of messages:", lines[1])
    print("This Message number:", lines[2])
    print("Text Identifier 00=ERROR 01=WARNING 02=NOTICE 07=USER:", lines[3])
    print("Message text:", lines[4])
    message = message + lines[4]
    if "FFFFFFFF" in lines[4]:
        print(message)
    return


def checksum(line):
    checkString = line.partition("*")
    checksum = 0
    for c in checkString[0]:
        checksum ^= ord(c)

    try:  # Just to make sure
        inputChecksum = int(checkString[2].rstrip(), 16)
    except:
        print("Error in string")
        return False

    if checksum == inputChecksum:
        return True
    else:
        print("=====================================================================================")
        print("===================================Checksum error!===================================")
        print("=====================================================================================")
        print(hex(checksum), "!=", hex(inputChecksum))
        return False


if __name__ == '__main__':
    try:
        while True:
            line = readString()
            lines = line.split(",")
            if checksum(line):
                if lines[0] == "GPRMC":
                    printRMC(lines)
                    pass
                elif lines[0] == "GPGGA":
                    printGGA(lines)
                    pass
                elif lines[0] == "GPGSA":
                    # printGSA(lines)
                    pass
                elif lines[0] == "GPGSV":
                    # printGSV(lines)
                    pass
                elif lines[0] == "GPGLL":
                    printGLL(lines)
                    pass
                elif lines[0] == "GPVTG":
                    printVTG(lines)
                    pass
                elif lines[0] == "GPTXT":
                    printTXT(lines)
                    pass
                else:
                    print("\n\nUnknown type:", lines[0], "\n\n")
    except KeyboardInterrupt:
        print('Exiting Script')
