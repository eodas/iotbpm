package com.iotbpm.model;

import java.util.Hashtable;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A helper class to load and return the list of agents
 */
public class AgentsList {

	private Hashtable<String, String> agents = new Hashtable<String, String>();

	private final Logger logger = LoggerFactory.getLogger(DevicesList.class);

	public AgentsList() {
	}

	public void parseAgents(String agentsList) {
		String agentName = "";
		String ipAddress = "";
		String[] values = agentsList.split(",");
		for (String token : values) {
			if (agentName == "") {
				agentName = token;
			} else {
				ipAddress = token;
				putAgent(agentName, ipAddress);
				agentName = "";
				ipAddress = "";
			}
		}
	}

	public String getAgent(String agentName) {
		for (Object o : agents.entrySet()) {
			Map.Entry entry = (Map.Entry) o;
			if (agentName.indexOf((String) entry.getKey()) != -1) {
				return (String) entry.getValue();
			}
		}
		return "";
	}

	public void putAgent(String agentName, String ipAddress) {
		agents.put(agentName, ipAddress);
	}
}
