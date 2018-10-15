package com.iotbpm.ui;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;
import javax.swing.SwingUtilities;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A panel to log information
 */
public class LogPanel extends JPanel {

	private static final long serialVersionUID = 1L;
	private final JTextArea log;

	private final Logger logger = LoggerFactory.getLogger(LogPanel.class);

	public LogPanel() {
		setLayout(new BorderLayout());
		log = new JTextArea();
		log.setEditable(false);

		JScrollPane areaScrollPane = new JScrollPane(log);
		areaScrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);

		add(areaScrollPane, BorderLayout.CENTER);
		setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		setPreferredSize(new Dimension(500, 60));
	}

	public void log(final String text) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				log.append(text + "\n");
			}
		});
	}

	public void logClear() {
		log.setText("");
	}
}
