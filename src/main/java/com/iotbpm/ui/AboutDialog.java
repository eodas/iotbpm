package com.iotbpm.ui;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JTextPane;

/**
 * This class displays the Arduino Tron standard about dialog
 */
public class AboutDialog extends JDialog {
	private static final long serialVersionUID = 1L;
	private final JPanel contentPanel = new JPanel();

	private final Logger logger = LoggerFactory.getLogger(AboutDialog.class);

	public AboutDialog() {
		try {
			setDefaultCloseOperation(DISPOSE_ON_CLOSE);
			initAboutBox();
		} catch (Exception exception) {
			exception.printStackTrace();
		}
	}

	private void initAboutBox() throws Exception {
		ImageIcon aboutIcon = new ImageIcon("images" + File.separator + "EOSpyLogo.png");
		setBounds(100, 100, 520, 300);
		setTitle("Arduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Arduino Tron Expert System");

		getContentPane().setLayout(new BorderLayout());
		contentPanel.setLayout(new FlowLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.WEST);
		{
			JLabel imageLabel = new JLabel(aboutIcon);
			contentPanel.add(imageLabel);
		}
		{
			JPanel buttonPane = new JPanel();
			buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
			getContentPane().add(buttonPane, BorderLayout.SOUTH);
			{
				JButton okButton = new JButton("OK");
				okButton.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						actionPerformed_Ok(e);
					}
				});
				okButton.setActionCommand("OK");
				buttonPane.add(okButton);
				getRootPane().setDefaultButton(okButton);
			}
		}
		{
			JTextPane txtIoTBPMSoftware = new JTextPane();
			txtIoTBPMSoftware.setText(
					"\r\nArduino Tron AI-IoTBPM :: Internet of Things Drools-jBPM Expert System using EOSpy Arduino Tron AI-IoTBPM Processing.\r\n\r\n"
							+ "This Software is Provided “As Is” And Any Expressed or Implied Warranties, Including, But Not Limited to, The Implied Warranties of "
							+ "Merchantability And Fitness For A Particular Purpose Are Disclaimed.\r\n\r\nVisit the www.IoTBPM.com website for additional information "
							+ "and documentation on Drools-jBPM Expert Systems, Arduino Tron and other Arduino projects, android projects and AI-IoTBPM Processing.\r\n\r\n"
							+ "Thank You! -Executive Order Custom Software Development Team");
			getContentPane().add(txtIoTBPMSoftware, BorderLayout.CENTER);
		}
	}

	public void actionPerformed_Ok(ActionEvent e) {
		dispose();

	}
}
