package com.iotbpm.ui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.atomic.AtomicInteger;

import javax.swing.JComponent;
import javax.swing.JTextField;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.iotbpm.model.ServerEvent;

/**
 * A simple component to show the incoming alert events
 */
public class ScrollingBanner extends JComponent implements Runnable {

	private static final long serialVersionUID = 510l;
	private static final long SPACE = 10;

	private Queue<ServerEvent> events;
	private volatile boolean shutdown = false;
	private AtomicInteger headOffset = new AtomicInteger(0);
	private ServerEvent headEvent = null;

	private String event_CONST = "keypress2.0";

	private final Logger logger = LoggerFactory.getLogger(ScrollingBanner.class);

	public ScrollingBanner() {
		super();
		events = new ConcurrentLinkedQueue<ServerEvent>();
		setBackground(Color.BLACK);
		setForeground(Color.GREEN);
		setFont(new JTextField().getFont().deriveFont(Font.BOLD));
		setPreferredSize(new Dimension(600, 30));
	}

	@Override
	public void run() {
		shutdown = false;
		while (!shutdown) {
			repaint();
			try {
				Thread.sleep(150);
			} catch (InterruptedException e) {
				shutdown = true;
			}
		}
	}

	public void shutdown() {
		shutdown = true;
	}

	public void addEvent(ServerEvent event) {
		events.add(event);
	}

	@Override
	public void paint(Graphics g) {
		final Dimension dim = this.getSize();
		final int y = ((dim.height - g.getFontMetrics().getHeight()) / 2) + g.getFontMetrics().getHeight() - 2;
		// erase previous
		g.setColor(Color.BLACK);
		g.fillRect(0, 0, dim.width, dim.height);
		// redraw
		int width = 10;
		if (headEvent == null) {
			headEvent = events.poll();
			headOffset.set(0);
		}
		if (headEvent != null) {
			String toDraw = headEvent.toString().substring(headOffset.get());
			width += SPACE + drawString(g, y, width, headEvent, toDraw);
		}
		for (ServerEvent event : events) {
			String toDraw = event.toString();
			width += SPACE + drawString(g, y, width, event, toDraw);
			if (width > dim.width) {
				if (headOffset.addAndGet(2) >= headEvent.toString().length()) {
					headEvent = null;
				}
				break;
			}
		}
	}

	private int drawString(Graphics g, final int y, int width, ServerEvent event, String toDraw) {
		int size = g.getFontMetrics().stringWidth(toDraw);
		if (event.getEvent().equals(event_CONST)) {
			g.setColor(Color.red);
		} else {
			g.setColor(Color.green);
		}
		g.drawString(toDraw, width, y);
		return size;
	}
}
