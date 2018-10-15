package com.iotbpm.util;

import org.kie.api.event.rule.AfterMatchFiredEvent;
import org.kie.api.event.rule.AgendaEventListener;
import org.kie.api.event.rule.AgendaGroupPoppedEvent;
import org.kie.api.event.rule.AgendaGroupPushedEvent;
import org.kie.api.event.rule.BeforeMatchFiredEvent;
import org.kie.api.event.rule.MatchCancelledEvent;
import org.kie.api.event.rule.MatchCreatedEvent;
import org.kie.api.event.rule.RuleFlowGroupActivatedEvent;
import org.kie.api.event.rule.RuleFlowGroupDeactivatedEvent;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class AgendaListener implements AgendaEventListener {

	private final Logger logger = LoggerFactory.getLogger(AgendaEventListener.class);

	@Override
	public void matchCreated(MatchCreatedEvent event) {

		System.out.println("> matchCreated : " + event.getMatch().getRule());
		for (Object obj : event.getMatch().getObjects()) {
			System.out.println(obj.toString());
		}
		System.out.println("matchCreated end:");
	}

	@Override
	public void matchCancelled(MatchCancelledEvent event) {
		System.out.println("> matchCancelled : " + event.getMatch().getRule());
	}

	@Override
	public void beforeRuleFlowGroupDeactivated(RuleFlowGroupDeactivatedEvent event) {
		System.out.println("> beforeRuleFlowGroupDeactivated : " + event.getRuleFlowGroup());
	}

	@Override
	public void beforeRuleFlowGroupActivated(RuleFlowGroupActivatedEvent event) {
		System.out.println("> beforeRuleFlowGroupActivated" + event.getRuleFlowGroup());
	}

	@Override
	public void beforeMatchFired(BeforeMatchFiredEvent event) {
		System.out.println("> beforeMatchFired" + event.getMatch().getRule());
	}

	@Override
	public void agendaGroupPushed(AgendaGroupPushedEvent event) {
		System.out.println("> agendaGroupPushed" + event.getAgendaGroup());
	}

	@Override
	public void agendaGroupPopped(AgendaGroupPoppedEvent event) {
		System.out.println("> agendaagendaGroupPoppedGroupPushed " + event.getAgendaGroup());
	}

	@Override
	public void afterRuleFlowGroupDeactivated(RuleFlowGroupDeactivatedEvent event) {
		System.out.println("> afterRuleFlowGroupDeactivated" + event.getRuleFlowGroup()); // .info
	}

	@Override
	public void afterRuleFlowGroupActivated(RuleFlowGroupActivatedEvent event) {
		System.out.println("> afterRuleFlowGroupActivated" + event.getRuleFlowGroup()); // .info
	}

	// FactHandle handle = new DefaultFactHandle();

	@Override
	public void afterMatchFired(AfterMatchFiredEvent event) {
		System.out.println("> afterMatchFired  : " + event.getMatch().getRule()); // .info
		System.out.println("> event facts size: " + event.getMatch().getFactHandles().size());

	}
}
