package com.iotbpm.model;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A POJO for devices
 */
public class Devices {

	public String id;
	public String name;
	public String action;
	public String status;

	private final Logger logger = LoggerFactory.getLogger(Devices.class);

	public Devices(String name, String id) {
		this(name, id, "", "");
	}

	public Devices(String name, String id, String action, String status) {
		this.id = id;
		this.name = name;
		this.action = action;
		this.status = status;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getAction() {
		return action;
	}

	public void setAction(String action) {
		this.action = action;
	}

	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}
}
