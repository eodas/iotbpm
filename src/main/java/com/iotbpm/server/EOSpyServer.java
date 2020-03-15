package com.iotbpm.server;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.iotbpm.bpmrules.jBPMRules;
import com.iotbpm.model.DeviceEvent;

public class EOSpyServer extends Thread {
	private int totalReads = 0; // Total number of reads

	private String EOSpyFile;
	private String response;
	private boolean alive = true;
	private jBPMRules jbpmRules;

	private final Logger logger = LoggerFactory.getLogger(EOSpyServer.class);

	public EOSpyServer(jBPMRules jbpmRules, String EOSpyFile) {
		this.EOSpyFile = EOSpyFile;
		this.jbpmRules = jbpmRules;
		System.out.println("Arduino Tron Drools-jBPM AI-IoTBPM Server, EOSpy Started Location: " + EOSpyFile);
	}

	@Override
	public void run() {
		while (alive) {
			File file = new File(EOSpyFile);
			boolean exists = file.exists();
			long start = System.currentTimeMillis();

			if (exists == true) {
				response = "";
				incTotalReads();

				try {
					BufferedReader reader = new BufferedReader(new FileReader(EOSpyFile));
					String request = reader.readLine();
					while (request != null) {

						System.out.println("> TRACE " + request);
						DeviceEvent deviceEvent = new DeviceEvent();
						String[] tokens = request.split("&");

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
						response = jbpmRules.receive(deviceEvent);
						if ((response != null) && (response.length() > 0)) {
							System.out.println("> TRACE RSP " + response);
						}
						// read next line
						request = reader.readLine();
					}

					reader.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
				file.delete();
			}

			try {
				Thread.sleep(3000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public synchronized void incTotalReads() {
		totalReads += 1;
	}

	public synchronized void decTotalReads() {
		totalReads -= 1;
	}

	public void killServer() {
		alive = false;
		System.out.println("Arduino Tron Drools-jBPM AI-IoTBPM Server EOSpy, Stopped");
		try {
			// server = null;
		} catch (Exception e) {
			e.printStackTrace();
			System.err.println("IoT Server kill error: " + e.toString());
		}
	}
}
