package com.iotbpm.bpmrules;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.kie.api.KieServices;
import org.kie.api.runtime.KieContainer;
import org.kie.api.runtime.KieSession;
import org.kie.api.runtime.process.ProcessInstance;
import org.kie.api.task.TaskService;
import org.kie.api.task.model.TaskSummary;
import org.kie.api.io.ResourceType;
import org.kie.api.runtime.manager.RuntimeEngine;
import org.kie.api.runtime.manager.RuntimeEnvironment;
import org.kie.api.runtime.manager.RuntimeEnvironmentBuilder;
import org.kie.api.runtime.manager.RuntimeManager;
import org.kie.api.runtime.manager.RuntimeManagerFactory;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.jbpm.test.JBPMHelper;
import org.jbpm.process.instance.event.listeners.RuleAwareProcessEventLister;
import org.jbpm.process.instance.event.listeners.TriggerRulesEventListener;

import com.iotbpm.model.Devices;
import com.iotbpm.model.DevicesList;
import com.iotbpm.model.DeviceEvent;
import com.iotbpm.model.StateList;
import com.iotbpm.ui.MainWindow;
import com.iotbpm.util.AgendaListener;
import com.iotbpm.util.SystemOutProcessEventListener;
import com.iotbpm.util.WorkingMemoryListener;

/**
 * The Arduino Tron AI-IoTBPM Drools-jBPM application
 */
public class jBPMRules {

	private StateList stateList;
	private DevicesList devices;
	private KieSession kSession;
	private KieContainer kContainer;
	private RuntimeManager manager;
	private RuntimeEngine runtime;
	private RuntimeEnvironment environment;

	private String knowledgeDebug = "none";
	private String kSessionType = "";
	private String kSessionName = "";
	private String processID = "";
	private String _processID = "";
	private boolean droolsProcessID = false;

	private final Logger logger = LoggerFactory.getLogger(jBPMRules.class);

	public jBPMRules(DevicesList devices, String kSessionType, String kSessionName, String processID,
			StateList stateList, String knowledgeDebug) {
		super();
		this.devices = devices;
		this.knowledgeDebug = knowledgeDebug;
		this.kSessionType = kSessionType;
		this.kSessionName = kSessionName;
		this.processID = processID;
		this._processID = processID;
		this.stateList = stateList;
	}

	public KieSession createKieSession(String kSessionName) {
		if (kContainer == null) {
			// load up the knowledge base
			KieServices ks = KieServices.Factory.get();
			kContainer = ks.getKieClasspathContainer();
		}
		if (kContainer == null) {
		}

		// kContainer.getKieBase("rules");
		kSession = kContainer.newKieSession(kSessionName);
		if (kSession == null) {
			System.err.println("Error: Cannot find <ksession name=" + kSessionName + "> match in kmodule.xml file.");
			return null;
		}

		if (knowledgeDebug.indexOf("debug") != -1) {
			AgendaListener agendaListener = new AgendaListener();
			WorkingMemoryListener memoryListener = new WorkingMemoryListener();
			kSession.addEventListener(agendaListener);
			kSession.addEventListener(memoryListener);
			// ksession.setGlobal("helper", helper);
			// ksession.setGlobal("logger", logger);
			// kSession.setGlobal("busCalendar", busCalendar);
		}
		return kSession;
	}

	private KieSession getKieSession(String bpmn) throws Exception {
		environment = RuntimeEnvironmentBuilder.Factory.get().newEmptyBuilder()
				.addAsset(KieServices.Factory.get().getResources().newClassPathResource(bpmn), ResourceType.BPMN2)
				.get();
		return RuntimeManagerFactory.Factory.get().newSingletonRuntimeManager(environment).getRuntimeEngine(null)
				.getKieSession();
	}

	private RuntimeManager getRuntimeManager(String process) {
		// load up the knowledge base
		JBPMHelper.startH2Server();
		JBPMHelper.setupDataSource();
		environment = RuntimeEnvironmentBuilder.Factory.get().newDefaultBuilder()
				.addAsset(KieServices.Factory.get().getResources().newClassPathResource(process), ResourceType.BPMN2)
				.get();
		return RuntimeManagerFactory.Factory.get().newSingletonRuntimeManager(environment);
	}

	// test procedure for kSessionType=getRuntimeManager
	public void main2(String[] args) {
		try {
			manager = getRuntimeManager("com/multipleinstance/multipleinstance.bpmn");
			runtime = manager.getRuntimeEngine(null);
			kSession = runtime.getKieSession();

			// start a new process instance
			Map<String, Object> params = new HashMap<String, Object>();
			List<String> list = new ArrayList<String>();
			list.add("krisv");
			list.add("john doe");
			list.add("superman");
			params.put("list", list);
			kSession.startProcess("com.sample.multipleinstance", params);

			TaskService taskService = runtime.getTaskService();
			List<TaskSummary> tasks = taskService.getTasksAssignedAsPotentialOwner("sales-rep", "en-UK");
			for (TaskSummary task : tasks) {
				System.out.println("Sales-rep executing task " + task.getName() + "(" + task.getId() + ": "
						+ task.getDescription() + ")");
				taskService.start(task.getId(), "sales-rep");
				taskService.complete(task.getId(), "sales-rep", null);
			}

			manager.disposeRuntimeEngine(runtime);
		} catch (Throwable t) {
			t.printStackTrace();
		}
		System.exit(0);
	}
	// test procedure for kSessionType=getRuntimeManager

	public String receive(DeviceEvent deviceEvent) {
		String response = "";
		ProcessInstance instance = null;

		try {
			// load up the knowledge base
			switch (this.kSessionType) {
			case "createKieSession":
				this.kSession = createKieSession(this.kSessionName);
				break;
			case "getKieSession":
				if (environment == null) {
					this.kSession = getKieSession(this.kSessionName);
				}
				break;
			case "getRuntimeManager":
				this.manager = getRuntimeManager(this.kSessionName);
				break;
			}
		} catch (Throwable t) {
			t.printStackTrace();
		}

		if (knowledgeDebug.indexOf("debug") != -1) {
			// KieSession ksession = this.createDefaultSession();
			kSession.addEventListener(new SystemOutProcessEventListener());
			kSession.addEventListener(new RuleAwareProcessEventLister());
			kSession.addEventListener(new TriggerRulesEventListener(kSession));
		}

		Devices device = this.devices.getDevice(deviceEvent.getId());
		if (device == null) {
			System.out.println("> id " + deviceEvent.search("id") + " : Extended IoT Device ID");
		} else {
			if (deviceEvent.search("name").equals("")) {
				deviceEvent.add("name", device.getName());
			}
			if (deviceEvent.search("event").equals("")) {
				if (deviceEvent.search("keypress").equals("")) {
					deviceEvent.add("event", "none");
				} else {
					deviceEvent.add("event", "keypress" + deviceEvent.search("keypress"));
				}
			}
		}

		if (knowledgeDebug.indexOf("none") == -1) {
			System.out.println("> TRACE " + deviceEvent.getDeviceTime() + " id " + device.getId() + "-"
					+ deviceEvent.getName() + " event " + deviceEvent.getEvent());
		}
		for (Devices devices : this.devices.getDevices()) {
			kSession.insert(devices);
		}
		kSession.insert(deviceEvent);

		try {
			// go! - fire rules
			long noOfRulesFired = this.kSession.fireAllRules();
			if (knowledgeDebug.indexOf("none") == -1) {
				System.out.println("> TRACE kSession no of Rules Fired: " + noOfRulesFired);
				System.out.println("> TRACE Number of facts in the session: " + kSession.getFactCount());
			}
			if (device != null) {
				MainWindow.getInstance().updateDevice(device.getId());
			}
			MainWindow.getInstance().updateEvent(deviceEvent);

			Map<String, Object> params = new HashMap<String, Object>();
			for (String key : deviceEvent.map.keySet()) {
				params.put(key, deviceEvent.map.get(key));
			}

			Map<String, Object> state = stateList.mapState();
			for (String key : state.keySet()) {
				params.put(key, state.get(key));
			}

			String rules_processID = stateList.getState("processID");
			if (rules_processID != null && !rules_processID.isEmpty()) {
				processID = rules_processID;
				droolsProcessID = true;
			}

			// go! - start jBPM processID
			if (processID != null && !processID.isEmpty()) {
				// Start the process with knowledge session
				instance = kSession.startProcess(processID, params);
			}
			if (instance.getState() != 2) {
				System.out.println(">>" + instance.getState());
			}

			if (droolsProcessID) {
				stateList.delState("processID");
				processID = _processID;
				droolsProcessID = false;
			}

			// Set response jBPM Global Variable List
			// kcontext.getKnowledgeRuntime().setGlobal("response", "");
			response = (String) kSession.getGlobal("response");

			switch (this.kSessionType) {
			case "createKieSession":
				kSession.dispose();
				break;
			case "getKieSession":
				// getKieSession(String bpmn);
				break;
			case "getRuntimeManager":
				environment.close();
				break;
			}
		} catch (Exception e) {
			System.err.println("Error: Unexpected exception caught: " + e.getMessage());
			e.printStackTrace();
		}
		return (response);
	}

	public void log(String message) {
		MainWindow.getInstance().log(message);
	}
}
