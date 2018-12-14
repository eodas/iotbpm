package com.iotbpm.ui;

import java.util.Collection;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

import com.iotbpm.bpmrules.IoTBPM;
import com.iotbpm.iottiles.IoTEvents;
import com.iotbpm.model.Devices;
import com.iotbpm.model.ServerEvent;
import com.iotbpm.util.WebBrowser;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JSeparator;
import javax.swing.WindowConstants;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.awt.event.ActionEvent;

/**
 * Main window implementation for the Arduino Tron AI-IoTBPM example
 */
public class MainWindow {

	private final JFrame frame;
	private final Map<String, DevicePanel> devices;
	private final LogPanel logPanel;
	private final ScrollingBanner banner;
	private static MainWindow MAINWINDOW_INSTANCE = null;

	private final Logger logger = LoggerFactory.getLogger(MainWindow.class);

	public MainWindow(final Collection<Devices> devices, boolean exitOnClose) {
		this.logPanel = new LogPanel();
		this.banner = new ScrollingBanner();
		this.devices = new HashMap<String, DevicePanel>();
		this.frame = buildFrame(devices, exitOnClose);
		MainWindow.MAINWINDOW_INSTANCE = this;
	}

	public static MainWindow getInstance() {
		return MAINWINDOW_INSTANCE;
	}

	private JFrame buildFrame(final Collection<Devices> devices, boolean exitOnClose) {
		JPanel contentPanel = new JPanel(new BorderLayout());

		JPanel devicesListPanel = new JPanel(new GridLayout(0, 2));

		for (Devices device : devices) {
			DevicePanel panel = new DevicePanel(device);
			this.devices.put(device.getId(), panel);
			devicesListPanel.add(panel);
		}
		contentPanel.add(devicesListPanel, BorderLayout.WEST);
		contentPanel.add(logPanel, BorderLayout.CENTER);
		contentPanel.add(banner, BorderLayout.SOUTH);

		JFrame frame = new JFrame();

		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);

		JMenu mnFileMenu = new JMenu("File");
		menuBar.add(mnFileMenu);

		JMenuItem mntmProperties = new JMenuItem("Arduino Tron Properties");
		mntmProperties.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				iotbpmPropertiesInformation(e);
			}
		});
		mnFileMenu.add(mntmProperties);

		JMenuItem mntmClearLog = new JMenuItem("Clear Log Panel");
		mntmClearLog.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				logPanel.logClear();
			}
		});
		mnFileMenu.add(mntmClearLog);

		JSeparator separator_1 = new JSeparator();
		mnFileMenu.add(separator_1);

		JMenuItem mntmExitIotBPM = new JMenuItem("Exit Arduino Tron AI-IoTBPM");
		mntmExitIotBPM.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				IoTBPM.stopIoTServer();
				System.exit(0);
			}
		});
		mnFileMenu.add(mntmExitIotBPM);

		JMenu mnArduinoMenu = new JMenu("Arduino");
		menuBar.add(mnArduinoMenu);

		JMenuItem mntmCommand = new JMenuItem("Send Arduino Command");
		mntmCommand.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				sendArduinoCommand(e);
			}
		});
		mnArduinoMenu.add(mntmCommand);

		JMenuItem mntmServerStatus = new JMenuItem("Arduino Tron Server Status");
		mntmServerStatus.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				getArduinoServerStatus(e);
			}
		});
		JSeparator separator_2 = new JSeparator();
		mnArduinoMenu.add(separator_2);
		mnArduinoMenu.add(mntmServerStatus);

		JMenuItem mntmServerUpdate = new JMenuItem("Arduino Tron Server Update");
		mntmServerUpdate.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				getArduinoServerUpdate(e);
			}
		});
		mnArduinoMenu.add(mntmServerUpdate);

		JMenu mnHelpMenu = new JMenu("Help");
		menuBar.add(mnHelpMenu);

		JMenuItem mntmHelpContents = new JMenuItem("Help Contents");
		mntmHelpContents.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				helpContentsAction(e);
			}
		});
		mnHelpMenu.add(mntmHelpContents);

		JSeparator separator_3 = new JSeparator();
		mnHelpMenu.add(separator_3);

		JMenuItem mntmAboutIoTBPM = new JMenuItem("About Arduino Tron");
		mntmAboutIoTBPM.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				aboutIoTBPMAction(e);
			}
		});
		mnHelpMenu.add(mntmAboutIoTBPM);
		frame.setContentPane(contentPanel);

		frame.setDefaultCloseOperation(exitOnClose ? JFrame.EXIT_ON_CLOSE : WindowConstants.DISPOSE_ON_CLOSE);
		frame.setTitle("Arduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using Arduino Tron AI-IoTBPM Processing");
		// frame.setBounds(100, 100, 630, 330);
		frame.pack();
		frame.setLocationRelativeTo(null); // Center in screen

		Thread bannerThread = new Thread(banner);
		bannerThread.setPriority(bannerThread.getPriority() - 1);
		bannerThread.start();

		return frame;
	}

	void iotbpmPropertiesInformation(ActionEvent e) {
		String Properties = "iotbpm.properties file:\n";
		try {
			File file = new File("iotbpm.properties");
			FileInputStream fileInput = new FileInputStream(file);
			Properties properties = new Properties();
			properties.load(fileInput);
			fileInput.close();

			Enumeration<?> enuKeys = properties.keys();
			while (enuKeys.hasMoreElements()) {
				String key = (String) enuKeys.nextElement();
				String value = properties.getProperty(key);
				if (key.indexOf("#") == -1) {
					Properties = Properties + key + "=" + value + "\n";
				}
			}
			Properties = Properties + "\n";
		} catch (FileNotFoundException ex) {
			ex.printStackTrace();
		} catch (IOException ex) {
			ex.printStackTrace();
		}

		int select = JOptionPane.showConfirmDialog(null, Properties, "Arduino Tron Properties Information",
				JOptionPane.DEFAULT_OPTION);
		if (select == 0) {
		}
	}

	void sendArduinoCommand(ActionEvent e) {
		JFrame arduinoframe = new JFrame();
		String arduinoCommand = JOptionPane.showInputDialog(arduinoframe, "Send Arduino Command",
				"Arduino Command: /LED1=ON /GPIO5=OFF", JOptionPane.WARNING_MESSAGE);
		if (arduinoCommand != null && !arduinoCommand.isEmpty()) {
			com.iotbpm.server.AgentConnect.getInstance().sendPost("TronAgent", arduinoCommand);
		}
	}

	// Arduino Tron Server Status
	void getArduinoServerStatus(ActionEvent e) {
		int select = JOptionPane.showConfirmDialog(null, "Arduino Tron Server Status?", "Arduino Tron Server",
				JOptionPane.YES_NO_CANCEL_OPTION);
		if (select == 0) {
			com.iotbpm.server.AgentConnect.getInstance().sendGet("TronAgent", "/server?q=status");
		}
	}

	void getArduinoServerUpdate(ActionEvent e) {
		int select = JOptionPane.showConfirmDialog(null, "Arduino Tron Server Update?", "Arduino Tron Server",
				JOptionPane.YES_NO_CANCEL_OPTION);
		if (select == 0) {
			com.iotbpm.server.AgentConnect.getInstance().sendGet("TronAgent", "/sensor?q=update");
		}
	}

	void helpContentsAction(ActionEvent e) {
		try {
			WebBrowser.url("http://www.iotbpm.com/help/");
		} catch (Exception ex) {
			System.out.println(ex.toString());
		}
	}

	void aboutIoTBPMAction(ActionEvent e) {
		try {
			AboutDialog dialog = new AboutDialog();
			dialog.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
			dialog.setVisible(true);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	public void show() {
		this.frame.setVisible(true);
	}

	public void updateDevice(String device) {
		this.devices.get(device).updateDevice();
	}

	public void log(String message) {
		this.logPanel.log(message);
	}

	public void updateEvent(ServerEvent event) {
		this.banner.addEvent(event);
	}
}
