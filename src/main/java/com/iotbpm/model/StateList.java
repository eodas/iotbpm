package com.iotbpm.model;

import java.util.HashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A helper class to load and return the list of state for jBPM
 */
public class StateList {

	private static StateList STATELIST_INSTANCE = null;

	private Map<String, Object> state = new HashMap<String, Object>();
	// private Hashtable<String, String> state = new Hashtable<String, String>();

	private final Logger logger = LoggerFactory.getLogger(StateList.class);

	public StateList() {
		StateList.STATELIST_INSTANCE = this;
	}

	public static StateList getInstance() {
		return STATELIST_INSTANCE;
	}

	public String getState(String key) {
		for (Object o : state.entrySet()) {
			Map.Entry entry = (Map.Entry) o;
			if (key.indexOf((String) entry.getKey()) != -1) {
				return (String) entry.getValue();
			}
		}
		return "";
	}

	public void putState(String key, String value) {
		state.put(key, value);
	}

	public void delState(String key) {
		Object obj = state.remove(key);
	}

	public Map mapState() {
		return state;
	}
}
