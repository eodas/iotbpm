package com.iotbpm.model;

import java.util.HashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * An event informing of a state change due to some operation
 */
public class DeviceEvent {

	private final Logger logger = LoggerFactory.getLogger(DeviceEvent.class);

	public Map<String, String> map = new HashMap<>();

	public String id;
	public String name;
	public String event;
	public String session;
	public String protocol;
	public String serverTime;
	public String deviceTime;
	public String fixTime;
	public boolean outdated;
	public boolean valid;
	public double lat;
	public double lon;
	public double altitude; // value in meters
	public double speed; // value in knots
	public double course;
	public String address;
	public double accuracy;
	public double bearing;
	public String network;

	public double batteryLevel;
	public String textMessage;
	public double temp;
	public double ir_temp;
	public double humidity;
	public double mbar;
	public double accel_x;
	public double accel_y;
	public double accel_z;
	public double gyro_x;
	public double gyro_y;
	public double gyro_z;
	public double magnet_x;
	public double magnet_y;
	public double magnet_z;
	public double light;
	public double keypress;
	public String alarm;
	public double distance;
	public double totalDistance;
	public double agentCount;
	public boolean motion;

	public DeviceEvent() {
	}

	public void add(String key, String value) {
		map.put(key, value);
		EventParser(key, value);
	}

	public int mapSize() {
		return map.size();
	}

	// Clear all values.
	public void mapClear() {
		map.clear();
	}

	public String search(String searchKey) {
		if (map.containsKey(searchKey)) {
			return map.get(searchKey);
		} else {
			return "";
		}
	}

	// Iterate over objects, using the keySet method.
	public void iterate() {
		for (String key : map.keySet())
			System.out.println(key + " - " + map.get(key));
		System.out.println();
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getEvent() {
		return event;
	}

	public void setEvent(String event) {
		this.event = event;
	}

	public String getSession() {
		return session;
	}

	public void setSession(String session) {
		this.session = session;
	}

	public String getProtocol() {
		return protocol;
	}

	public void setProtocol(String protocol) {
		this.protocol = protocol;
	}

	public String getServerTime() {
		return serverTime;
	}

	public void setServerTime(String serverTime) {
		this.serverTime = serverTime;
	}

	public String getDeviceTime() {
		return deviceTime;
	}

	public void setDeviceTime(String deviceTime) {
		this.deviceTime = deviceTime;
	}

	public String getFixTime() {
		return fixTime;
	}

	public void setFixTime(String fixTime) {
		this.fixTime = fixTime;
	}

	public boolean isOutdated() {
		return outdated;
	}

	public void setOutdated(boolean outdated) {
		this.outdated = outdated;
	}

	public boolean isValid() {
		return valid;
	}

	public void setValid(boolean valid) {
		this.valid = valid;
	}

	public double getLat() {
		return lat;
	}

	public void setLat(double lat) {
		this.lat = lat;
	}

	public double getLon() {
		return lon;
	}

	public void setLon(double lon) {
		this.lon = lon;
	}

	public double getAltitude() {
		return altitude;
	}

	public void setAltitude(double altitude) {
		this.altitude = altitude;
	}

	public double getSpeed() {
		return speed;
	}

	public void setSpeed(double speed) {
		this.speed = speed;
	}

	public double getCourse() {
		return course;
	}

	public void setCourse(double course) {
		this.course = course;
	}

	public String getAddress() {
		return address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

	public double getAccuracy() {
		return accuracy;
	}

	public void setAccuracy(double accuracy) {
		this.accuracy = accuracy;
	}

	public double getBearing() {
		return bearing;
	}

	public void setBearing(double bearing) {
		this.bearing = bearing;
	}

	public String getNetwork() {
		return network;
	}

	public void setNetwork(String network) {
		this.network = network;
	}

	public double getBatteryLevel() {
		return batteryLevel;
	}

	public void setBatteryLevel(double batteryLevel) {
		this.batteryLevel = batteryLevel;
	}

	public String getTextMessage() {
		return textMessage;
	}

	public void setTextMessage(String textMessage) {
		this.textMessage = textMessage;
	}

	public double getTemp() {
		return temp;
	}

	public void setTemp(double temp) {
		this.temp = temp;
	}

	public double getIr_temp() {
		return ir_temp;
	}

	public void setIr_temp(double ir_temp) {
		this.ir_temp = ir_temp;
	}

	public double getHumidity() {
		return humidity;
	}

	public void setHumidity(double humidity) {
		this.humidity = humidity;
	}

	public double getMbar() {
		return mbar;
	}

	public void setMbar(double mbar) {
		this.mbar = mbar;
	}

	public double getAccel_x() {
		return accel_x;
	}

	public void setAccel_x(double accel_x) {
		this.accel_x = accel_x;
	}

	public double getAccel_y() {
		return accel_y;
	}

	public void setAccel_y(double accel_y) {
		this.accel_y = accel_y;
	}

	public double getAccel_z() {
		return accel_z;
	}

	public void setAccel_z(double accel_z) {
		this.accel_z = accel_z;
	}

	public double getGyro_x() {
		return gyro_x;
	}

	public void setGyro_x(double gyro_x) {
		this.gyro_x = gyro_x;
	}

	public double getGyro_y() {
		return gyro_y;
	}

	public void setGyro_y(double gyro_y) {
		this.gyro_y = gyro_y;
	}

	public double getGyro_z() {
		return gyro_z;
	}

	public void setGyro_z(double gyro_z) {
		this.gyro_z = gyro_z;
	}

	public double getMagnet_x() {
		return magnet_x;
	}

	public void setMagnet_x(double magnet_x) {
		this.magnet_x = magnet_x;
	}

	public double getMagnet_y() {
		return magnet_y;
	}

	public void setMagnet_y(double magnet_y) {
		this.magnet_y = magnet_y;
	}

	public double getMagnet_z() {
		return magnet_z;
	}

	public void setMagnet_z(double magnet_z) {
		this.magnet_z = magnet_z;
	}

	public double getLight() {
		return light;
	}

	public void setLight(double light) {
		this.light = light;
	}

	public double getKeypress() {
		return keypress;
	}

	public void setKeypress(double keypress) {
		this.keypress = keypress;
	}

	public String getAlarm() {
		return alarm;
	}

	public void setAlarm(String alarm) {
		this.alarm = alarm;
	}

	public double getDistance() {
		return distance;
	}

	public void setDistance(double distance) {
		this.distance = distance;
	}

	public double getTotalDistance() {
		return totalDistance;
	}

	public void setTotalDistance(double totalDistance) {
		this.totalDistance = totalDistance;
	}

	public double getAgentCount() {
		return agentCount;
	}

	public void setAgentCount(double agentCount) {
		this.agentCount = agentCount;
	}

	public boolean isMotion() {
		return motion;
	}

	public void setMotion(boolean motion) {
		this.motion = motion;
	}

	public void EventParser(String key, String value) {
		switch (key) {
		case "id":
			setId(value);
			break;
		case "name":
			setName(value);
			break;
		case "event":
			setEvent(value);
			break;
		case "session":
			setSession(value);
			break;
		case "protocol":
			setProtocol(value);
			break;
		case "servertime":
			setServerTime(parseDate(value));
			break;
		case "timestamp":
			setDeviceTime(parseDate(value));
			break;
		case "fixtime":
			setFixTime(parseDate(value));
			break;
		case "outdated":
			setOutdated(Boolean.parseBoolean(value));
			break;
		case "valid":
			setValid(Boolean.parseBoolean(value));
			break;
		case "lat":
			setLat(Double.parseDouble(value));
			break;
		case "lon":
			setLon(Double.parseDouble(value));
			break;
		case "altitude":
			setAltitude(Double.parseDouble(value));
			break;
		case "speed":
			setSpeed(Double.parseDouble(value));
			break;
		case "course":
			setCourse(Double.parseDouble(value));
			break;
		case "address":
			setAddress(value);
			break;
		case "accuracy":
			setAccuracy(Double.parseDouble(value));
			break;
		case "bearing":
			setBearing(Double.parseDouble(value));
			break;
		case "network":
			setNetwork(value);
			break;
		case "batteryLevel":
		case "batt":
			setBatteryLevel(Double.parseDouble(value));
			break;
		case "textMessage":
			setTextMessage(value);
			break;
		case "temp":
			setTemp(Double.parseDouble(value));
			break;
		case "ir_temp":
			setIr_temp(Double.parseDouble(value));
			break;
		case "humidity":
			setHumidity(Double.parseDouble(value));
			break;
		case "mbar":
			setMbar(Double.parseDouble(value));
			break;
		case "accel_x":
			setAccel_x(Double.parseDouble(value));
			break;
		case "accel_y":
			setAccel_y(Double.parseDouble(value));
			break;
		case "accel_z":
			setAccel_z(Double.parseDouble(value));
			break;
		case "gyro_x":
			setGyro_x(Double.parseDouble(value));
			break;
		case "gyro_y":
			setGyro_y(Double.parseDouble(value));
			break;
		case "gyro_z":
			setGyro_z(Double.parseDouble(value));
			break;
		case "magnet_x":
			setMagnet_x(Double.parseDouble(value));
			break;
		case "magnet_y":
			setMagnet_y(Double.parseDouble(value));
			break;
		case "magnet_z":
			setMagnet_z(Double.parseDouble(value));
			break;
		case "light":
			setLight(Double.parseDouble(value));
			break;
		case "keypress":
			setKeypress(Double.parseDouble(value));
			break;
		case "alarm":
			setAlarm(value);
			break;
		case "distance":
			setDistance(Double.parseDouble(value));
			break;
		case "totalDistance":
			setTotalDistance(Double.parseDouble(value));
			break;
		case "agentCount":
			setAgentCount(Double.parseDouble(value));
			break;
		case "motion":
			setMotion(Boolean.parseBoolean(value));
			break;
		default:
			System.out.println("> Extended Event Token " + key + "=" + value);
		}
	}

	private String parseDate(String date) {
		long ldate = Long.parseLong(date);
		String sdate = new java.text.SimpleDateFormat("MM/dd/yyyy HH:mm:ss").format(new java.util.Date(ldate * 1000));
		return sdate;
	}

	@Override
	public String toString() {
		String s = name + " - " + event;
		if (alarm != null && !alarm.isEmpty()) {
			return s = s + " - " + alarm;
		}
		if (textMessage != null && !textMessage.isEmpty()) {
			return s = s + " - " + textMessage;
		}
		return s;
	}
}
