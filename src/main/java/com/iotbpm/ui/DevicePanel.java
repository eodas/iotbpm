package com.iotbpm.ui;

import java.awt.Color;

import javax.swing.GroupLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.iotbpm.model.Devices;

/**
 * Class that manages a device UI panel
 */
public class DevicePanel extends JPanel {

	private static final long serialVersionUID = 1L;
	private final Devices model;
	private final JTextField actionField;
	private final JTextField statusField;

	private String action_CONST = "Alert";

	private final Logger logger = LoggerFactory.getLogger(DevicePanel.class);

	public DevicePanel(Devices model) {
		this.model = model;
		GroupLayout formLayout = new GroupLayout(this);
		setLayout(formLayout);
		formLayout.setAutoCreateGaps(true);
		formLayout.setAutoCreateContainerGaps(true);

		JLabel deviceName = new JLabel(model.getName());
		JLabel actionLabel = new JLabel("Action:");
		actionField = new JTextField(model.getAction());
		actionField.setEditable(false);
		JLabel statusLabel = new JLabel("Status:");
		statusField = new JTextField(model.getStatus());
		statusField.setEditable(false);

		formLayout.setHorizontalGroup(formLayout.createParallelGroup().addComponent(deviceName)
				.addGroup(formLayout.createSequentialGroup().addGap(5).addComponent(actionLabel).addGap(5)
						.addComponent(actionField))
				.addGroup(formLayout.createSequentialGroup().addGap(5).addComponent(statusLabel).addGap(5)
						.addComponent(statusField)));
		formLayout.setVerticalGroup(formLayout.createSequentialGroup().addComponent(deviceName).addGroup(formLayout
				.createParallelGroup(GroupLayout.Alignment.BASELINE).addGap(5)
				.addGroup(formLayout.createSequentialGroup().addComponent(actionLabel).addComponent(statusLabel))
				.addGap(5)
				.addGroup(formLayout.createSequentialGroup().addComponent(actionField).addComponent(statusField))));
	}

	public void updateDevice() {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				actionField.setText(model.getAction());
				statusField.setText(model.getStatus());

				if (model.getAction().equals(action_CONST)) {
					actionField.setForeground(Color.RED);
					statusField.setForeground(Color.RED);
				} else {
					actionField.setForeground(Color.BLUE);
					statusField.setForeground(Color.BLUE);
				}
			}
		});
	}
}
