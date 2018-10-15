package com.iotbpm.events;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.regex.Pattern;

import com.iotbpm.ProcessjBPMRules;
import com.iotbpm.model.ServerEvent;

public class EventReader {

	private BufferedReader in;
	private volatile static boolean shutdown = false;
	private String DateFormatString = "yyy-mm-dd hh:mm:ss";

	ProcessjBPMRules processjBPMRules;
	private String serverEvent;
	private int eventSleepTimer;

	public EventReader(ProcessjBPMRules processjBPMRules, String serverEvent, int eventSleepTimer) {
		this.serverEvent = serverEvent;
		this.eventSleepTimer = eventSleepTimer;
		this.processjBPMRules = processjBPMRules;
		System.out.println("Arduino Tron Drools-jBPM AI-IoTBPM Event Reader, Location: " + serverEvent);
	}

	public void StartEventThread() {
		new Thread(new Runnable() {
			@Override
			public void run() {
				shutdown = false;
				while (!shutdown) {
					if (EventFileExist()) {
						EventFileRead();
						EventFileDelete();
					}
					try {
						Thread.sleep(eventSleepTimer);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}).start();
	}

	public static void shutdownEventThread() {
		shutdown = true;
	}

	public void EventFileDelete() {
		File file = new File(serverEvent);
		if (!file.delete()) {
			System.err.println("ERROR: Failed to delete the file " + serverEvent);
		}
	}

	private Date parseDate(String date, String format) {
		SimpleDateFormat formatter = new SimpleDateFormat(format);
		try {
			return formatter.parse(date);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return null;
	}

	public boolean EventFileExist() {
		File file = new File(serverEvent);
		if (file.exists() && !file.isDirectory()) {
			return true;
		}
		return false;
	}

	public void EventFileRead() {
		try {
			File file = new File(serverEvent);
			in = new BufferedReader(new FileReader(file));

			String line;
			while ((line = in.readLine()) != null) {
				IoTServerEvent(line);
			}

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				in.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public void IoTServerEvent(String request) {
		System.out.println("> EVENT " + request);

		ServerEvent serverEvent = new ServerEvent();
		String[] req = Pattern.compile(" ").split(request);

		if (req[0].equals("GET")) {

			String arg = req[1].substring(req[1].indexOf('?') + 1);
			String[] tokens = arg.split("&");

			for (String token : tokens) {
				try {
					String key = token.substring(0, token.indexOf('='));
					String value = token.substring(token.indexOf('=') + 1);
					serverEvent.add(key, value);

				} catch (IndexOutOfBoundsException e) {
					System.err.println("Error: Unexpected exception caught: " + e.getMessage());
					e.printStackTrace();
				}
			}
			String response = "";
			response = processjBPMRules.receive(serverEvent);
			if ((response != null) && (response.length() > 0)) {
				System.out.println("> EVENT RSP " + response);
			}
		}
	}

}
