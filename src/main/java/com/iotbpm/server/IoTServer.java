package com.iotbpm.server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.SocketException;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.iotbpm.ProcessjBPMRules;

public class IoTServer extends Thread {
	private int currrentConnections = 0;
	private int maxConnections = 30;

	private int port;
	private boolean alive = true;
	private ProcessjBPMRules processjBPMRules;
	private ServerSocket server = null;

	private final Logger logger = LoggerFactory.getLogger(IoTServer.class);

	public IoTServer(ProcessjBPMRules processjBPMRules, int port) {
		this.port = port;
		this.processjBPMRules = processjBPMRules;
		System.out.println("Arduino Tron Drools-jBPM AI-IoTBPM Server, Started Port: " + port);
	}

	@Override
	public void run() {
		try {
			server = new ServerSocket(port);
			server.setReuseAddress(true);
		} catch (Exception ee) {
			alive = false;
			System.err.println(
					"Error: Port " + port + " is already in use.\n" + "Please select another port for IoT Server.");
		}
		while (alive) {
			if (getConnection() >= maxConnections) {
				System.err.println("Error: Too many connections...");
				while (getConnection() >= maxConnections)
					try {
						Thread.sleep(50L);
					} catch (Exception localException1) {
					}
			}
			if ((alive) && (!server.isClosed())) {
				try {
					new IoTServerThread(server.accept(), this, processjBPMRules);
					incConnection();
				} catch (SocketException localSocketException) {
				} catch (IOException ioe) {
					ioe.printStackTrace();
				}
			}
		}
	}

	public synchronized void incConnection() {
		currrentConnections += 1;
	}

	public synchronized void decConnection() {
		currrentConnections -= 1;
	}

	public synchronized int getConnection() {
		return currrentConnections;
	}

	public void killServer() {
		alive = false;
		System.out.println("Arduino Tron Drools-jBPM AI-IoTBPM Server, Stopped");
		try {
			if (server != null) {
				server.close();
				server = null;
			}
		} catch (Exception e) {
			e.printStackTrace();
			System.err.println("IoT Server kill error: " + e.toString());
		}
	}
}
