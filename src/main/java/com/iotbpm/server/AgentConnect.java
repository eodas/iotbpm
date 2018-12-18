package com.iotbpm.server;

import java.io.IOException;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;

import java.net.URL;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.iotbpm.model.AgentsList;

import java.net.HttpURLConnection;
import java.net.MalformedURLException;

public class AgentConnect {

	private AgentsList agentsList;
	private String knowledgeDebug = "none";
	private final String USER_AGENT = "Mozilla/5.0";
	private static AgentConnect AGENTCONNECT_INSTANCE = null;

	private final Logger logger = LoggerFactory.getLogger(AgentConnect.class);

	public AgentConnect(AgentsList agentsList, String knowledgeDebug) {
		this.agentsList = agentsList;
		this.knowledgeDebug = knowledgeDebug;
		AgentConnect.AGENTCONNECT_INSTANCE = this;
	}

	public static AgentConnect getInstance() {
		return AGENTCONNECT_INSTANCE;
	}

	// HTTP GET request
	public void sendGet(String agentName, String command) {
		String agentIP = agentsList.getAgent(agentName);
		if (agentIP == "") {
			System.err.println("Error no " + agentName + ": Send Arduino Command no arduinoAgent=[AgentName,http://10.0.0.2,...] "
					+ "defined in iotbpm.properties file.");
			return;
		}

		String urlString = agentIP + command;
		try {
			URL url = new URL(urlString);
			HttpURLConnection con = (HttpURLConnection) url.openConnection();

			// By default it is GET request
			con.setRequestMethod("GET");

			// add request header
			con.setRequestProperty("User-Agent", USER_AGENT);

			int responseCode = con.getResponseCode();
			System.out.println("Send GET request: " + url);
			System.out.println("Response code: " + responseCode);

			// Reading response from input Stream
			BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
			StringBuffer response = new StringBuffer();
			String output;

			while ((output = in.readLine()) != null) {
				response.append(output);
			}
			in.close();

			// printing result from response
			System.out.println(response.toString());
		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	// HTTP Post request
	public void sendPost(String agentName, String command) {
		String agentIP = agentsList.getAgent(agentName);
		if (agentIP == "") {
			System.err.println("Error no " + agentName + ": Send Arduino Command no arduinoAgent=[AgentName,http://10.0.0.2,...] "
					+ "defined in iotbpm.properties file.");
			return;
		}

		String url = agentIP + command;
		try {
			URL obj = new URL(url);
			HttpURLConnection con = (HttpURLConnection) obj.openConnection();

			// Setting basic post request
			con.setRequestMethod("POST");
			con.setRequestProperty("User-Agent", USER_AGENT);
			con.setRequestProperty("Accept-Language", "en-US,en;q=0.5");
			con.setRequestProperty("Content-Type", "application/json");

			String postJsonData = "AI-IoTBPMbpm";

			// Send post request
			con.setDoOutput(true);
			DataOutputStream wr = new DataOutputStream(con.getOutputStream());
			wr.writeBytes(postJsonData);
			wr.flush();
			wr.close();

			int responseCode = con.getResponseCode();
			if (knowledgeDebug.indexOf("none") == -1) {
				System.out.println("Send 'POST' request to URL: " + url);
				System.out.println("Post Data: " + postJsonData);
				System.out.println("Response Code: " + responseCode);
			}

			BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
			StringBuffer response = new StringBuffer();
			String output;

			while ((output = in.readLine()) != null) {
				response.append(output);
			}
			in.close();

			// printing result from response
			if (knowledgeDebug.indexOf("none") == -1) {
				System.out.println(response.toString());
			}
		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
