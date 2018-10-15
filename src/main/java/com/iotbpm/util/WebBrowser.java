package com.iotbpm.util;

import java.awt.Desktop;
import java.net.URI;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class WebBrowser {

	private final Logger logger = LoggerFactory.getLogger(WebBrowser.class);

	public static void url_(String url) {
		try {
			Runtime.getRuntime().exec("cmd.exe /c start iexplore -new \"" + url + "\"");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void url(String url) {
		Desktop desktop = null;
		if (Desktop.isDesktopSupported())
			try {
				desktop = Desktop.getDesktop();
				desktop.browse(new URI(url));
			} catch (Exception e) {
				e.printStackTrace();
			}
		else
			url_(url);
	}
}
