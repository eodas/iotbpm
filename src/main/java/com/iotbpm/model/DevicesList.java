package com.iotbpm.model;

import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A helper class to load and return the list of devices
 */
public class DevicesList {

	private Map<String, Devices> devices;

	private final Logger logger = LoggerFactory.getLogger(DevicesList.class);

	public DevicesList() {

		this.devices = new HashMap<String, Devices>();
		
        this.devices.put("100111", new Devices("Arduino Tron IoT", "100111"));
        this.devices.put("100222", new Devices("Temperature Humidity", "100222"));
        this.devices.put("100333", new Devices("IoT-MCU Door Lock", "100333"));
        this.devices.put("100444", new Devices("Arduino IoT-SensorTag", "100444"));
        this.devices.put("100555", new Devices("Arduino Dash Button", "100555"));
        this.devices.put("100666", new Devices("Door Open Sensor ESP01", "100666"));
        this.devices.put("100777", new Devices("IoT-MCU ESP-01 Relay", "100777"));
        this.devices.put("100888", new Devices("Desk OLED SSD Display", "100888"));
	}

	public Collection<Devices> getDevices() {
		return Collections.unmodifiableCollection(devices.values());
	}

	public Devices getDevice(String device) {
		return this.devices.get(device);
	}
}
