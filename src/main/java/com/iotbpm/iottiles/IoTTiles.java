package com.iotbpm.iottiles;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.ImageIcon;
import javax.swing.SwingConstants;
import javax.swing.WindowConstants;

import java.awt.Font;
import java.awt.Color;
import java.awt.BorderLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import java.io.File;

/**
 * Main window implementation for the Arduino Tron IoT Tiles example
 */
public class IoTTiles {
	private final JFrame frameIoT;
	private final IoTEvents iotEvents;
	private static IoTTiles IOTTILES_INSTANCE = null;

	private ImageIcon bulbIcon;
	private ImageIcon celsiusIcon;
	private ImageIcon coldIcon;

	private ImageIcon doorIcon;
	private ImageIcon door_inIcon;
	private ImageIcon door_openIcon;
	private ImageIcon door_outIcon;

	private ImageIcon emblem_systemIcon;

	private ImageIcon lightbulbIcon;
	private ImageIcon lightbulb_offIcon;

	private ImageIcon lockIcon;
	private ImageIcon lock_openIcon;

	private ImageIcon personalIcon;
	private ImageIcon personal2Icon;

	private ImageIcon weather_cloudsIcon;
	private ImageIcon weather_cloudyIcon;
	private ImageIcon weather_lightningIcon;
	private ImageIcon weather_rainIcon;
	private ImageIcon weather_snowIcon;
	private ImageIcon weather_sunIcon;

	private ImageIcon web_conciergeIcon;

	private JPanel panel_1;
	private JLabel lblBottomLabel_1;
	private JLabel lblIconLabel_1;

	private JPanel panel_2;
	private JLabel lblBottomLabel_2;
	private JLabel lblIconLabel_2;

	private JPanel panel_3;
	private JLabel lblBottomLabel_3;
	private JLabel lblIconLabel_3;

	private JPanel panel_4;
	private JLabel lblBottomLabel_4;
	private JLabel lblIconLabel_4;

	private JPanel panel_5;
	private JLabel lblBottomLabel_5;
	private JLabel lblIconLabel_5;

	private JPanel panel_6;
	private JLabel lblBottomLabel_6;
	private JLabel lblIconLabel_6;

	private JPanel panel_7;
	private JLabel lblBottomLabel_7;
	private JLabel lblIconLabel_7;

	private JPanel panel_8;
	private JLabel lblBottomLabel_8;
	private JLabel lblIconLabel_8;

	private JPanel panel_9;
	private JLabel lblBottomLabel_9;
	private JLabel lblIconLabel_9;

	private JPanel panel_10;
	private JLabel lblBottomLabel_10;
	private JLabel lblIconLabel_10;

	private JPanel panel_11;
	private JLabel lblBottomLabel_11;
	private JLabel lblIconLabel_11;

	private JPanel panel_12;
	private JLabel lblBottomLabel_12;
	private JLabel lblIconLabel_12;

	private JPanel panel_13;
	private JLabel lblBottomLabel_13;
	private JLabel lblIconLabel_13;

	private JPanel panel_14;
	private JLabel lblBottomLabel_14;
	private JLabel lblIconLabel_14;

	private JPanel panel_15;
	private JLabel lblBottomLabel_15;
	private JLabel lblIconLabel_15;

	private JPanel panel_16;
	private JLabel lblBottomLabel_16;
	private JLabel lblIconLabel_16;

	private JPanel panel_17;
	private JLabel lblBottomLabel_17;
	private JLabel lblIconLabel_17;

	private JPanel panel_18;
	private JLabel lblBottomLabel_18;
	private JLabel lblIconLabel_18;

	private JPanel panel_19;
	private JLabel lblBottomLabel_19;
	private JLabel lblIconLabel_19;

	public IoTTiles(IoTEvents iotEvents, boolean exitOnClose) {
		this.iotEvents = iotEvents;
		this.frameIoT = buildFrame(exitOnClose);
		IoTTiles.IOTTILES_INSTANCE = this;
	}

	public static IoTTiles getInstance() {
		return IOTTILES_INSTANCE;
	}

	// Initialize the contents of the frame
	private JFrame buildFrame(boolean exitOnClose) {
		JFrame frame = new JFrame();

		frame.getContentPane().setBackground(Color.BLACK);
		frame.setTitle(
				"Arduino Tron AI-IoTBPM :: IoT Tiles Internet of Things Drools-jBPM using Arduino Tron AI-IoTBPM");
		frame.setBounds(100, 100, 755, 465);
		frame.setDefaultCloseOperation(exitOnClose ? JFrame.EXIT_ON_CLOSE : WindowConstants.DISPOSE_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		frame.setLocationRelativeTo(null); // Center in screen

		bulbIcon = new ImageIcon("icons" + File.separator + "bulb.png");
		celsiusIcon = new ImageIcon("icons" + File.separator + "celsius.png");
		coldIcon = new ImageIcon("icons" + File.separator + "cold.png");

		doorIcon = new ImageIcon("icons" + File.separator + "door.png");
		door_inIcon = new ImageIcon("icons" + File.separator + "door_in.png");
		door_openIcon = new ImageIcon("icons" + File.separator + "door_open.png");
		door_outIcon = new ImageIcon("icons" + File.separator + "door_out.png");

		emblem_systemIcon = new ImageIcon("icons" + File.separator + "emblem_system.png");

		lightbulbIcon = new ImageIcon("icons" + File.separator + "lightbulb.png");
		lightbulb_offIcon = new ImageIcon("icons" + File.separator + "lightbulb_off.png");

		lockIcon = new ImageIcon("icons" + File.separator + "lock.png");
		lock_openIcon = new ImageIcon("icons" + File.separator + "lock_open.png");

		personalIcon = new ImageIcon("icons" + File.separator + "personal.png");
		personal2Icon = new ImageIcon("icons" + File.separator + "personal-2.png");

		weather_cloudsIcon = new ImageIcon("icons" + File.separator + "weather_clouds.png");
		weather_cloudyIcon = new ImageIcon("icons" + File.separator + "weather_cloudy.png");
		weather_lightningIcon = new ImageIcon("icons" + File.separator + "weather_lightning.png");
		weather_rainIcon = new ImageIcon("icons" + File.separator + "weather_rain.png");
		weather_snowIcon = new ImageIcon("icons" + File.separator + "weather_snow.png");
		weather_sunIcon = new ImageIcon("icons" + File.separator + "weather_sun.png");

		web_conciergeIcon = new ImageIcon("icons" + File.separator + "web_concierge.png");

		panel_1 = new JPanel();
		panel_1.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_1Clicked(e);
			}
		});
		panel_1.setBackground(Color.BLUE);
		panel_1.setBounds(5, 5, 205, 100);
		frame.getContentPane().add(panel_1);
		panel_1.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_1 = new JLabel("Alert Bell");
		lblTopLabel_1.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_1.setForeground(Color.WHITE);
		panel_1.add(lblTopLabel_1, BorderLayout.NORTH);

		lblBottomLabel_1 = new JLabel("Active");
		lblBottomLabel_1.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_1.setForeground(Color.WHITE);
		panel_1.add(lblBottomLabel_1, BorderLayout.SOUTH);

		lblIconLabel_1 = new JLabel("");
		lblIconLabel_1.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblIconLabel_1.setForeground(Color.WHITE);
		lblIconLabel_1.setHorizontalAlignment(SwingConstants.CENTER);
		panel_1.add(lblIconLabel_1, BorderLayout.CENTER);
		lblIconLabel_1.setIcon(doorIcon);

		panel_2 = new JPanel();
		panel_2.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_2Clicked(e);
			}
		});
		panel_2.setBackground(Color.MAGENTA);
		panel_2.setBounds(215, 5, 205, 100);
		frame.getContentPane().add(panel_2);
		panel_2.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_2 = new JLabel("Office Mode");
		lblTopLabel_2.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_2.setForeground(Color.WHITE);
		panel_2.add(lblTopLabel_2, BorderLayout.NORTH);

		lblBottomLabel_2 = new JLabel("Office-Day");
		lblBottomLabel_2.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_2.setForeground(Color.WHITE);
		panel_2.add(lblBottomLabel_2, BorderLayout.SOUTH);

		lblIconLabel_2 = new JLabel("");
		lblIconLabel_2.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblIconLabel_2.setForeground(Color.WHITE);
		lblIconLabel_2.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(lblIconLabel_2, BorderLayout.CENTER);
		lblIconLabel_2.setIcon(doorIcon);

		panel_3 = new JPanel();
		panel_3.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_3Clicked(e);
			}
		});
		panel_3.setBackground(new Color(199, 21, 133));
		panel_3.setBounds(425, 5, 100, 100);
		frame.getContentPane().add(panel_3);
		panel_3.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_3 = new JLabel("Steven");
		lblTopLabel_3.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_3.setForeground(Color.WHITE);
		panel_3.add(lblTopLabel_3, BorderLayout.NORTH);

		lblBottomLabel_3 = new JLabel("Present");
		lblBottomLabel_3.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_3.setForeground(Color.WHITE);
		panel_3.add(lblBottomLabel_3, BorderLayout.SOUTH);

		lblIconLabel_3 = new JLabel("");
		lblIconLabel_3.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblIconLabel_3.setForeground(Color.WHITE);
		lblIconLabel_3.setHorizontalAlignment(SwingConstants.CENTER);
		panel_3.add(lblIconLabel_3, BorderLayout.CENTER);
		lblIconLabel_3.setIcon(personal2Icon);

		panel_4 = new JPanel();
		panel_4.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_4Clicked(e);
			}
		});
		panel_4.setBackground(Color.RED);
		panel_4.setBounds(530, 5, 205, 100);
		frame.getContentPane().add(panel_4);
		panel_4.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_4 = new JLabel("Smart Office Monitor");
		lblTopLabel_4.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_4.setForeground(Color.WHITE);
		panel_4.add(lblTopLabel_4, BorderLayout.NORTH);

		lblBottomLabel_4 = new JLabel("Office Armed (Stay)");
		lblBottomLabel_4.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_4.setForeground(Color.WHITE);
		panel_4.add(lblBottomLabel_4, BorderLayout.SOUTH);

		lblIconLabel_4 = new JLabel("");
		lblIconLabel_4.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblIconLabel_3.setForeground(Color.WHITE);
		lblIconLabel_4.setHorizontalAlignment(SwingConstants.CENTER);
		panel_4.add(lblIconLabel_4, BorderLayout.CENTER);
		lblIconLabel_4.setIcon(lightbulbIcon);

		panel_5 = new JPanel();
		panel_5.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_5Clicked(e);
			}
		});
		panel_5.setBackground(Color.RED);
		panel_5.setBounds(5, 110, 205, 100);
		frame.getContentPane().add(panel_5);
		panel_5.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_5 = new JLabel("Office Temperature");
		lblTopLabel_5.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_5.setForeground(Color.WHITE);
		panel_5.add(lblTopLabel_5, BorderLayout.NORTH);

		lblBottomLabel_5 = new JLabel("DHT11 Temperature Humidity");
		lblBottomLabel_5.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_5.setForeground(Color.WHITE);
		panel_5.add(lblBottomLabel_5, BorderLayout.SOUTH);

		lblIconLabel_5 = new JLabel("72'");
		lblIconLabel_5.setFont(new Font("Tahoma", Font.BOLD | Font.ITALIC, 16));
		lblIconLabel_5.setForeground(Color.WHITE);
		lblIconLabel_5.setHorizontalAlignment(SwingConstants.CENTER);
		panel_5.add(lblIconLabel_5, BorderLayout.CENTER);
		lblIconLabel_5.setIcon(celsiusIcon);

		panel_6 = new JPanel();
		panel_6.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_6Clicked(e);
			}
		});
		panel_6.setBackground(Color.LIGHT_GRAY);
		panel_6.setBounds(215, 110, 100, 100);
		frame.getContentPane().add(panel_6);
		panel_6.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_6 = new JLabel("Front Door");
		lblTopLabel_6.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_6.setForeground(Color.WHITE);
		panel_6.add(lblTopLabel_6, BorderLayout.NORTH);

		lblBottomLabel_6 = new JLabel("Unlocked");
		lblBottomLabel_6.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_6.setForeground(Color.WHITE);
		panel_6.add(lblBottomLabel_6, BorderLayout.SOUTH);

		lblIconLabel_6 = new JLabel("");
		lblIconLabel_6.setForeground(Color.WHITE);
		lblIconLabel_6.setHorizontalAlignment(SwingConstants.CENTER);
		panel_6.add(lblIconLabel_6, BorderLayout.CENTER);
		lblIconLabel_6.setIcon(lock_openIcon);

		panel_7 = new JPanel();
		panel_7.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_7Clicked(e);
			}
		});
		panel_7.setBackground(Color.BLUE);
		panel_7.setBounds(320, 110, 100, 100);
		frame.getContentPane().add(panel_7);
		panel_7.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_7 = new JLabel("Front Door");
		lblTopLabel_7.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_7.setForeground(Color.WHITE);
		panel_7.add(lblTopLabel_7, BorderLayout.NORTH);

		lblBottomLabel_7 = new JLabel("Closed");
		lblBottomLabel_7.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_7.setForeground(Color.WHITE);
		panel_7.add(lblBottomLabel_7, BorderLayout.SOUTH);

		lblIconLabel_7 = new JLabel("");
		lblIconLabel_7.setForeground(Color.WHITE);
		lblIconLabel_7.setHorizontalAlignment(SwingConstants.CENTER);
		panel_7.add(lblIconLabel_7, BorderLayout.CENTER);
		lblIconLabel_7.setIcon(doorIcon);

		panel_8 = new JPanel();
		panel_8.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_8Clicked(e);
			}
		});
		panel_8.setBackground(new Color(128, 128, 128));
		panel_8.setBounds(425, 110, 100, 100);
		frame.getContentPane().add(panel_8);
		panel_8.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_8 = new JLabel("Lobby Door");
		lblTopLabel_8.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_8.setForeground(Color.WHITE);
		panel_8.add(lblTopLabel_8, BorderLayout.NORTH);

		lblBottomLabel_8 = new JLabel("Unlocked");
		lblBottomLabel_8.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_8.setForeground(Color.WHITE);
		panel_8.add(lblBottomLabel_8, BorderLayout.SOUTH);

		lblIconLabel_8 = new JLabel("");
		lblIconLabel_8.setForeground(Color.WHITE);
		lblIconLabel_8.setHorizontalAlignment(SwingConstants.CENTER);
		panel_8.add(lblIconLabel_8, BorderLayout.CENTER);
		lblIconLabel_8.setIcon(lock_openIcon);

		panel_9 = new JPanel();
		panel_9.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_9Clicked(e);
			}
		});
		panel_9.setBackground(Color.BLUE);
		panel_9.setBounds(530, 110, 100, 100);
		frame.getContentPane().add(panel_9);
		panel_9.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_9 = new JLabel("Lobby Door");
		lblTopLabel_9.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_9.setForeground(Color.WHITE);
		panel_9.add(lblTopLabel_9, BorderLayout.NORTH);

		lblBottomLabel_9 = new JLabel("Closed");
		lblBottomLabel_9.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_9.setForeground(Color.WHITE);
		panel_9.add(lblBottomLabel_9, BorderLayout.SOUTH);

		lblIconLabel_9 = new JLabel("");
		lblIconLabel_9.setForeground(Color.WHITE);
		lblIconLabel_9.setHorizontalAlignment(SwingConstants.CENTER);
		panel_9.add(lblIconLabel_9, BorderLayout.CENTER);
		lblIconLabel_9.setIcon(lockIcon);

		panel_10 = new JPanel();
		panel_10.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_10Clicked(e);
			}
		});
		panel_10.setBackground(Color.PINK);
		panel_10.setBounds(635, 110, 100, 205);
		frame.getContentPane().add(panel_10);
		panel_10.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_10 = new JLabel("Lobby Light");
		lblTopLabel_10.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_10.setForeground(Color.WHITE);
		panel_10.add(lblTopLabel_10, BorderLayout.NORTH);

		lblBottomLabel_10 = new JLabel("Light Level");
		lblBottomLabel_10.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_10.setForeground(Color.WHITE);
		panel_10.add(lblBottomLabel_10, BorderLayout.SOUTH);

		lblIconLabel_10 = new JLabel("");
		lblIconLabel_10.setForeground(Color.WHITE);
		lblIconLabel_10.setHorizontalAlignment(SwingConstants.CENTER);
		panel_10.add(lblIconLabel_10, BorderLayout.CENTER);
		lblIconLabel_10.setIcon(lockIcon);

		panel_11 = new JPanel();
		panel_11.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_11Clicked(e);
			}
		});
		panel_11.setBackground(new Color(244, 164, 96));
		panel_11.setBounds(5, 215, 100, 205);
		frame.getContentPane().add(panel_11);
		panel_11.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_11 = new JLabel("-Front Door");
		lblTopLabel_11.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_11.setForeground(Color.WHITE);
		panel_11.add(lblTopLabel_11, BorderLayout.NORTH);

		lblBottomLabel_11 = new JLabel("Lock");
		lblBottomLabel_11.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_11.setForeground(Color.WHITE);
		panel_11.add(lblBottomLabel_11, BorderLayout.SOUTH);

		lblIconLabel_11 = new JLabel("");
		lblIconLabel_11.setForeground(Color.WHITE);
		lblIconLabel_11.setHorizontalAlignment(SwingConstants.CENTER);
		panel_11.add(lblIconLabel_11, BorderLayout.CENTER);
		lblIconLabel_11.setIcon(lockIcon);

		panel_12 = new JPanel();
		panel_12.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_12Clicked(e);
			}
		});
		panel_12.setBackground(Color.DARK_GRAY);
		panel_12.setBounds(110, 215, 100, 100);
		frame.getContentPane().add(panel_12);
		panel_12.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_12 = new JLabel("Front Door");
		lblTopLabel_12.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_12.setForeground(Color.WHITE);
		panel_12.add(lblTopLabel_12, BorderLayout.NORTH);

		lblBottomLabel_12 = new JLabel("Lock");
		lblBottomLabel_12.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_12.setForeground(Color.WHITE);
		panel_12.add(lblBottomLabel_12, BorderLayout.SOUTH);

		lblIconLabel_12 = new JLabel("");
		lblIconLabel_12.setForeground(Color.WHITE);
		lblIconLabel_12.setHorizontalAlignment(SwingConstants.CENTER);
		panel_12.add(lblIconLabel_12, BorderLayout.CENTER);
		lblIconLabel_12.setIcon(lockIcon);

		panel_13 = new JPanel();
		panel_13.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_13Clicked(e);
			}
		});
		panel_13.setBackground(new Color(0, 128, 0));
		panel_13.setBounds(215, 215, 205, 100);
		frame.getContentPane().add(panel_13);
		panel_13.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_13 = new JLabel("OLED ESP-01 Display");
		lblTopLabel_13.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_13.setForeground(Color.WHITE);
		panel_13.add(lblTopLabel_13, BorderLayout.NORTH);

		lblBottomLabel_13 = new JLabel("IoT OLED Message");
		lblBottomLabel_13.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_13.setForeground(Color.WHITE);
		panel_13.add(lblBottomLabel_13, BorderLayout.SOUTH);

		lblIconLabel_13 = new JLabel("");
		lblIconLabel_13.setForeground(Color.WHITE);
		lblIconLabel_13.setHorizontalAlignment(SwingConstants.CENTER);
		panel_13.add(lblIconLabel_13, BorderLayout.CENTER);
		lblIconLabel_13.setIcon(lockIcon);

		panel_14 = new JPanel();
		panel_14.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_14Clicked(e);
			}
		});
		panel_14.setBackground(Color.RED);
		panel_14.setBounds(425, 215, 100, 100);
		frame.getContentPane().add(panel_14);
		panel_14.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_14 = new JLabel("-Front Door");
		lblTopLabel_14.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_14.setForeground(Color.WHITE);
		panel_14.add(lblTopLabel_14, BorderLayout.NORTH);

		lblBottomLabel_14 = new JLabel("Lock");
		lblBottomLabel_14.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_14.setForeground(Color.WHITE);
		panel_14.add(lblBottomLabel_14, BorderLayout.SOUTH);

		lblIconLabel_14 = new JLabel("");
		lblIconLabel_14.setForeground(Color.WHITE);
		lblIconLabel_14.setHorizontalAlignment(SwingConstants.CENTER);
		panel_14.add(lblIconLabel_14, BorderLayout.CENTER);
		lblIconLabel_14.setIcon(lockIcon);

		panel_15 = new JPanel();
		panel_15.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_15Clicked(e);
			}
		});
		panel_15.setBackground(Color.DARK_GRAY);
		panel_15.setBounds(530, 215, 100, 205);
		frame.getContentPane().add(panel_15);
		panel_15.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_15 = new JLabel("IoT Dash Button");
		lblTopLabel_15.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_15.setForeground(Color.WHITE);
		panel_15.add(lblTopLabel_15, BorderLayout.NORTH);

		lblBottomLabel_15 = new JLabel("IoT Chime");
		lblBottomLabel_15.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_15.setForeground(Color.WHITE);
		panel_15.add(lblBottomLabel_15, BorderLayout.SOUTH);

		lblIconLabel_15 = new JLabel("");
		lblIconLabel_15.setForeground(Color.WHITE);
		lblIconLabel_15.setHorizontalAlignment(SwingConstants.CENTER);
		panel_15.add(lblIconLabel_15, BorderLayout.CENTER);
		lblIconLabel_15.setIcon(web_conciergeIcon);

		panel_16 = new JPanel();
		panel_16.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_16Clicked(e);
			}
		});
		panel_16.setBackground(Color.BLUE);
		panel_16.setBounds(110, 320, 100, 100);
		frame.getContentPane().add(panel_16);
		panel_16.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_16 = new JLabel("IoT Sensors");
		lblTopLabel_16.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_16.setForeground(Color.WHITE);
		panel_16.add(lblTopLabel_16, BorderLayout.NORTH);

		lblBottomLabel_16 = new JLabel("Monitor");
		lblBottomLabel_16.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_16.setForeground(Color.WHITE);
		panel_16.add(lblBottomLabel_16, BorderLayout.SOUTH);

		lblIconLabel_16 = new JLabel("");
		lblIconLabel_16.setForeground(Color.WHITE);
		lblIconLabel_16.setHorizontalAlignment(SwingConstants.CENTER);
		panel_16.add(lblIconLabel_16, BorderLayout.CENTER);
		lblIconLabel_16.setIcon(emblem_systemIcon);

		panel_17 = new JPanel();
		panel_17.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_17Clicked(e);
			}
		});
		panel_17.setBackground(Color.GRAY);
		panel_17.setBounds(215, 320, 100, 100);
		frame.getContentPane().add(panel_17);
		panel_17.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_17 = new JLabel("Dash Button");
		lblTopLabel_17.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_17.setForeground(Color.WHITE);
		panel_17.add(lblTopLabel_17, BorderLayout.NORTH);

		lblBottomLabel_17 = new JLabel("Button Press");
		lblBottomLabel_17.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_17.setForeground(Color.WHITE);
		panel_17.add(lblBottomLabel_17, BorderLayout.SOUTH);

		lblIconLabel_17 = new JLabel("");
		lblIconLabel_17.setForeground(Color.WHITE);
		lblIconLabel_17.setHorizontalAlignment(SwingConstants.CENTER);
		panel_17.add(lblIconLabel_17, BorderLayout.CENTER);
		lblIconLabel_17.setIcon(web_conciergeIcon);

		panel_18 = new JPanel();
		panel_18.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_18Clicked(e);
			}
		});
		panel_18.setBackground(Color.RED);
		panel_18.setBounds(320, 320, 205, 100);
		frame.getContentPane().add(panel_18);
		panel_18.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_18 = new JLabel("Outside Temperature");
		lblTopLabel_18.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_18.setForeground(Color.WHITE);
		panel_18.add(lblTopLabel_18, BorderLayout.NORTH);

		lblBottomLabel_18 = new JLabel("DHT11 Temperature Humidity");
		lblBottomLabel_18.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_18.setForeground(Color.WHITE);
		panel_18.add(lblBottomLabel_18, BorderLayout.SOUTH);

		lblIconLabel_18 = new JLabel("75'");
		lblIconLabel_18.setFont(new Font("Tahoma", Font.BOLD | Font.ITALIC, 16));
		lblIconLabel_18.setForeground(Color.WHITE);
		lblIconLabel_18.setHorizontalAlignment(SwingConstants.CENTER);
		panel_18.add(lblIconLabel_18, BorderLayout.CENTER);
		lblIconLabel_18.setIcon(weather_sunIcon);

		panel_19 = new JPanel();
		panel_19.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				panel_19Clicked(e);
			}
		});
		panel_19.setBackground(Color.BLUE);
		panel_19.setBounds(635, 320, 100, 100);
		frame.getContentPane().add(panel_19);
		panel_19.setLayout(new BorderLayout(0, 0));

		JLabel lblTopLabel_19 = new JLabel("-Front Door");
		lblTopLabel_19.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblTopLabel_19.setForeground(Color.WHITE);
		panel_19.add(lblTopLabel_19, BorderLayout.NORTH);

		lblBottomLabel_19 = new JLabel("Lock");
		lblBottomLabel_19.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblBottomLabel_19.setForeground(Color.WHITE);
		panel_19.add(lblBottomLabel_19, BorderLayout.SOUTH);

		lblIconLabel_19 = new JLabel("");
		lblIconLabel_19.setForeground(Color.WHITE);
		lblIconLabel_19.setHorizontalAlignment(SwingConstants.CENTER);
		panel_19.add(lblIconLabel_19, BorderLayout.CENTER);
		lblIconLabel_19.setIcon(lockIcon);

		return frame;
	}

	public void show() {
		this.frameIoT.setVisible(true);
	}

	public void panel_1Clicked(MouseEvent e) {
	}

	public void panel_2Clicked(MouseEvent e) {
		lblIconLabel_3.setIcon(lightbulbIcon);
		lblBottomLabel_3.setText("On");
	}

	public void panel_3Clicked(MouseEvent e) {
		iotEvents.IoTServerEvent("GET /?id=100222&timestamp=0&event=CHIME");
	}

	public void panel_4Clicked(MouseEvent e) {
	}

	// Office Temperature
	public void panel_5Clicked(MouseEvent e) {
	}

	public void panel_5Temp(String temp) {
		lblIconLabel_5.setText(temp);
	}

	// Front Door Locked
	public void panel_6Clicked(MouseEvent e) {
		iotEvents.IoTServerEvent("GET /?id=100333&timestamp=0&event=Lock");
	}

	public void panel_6DoorLocked() {
		lblIconLabel_6.setIcon(lockIcon);
		lblBottomLabel_6.setText("Locked");
		panel_6.setBackground(Color.RED);
	}

	public void panel_6DoorUnlocked() {
		lblIconLabel_6.setIcon(lock_openIcon);
		lblBottomLabel_6.setText("Unlocked");
		panel_6.setBackground(Color.LIGHT_GRAY);
	}

	// Front Door Open
	public void panel_7Clicked(MouseEvent e) {
		JOptionPane.showMessageDialog(null,
				"The IoT Door Open Sensor jBPM Automation process is triggered by an Arduino Tron event.",
				"IoT Door Sensor", JOptionPane.INFORMATION_MESSAGE);
	}

	public void panel_7DoorOpened() {
		lblIconLabel_7.setIcon(door_inIcon);
		lblBottomLabel_7.setText("Opened");
		panel_7.setBackground(Color.RED);
		panel_7Clear();
	}

	public void panel_7DoorClosed() {
		lblIconLabel_7.setIcon(doorIcon);
		lblBottomLabel_7.setText("Closed");
		panel_7.setBackground(Color.BLUE);
	}

	public void panel_7Clear() {
		new Thread(new Runnable() {
			public void run() {
				for (int i = 0; i <= 4; i++) {
					if (i == 4) {
						panel_7DoorClosed();
					}
					try {
						Thread.sleep(500L);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}).start();
	}

	public void panel_8Clicked(MouseEvent e) {
	}

	// Lobby Door Open
	public void panel_9Clicked(MouseEvent e) {
	}

	public void panel_10Clicked(MouseEvent e) {
	}

	public void panel_11Clicked(MouseEvent e) {
	}

	public void panel_12Clicked(MouseEvent e) {
	}

	public void panel_13Clicked(MouseEvent e) {
	}

	public void panel_14Clicked(MouseEvent e) {
	}

	// IoT Dash Button
	public void panel_15Clicked(MouseEvent e) {
		JOptionPane.showMessageDialog(null,
				"Clear IoT Dash Button Sensor process triggered by an Arduino Tron event message.", "IoT Dash Button",
				JOptionPane.INFORMATION_MESSAGE);
		panel_15DashButtonAlert("");
	}

	public void panel_15DashButtonAlert(String alert) {
		lblIconLabel_15.setText(alert);
	}

	// IoT Sensors
	public void panel_16Clicked(MouseEvent e) {
		JOptionPane.showMessageDialog(null,
				"This is the default IoT Sensors jBPM Automation process. Use Drools Rules to start a specific IoT jBPM Automation process.",
				"Monitor IoT Sensors", JOptionPane.INFORMATION_MESSAGE);
	}

	public void panel_16IoTSensors(String IoT_Sensors) {
		lblBottomLabel_16.setText(IoT_Sensors);
		panel_16Blink();
	}

	public void panel_16Blink() {
		new Thread(new Runnable() {
			public void run() {
				boolean blink = true;
				for (int i = 0; i < 6; i++) {
					if (blink) {
						panel_16.setBackground(Color.RED);
					} else {
						panel_16.setBackground(Color.BLUE);
					}
					blink = !blink;
					try {
						Thread.sleep(500L);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}).start();
	}

	// Dash Button
	public void panel_17Clicked(MouseEvent e) {
		iotEvents.IoTServerEvent("GET /?id=100555&timestamp=0&alarm=Message&event=Chime");
	}

	// Outside Temperature
	public void panel_18Clicked(MouseEvent e) {
	}

	public void panel_18Temp(String temp) {
		lblIconLabel_18.setText(temp);
	}

	public void panel_19Clicked(MouseEvent e) {
	}
}
