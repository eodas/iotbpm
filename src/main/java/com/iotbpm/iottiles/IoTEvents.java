package com.iotbpm.iottiles;

import java.util.regex.Pattern;
import com.iotbpm.bpmrules.jBPMRules;
import com.iotbpm.model.DeviceEvent;

public class IoTEvents {
	jBPMRules jbpmRules;

	public IoTEvents(jBPMRules jbpmRules) {
		this.jbpmRules = jbpmRules;
	}

	public void IoTDeviceEvent(String request) {
		System.out.println("> EVENT " + request);

		DeviceEvent deviceEvent = new DeviceEvent();
		String[] req = Pattern.compile(" ").split(request);

		if (req[0].equals("GET")) {

			String arg = req[1].substring(req[1].indexOf('?') + 1);
			String[] tokens = arg.split("&");

			for (String token : tokens) {
				try {
					String key = token.substring(0, token.indexOf('='));
					String value = token.substring(token.indexOf('=') + 1);
					deviceEvent.add(key, value);

				} catch (IndexOutOfBoundsException e) {
					System.err.println("Error: Unexpected exception caught: " + e.getMessage());
					e.printStackTrace();
				}
			}
			String response = "";
			response = jbpmRules.receive(deviceEvent);
			if ((response != null) && (response.length() > 0)) {
				System.out.println("> RESPONSE " + response);
			}
		}
	}
}
