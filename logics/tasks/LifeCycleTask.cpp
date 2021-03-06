/*
 * LifeCycleTask.cpp
 *
 *  Created on: May 8, 2014
 *      Author: dariaz
 */

#include <data_protocol/abstract_datatype/PacketFactory.hpp>
#include <data_protocol/abstract_datatype/StatusPacket.hpp>
#include <logics/tasks/LifeCycleTask.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "utils/stringutils.hpp"
#include "logics/NegevSatConstants.hpp"
#include "logics/SendReceiveConf.hpp"
#include <rtems++/rtemsEvent.h>
#include "utils/timeutils.hpp"

using namespace timeutils;
using namespace std;
using namespace stringutils;

static int energy_value=45;
static int spinrate_value=15;

LifeCycleTask::LifeCycleTask(WorkQueue::WorkQueue* _rdy_works, SendReceiveQueue::SendReceiveQueue** _send_queues) {
	this->hardware.SetHardware2(&hardware2);  //#308458272
	rdy_works = _rdy_works;
	send_queues = _send_queues;
	samples_counter = 0;
	state = INIT_STATE;
	executor.setModulesRequest(&modules_request);
	sampler.setHardware(&hardware);
	sampler.setHardware2(&hardware2);
	enePacket = 0;
	statPacket = 0;
	tempsPacket = 0;
}

LifeCycleTask::~LifeCycleTask() {
	// TODO Auto-generated destructor stub
}

/**
 * Write the results of the algorithms calculation to I2C
 */
void LifeCycleTask::control_command(){
	//printf(" * LifeCycle TASK:: control_command *\n");
	if (state == SAFE_STATE){
		//int voltage = hardware.getEnergy(false);    #308458272
		int dod = hardware2.getValue(HW_ENERGY_MODULE,false);
		if (dod > MAX_DOD_FOR_EXITING_SAFE){
			dod--;
			printf(" * LifeCycle TASK:: control_command - CHARGING BATTERY DOD to  %d  *\n", dod);
			//hardware.setEnergy(voltage); #308458272
			hardware2.setValue(HW_ENERGY_MODULE,dod);
		}


		int attitude = hardware2.getValue(HW_ATTITUDE_MODULE,false);


		if (attitude > MIN_ATTITUDE_ENTERING_SAFE){
			hardware2.attitudeControler->StopIncreaseSpinRate();
			hardware2.attitudeControler->StartReduceSpinRate();

		}
		else if(attitude<MAX_ATTITUDE_ENTERING_SAFE){
			hardware2.attitudeControler->StopReduceSpinRate();
			hardware2.attitudeControler->StartIncreaseSpinRate();

		}
		else{
			hardware2.attitudeControler->StopReduceSpinRate();
			hardware2.attitudeControler->StopIncreaseSpinRate();
		}
		hardware2.setValue(HW_ATTITUDE_MODULE,attitude);


		int temperature = hardware2.getValue(HW_TEMP_MODULE,false);
		if (temperature > MAX_PROPER_TEMPERATURE){
			hardware2.thermalControl->StartCooling();
			hardware2.thermalControl->StopHeating();
		}
		else if (temperature < MIN_PROPER_TEMPERATURE){
			hardware2.thermalControl->StartHeating();
			hardware2.thermalControl->StopCooling();
		}
		else{
			hardware2.thermalControl->StopCooling();
			hardware2.thermalControl->StopHeating();
		}

	}
	hardware2.attitudeControler->WorkCycle();
	hardware2.thermalControl->WorkCycle();
	if (state == REGULAR_OPS_STATE || state == FACING_GROUND_STATE||state ==IDLE_STATE_EVENT){
		//printf(" * LifeCycle TASK:: control_command - EARTH POINTING *\n");
	}
	//in INIT and STANDBY modes no actions to take
}

/**
 * Perform algorithm - using the samples which were read in the control_unit_samples function and
 * perform computation
 */
void LifeCycleTask::control_algorithmics(){
	//printf(" * LifeCycle TASK:: control_algorithmics *\n");
}

/**
 * check on which state the satellite is atm
 */
void LifeCycleTask::obtain_state(){
	//printf(" * LifeCycle TASK:: obtain_state *\n");
	rtemsEvent event;
	rtems_event_set out;
	rtems_status_code status = event.receive(RTEMS_ALL_EVENTS, out, 0, rtemsEvent::no_wait, rtemsEvent::any);
	if (status == RTEMS_SUCCESSFUL){
		if (out & INIT_STATE_EVENT){
			state = INIT_STATE;
		}
		if (out & STANDBY_STATE_EVENT){
			state = STANDBY_STATE;
		}
		if (out & SAFE_STATE_EVENT){
			state = SAFE_STATE;
		}
		if (out & REGULAR_OPS_STATE_EVENT){
			state = REGULAR_OPS_STATE;
		}
		if (out & IDLE_STATE_EVENT){
			state = IDLE_STATE;
		}
		if (out & FACING_GROUND_STATE_EVENT){
			printf(" * LifeCycle TASK:: FACING GROUND! *\n");
			state = FACING_GROUND_STATE;
		}
	}
}

/**
 * Samples control unit - critical samples (read using I2C)
 */
void LifeCycleTask::control_unit_samples(){
	//EnergyPacket* enePacket
	//TempsPacket* tempsPacket;
	if(enePacket == 0){
		enePacket =  PacketFactory::factory->createEnergyPacket();
		tempsPacket =  PacketFactory::factory->createTempsPacket();
		statPacket= PacketFactory::factory->createStatusPacket();
	}

	if (samples_counter == 0){
		enePacket->getSamples().clear();
		tempsPacket->getTempSamples().clear();
	}
	statPacket->getComponentsInfo().clear();

	//StatusPacket* statusPacket= PacketFactory::factory->createStatusPacket();
	rtems_clock_get_tod( &current_time);
	BattaryInfo battary;															//$$$$
	TempSample tempSample;
	ComponentInfo compInfo;

	sampler.createEnergySample(battary);													//$$$$
	enePacket->getSamples().push_back(battary);
	sampler.createTempSample(tempSample);
	tempsPacket->getTempSamples().push_back(tempSample);


	sampler.createStatusSample(compInfo,Component::Sband);
	statPacket->getComponentsInfo().push_back(compInfo);
	sampler.createStatusSample(compInfo,Component::Temperature);
	statPacket->getComponentsInfo().push_back(compInfo);
	sampler.createStatusSample(compInfo,Component::Energy);								//$$$$
	statPacket->getComponentsInfo().push_back(compInfo);
	sampler.createStatusSample(compInfo,Component::SolarPanels);
	statPacket->getComponentsInfo().push_back(compInfo);
	sampler.createStatusSample(compInfo,Component::Payload);
	statPacket->getComponentsInfo().push_back(compInfo);
	sampler.createStatusSample(compInfo,Component::ThermalControl);
	statPacket->getComponentsInfo().push_back(compInfo);
	sampler.createStatusSample(compInfo,Component::Attitude);
	statPacket->getComponentsInfo().push_back(compInfo);

	samples_counter++;

	if (samples_counter == MAX_SAMPLES){
		vector<char> resultEne;
		vector<char> resultTemps;
		enePacket->toBytes(resultEne);
		tempsPacket->toBytes(resultTemps);
		//printf("ENERGY_STR:%s\n",&resultEne[0]);
		//printf("TEMPERATURE_STR:%s\n",&resultTemps[0]);
		send_queues[SENDQ_ENERGY_INDEX]->enqueue(resultEne);
		send_queues[SENDQ_TEMP_INDEX]->enqueue(resultTemps);
		samples_counter = 0;
	}
//	if(state == FACING_GROUND_STATE){
	vector<char> resultStatus;
	statPacket->toBytes(resultStatus);
	//printf("STATIC_STR:%s\n",&resultStatus[0]);
	send_queues[SENDQ_STATIC_INDEX]->enqueue(resultStatus);
//	}
	/*
	//printf(" * LifeCycle TASK:: control_unit_samples *\n");
	if (samples_counter == 0){
		parser.createPacket("",ENERGY_STR);
		parser.createPacket("", TEMPERATURE_STR);
	}
	parser.createPacket(state_to_chars(state),STATIC_STR);
	rtems_clock_get_tod( &current_time);
	unsigned long long time = time_to_long();
	// create energy sample
	Sample::Sample* energy_sample = sampler.createSample(ENERGY_STR, true, time, HW_ENERGY_MODULE);
	parser.addSampleToPacket(energy_sample,ENERGY_STR);
	// create temperature sample
	Sample::Sample* temp_sample = sampler.createSample(TEMPERATURE_STR, true, time, HW_TEMP_MODULE);
	parser.addSampleToPacket(temp_sample,TEMPERATURE_STR);

	// create static samples
	Sample::Sample* static_sband_sample = sampler.createSample(STATIC_STR, true, time, HW_SBAND_MODULE);
	parser.addSampleToPacket(static_sband_sample,STATIC_STR);
	Sample::Sample* static_temp_sample = sampler.createSample(STATIC_STR, true, time, HW_TEMP_MODULE);
	parser.addSampleToPacket(static_temp_sample,STATIC_STR);
	Sample::Sample* static_energy_sample = sampler.createSample(STATIC_STR, true, time, HW_ENERGY_MODULE);
	parser.addSampleToPacket(static_energy_sample,STATIC_STR);
	Sample::Sample* static_solarp_sample = sampler.createSample(STATIC_STR, true, time, HW_SOLARP_MODULE);
	parser.addSampleToPacket(static_solarp_sample,STATIC_STR);
	Sample::Sample* static_payload_sample = sampler.createSample(STATIC_STR, true, time, HW_PAYLOAD_MODULE);
	parser.addSampleToPacket(static_payload_sample,STATIC_STR);
	Sample::Sample* static_thermal_ctrl_sample = sampler.createSample(STATIC_STR, true, time, HW_TERMAL_CTRL_MODULE);
	parser.addSampleToPacket(static_thermal_ctrl_sample,STATIC_STR);

	samples_counter++;
	// when packets are filled with details push them into the send queues and remove them from
	// parser to prevent memory leak and keep the invariant that parser always keeps 3 packets ONLY!
	if (samples_counter == MAX_SAMPLES){
		string temp = parser.getPacket(ENERGY_STR)->packetToString();
		const char * temp2 = temp.c_str();
		printf("ENERGY_STR:%s\n",temp2);
		send_queues[SENDQ_ENERGY_INDEX]->enqueue(temp);
		parser.removePacket(ENERGY_STR);
		string temp3 = parser.getPacket(TEMPERATURE_STR)->packetToString();
		printf("TEMPERATURE_STR:%s\n",temp3.c_str());
		send_queues[SENDQ_TEMP_INDEX]->enqueue(temp3);
		parser.removePacket(TEMPERATURE_STR);
		samples_counter = 0;
	}
	string temp4 = parser.getPacket(STATIC_STR)->packetToString();
	printf("STATIC_STR:%s\n",temp4.c_str());
	send_queues[SENDQ_STATIC_INDEX]->enqueue(temp4);
	parser.removePacket(STATIC_STR);*/
}

void LifeCycleTask::attitude_control(int counter){
	//printf(" * LifeCycle TASK:: attitude_control *\n");
	if (counter == 0)
		control_unit_samples();
	control_algorithmics();
	control_command();
}

void LifeCycleTask::logics(){
	//printf(" * LifeCycle TASK:: logics *\n");
	rtemsEvent event;
	rtems_event_set out;
	//if (hardware.getEnergyStatus() == MODULE_MALFUNCTION){ 	#308458272
	if (hardware2.getStatus(HW_ENERGY_MODULE) == MODULE_MALFUNCTION && state!= SAFE_STATE ){
		out = MOVE_TO_SAFE_EVENT;
		event.send(*(task_table[STATE_MACHINE_TASK_INDEX]),out);
	}
	if (hardware2.getStatus(HW_ATTITUDE_MODULE) == MODULE_MALFUNCTION && state!= SAFE_STATE){
		out = MOVE_TO_SAFE_EVENT;
		event.send(*(task_table[STATE_MACHINE_TASK_INDEX]),out);
	}
	if (hardware2.getStatus(HW_TEMP_MODULE) == MODULE_MALFUNCTION && state!= SAFE_STATE){
			out = MOVE_TO_SAFE_EVENT;
			event.send(*(task_table[STATE_MACHINE_TASK_INDEX]),out);
	}
	//if (state == SAFE_STATE && hardware.getEnergyStatus() == MODULE_ON){ #308458272
	if (state == SAFE_STATE &&
			hardware2.getStatus(HW_ENERGY_MODULE) == MODULE_ON&&
			hardware2.getStatus(HW_ATTITUDE_MODULE) == MODULE_ON&&
			hardware2.getStatus(HW_TEMP_MODULE) == MODULE_ON){
		out = MOVE_TO_OP_EVENT;
		event.send(*(task_table[STATE_MACHINE_TASK_INDEX]),out);
	}
}

void LifeCycleTask::perform_cmd(){
	//printf(" * LifeCycle TASK:: perform_cmd *\n");
	WorkDescription::WorkDescription work = rdy_works->dequeue(false);
	if (work.getCode() != NULL_WORK)
		executor.execute(work);
}

void LifeCycleTask::monitoring(){
	//printf(" * LifeCycle TASK:: monitoring *\n");

	//int voltage = hardware.getEnergy(false); #308458272
	//int current = hardware.getEnergyCurrent(false); #308458272
	int dod =  hardware2.getValue(HW_ENERGY_MODULE,false);
	int current = hardware2.getValue(HW_CURRENT_MODULE,false);
	int attitude =hardware2.getValue(HW_ATTITUDE_MODULE,false);

	//int temp = hardware.getTemperature(false);#308458272
	int temp = hardware2.getValue(HW_TEMP_MODULE,false);
	//TODO check the condition of the samples (energy,temp and so on) and if the value is wrong
	//change something in order to invoke the right handling in the logics stage


	// dod monitoring:   ----------------------------

	/*if (voltage < MIN_PROPER_VOLTAGE || current < MIN_PROPER_CURRENT){ #308458272 i have wrote the 2 next "if"
		hardware.setEnergyStatus(MODULE_MALFUNCTION);
	}*/
	if (dod > MIN_DOD_FOR_ENTERING_SAFE){
			hardware2.setStatus(HW_ENERGY_MODULE,MODULE_MALFUNCTION);
	}
	else if (dod> MAX_DOD_FOR_EXITING_SAFE && dod <= MIN_DOD_FOR_ENTERING_SAFE){
				hardware2.setStatus(HW_ENERGY_MODULE,MODULE_MALFUNCTION);
	}
	else {
		hardware2.setStatus(HW_ENERGY_MODULE,MODULE_ON);
	}


	// attitude monitoring: ----------------------------

	if(attitude >= MAX_ATTITUDE_ENTERING_SAFE && attitude <= MIN_ATTITUDE_ENTERING_SAFE){
		hardware2.setStatus(HW_ATTITUDE_MODULE,MODULE_ON);
	}
	else{
		hardware2.setStatus(HW_ATTITUDE_MODULE,MODULE_MALFUNCTION);
	}


	// TEMPERATURE monitoring: ----------------------------

	/*if (temp > MAX_PROPER_TEMPERATURE){
		hardware.setTemperatureStatus(MODULE_MALFUNCTION); 	#308458272
	}*/
	if (temp > MAX_PROPER_TEMPERATURE){
			hardware2.setStatus(HW_TEMP_MODULE,MODULE_MALFUNCTION);
	}
	/*if (temp <= MAX_PROPER_TEMPERATURE){
			hardware.setTemperatureStatus(MODULE_ON); #308458272
	}*/
	if (temp <= MAX_PROPER_TEMPERATURE){
		hardware2.setStatus(HW_TEMP_MODULE,MODULE_ON);
	}
}

	/* YANIV HOD
	if (current < MIN_PROPER_CURRENT){
			hardware2.setStatus(HW_CURRENT_MODULE,HW_CURRENT_MODULE);
	}




	/*if (voltage >= MIN_PROPER_VOLTAGE){
		hardware.setEnergyStatus(MODULE_ON); #308458272
	}
	if (dod >= MIN_PROPER_VOLTAGE){
		hardware2.setStatus(HW_ENERGY_MODULE,MODULE_ON);
	}


	*/


void LifeCycleTask::module_ctrl(){

	//printf(" * LifeCycle TASK:: module ctrl *\n");

	if (state == SAFE_STATE){
		printf(" * LifeCycle TASK:: module ctrl - SAFE! turning off unneeded modules *\n");
		hardware.setPayloadStatus(MODULE_STANDBY);
		hardware.setSbandStatus(MODULE_STANDBY);
	}

	if(modules_request.get_payload_request() == TURN_ON
			&& (state == FACING_GROUND_STATE || state == REGULAR_OPS_STATE||state ==IDLE_STATE_EVENT)
	//		&& hardware.getTemperatureStatus() == MODULE_ON){ #308458272
	//		&& hardware2.getStatus(HW_TEMP_MODULE) == MODULE_ON){
		){
		hardware.setPayloadStatus(MODULE_ON);
		modules_request.request_payload(NO_CHANGE);
	}

	if (modules_request.get_payload_request() == STANDBY){
		hardware.setPayloadStatus(MODULE_STANDBY);
		modules_request.request_payload(NO_CHANGE);
	}

	if(modules_request.get_sband_request() == TURN_ON
			&& (state == FACING_GROUND_STATE || state == REGULAR_OPS_STATE||state ==IDLE_STATE_EVENT)
			//&& hardware.getTemperatureStatus() == MODULE_ON){	#308458272
		//	&& hardware2.getStatus(HW_TEMP_MODULE)== MODULE_ON){
		){
		hardware.setSbandStatus(MODULE_ON);
		modules_request.request_sband(NO_CHANGE);
	}

	if (modules_request.get_sband_request() == STANDBY){
		hardware.setSbandStatus(MODULE_STANDBY);
		modules_request.request_sband(NO_CHANGE);
	}

	if (modules_request.get_thermal_ctrl_request() == TURN_ON){
		hardware.setThermalControlStatus(MODULE_ON);
		modules_request.request_thermal_ctrl(NO_CHANGE);
	}

	if (modules_request.get_thermal_ctrl_request() == STANDBY){
		hardware.setThermalControlStatus(MODULE_STANDBY);
		modules_request.request_thermal_ctrl(NO_CHANGE);
	}


	// XXX SIMULATOR FIELDS XXX
	rtemsEvent event;
	rtems_event_set out;

	int high_temp = 50;
	int low_en = 0;

	if (modules_request.get_request_connected() == TURN_ON){
		//out = RECEIVED_COMMUNICATION_EVENT;
		//event.send(*(task_table[STATE_MACHINE_TASK_INDEX]),out);
		//modules_request.request_connected(NO_CHANGE);
	}
	if (modules_request.get_request_connected() == STANDBY){
		out = LOST_COMMUNICATION_EVENT;
		event.send(*(task_table[STATE_MACHINE_TASK_INDEX]),out);
		modules_request.request_connected(NO_CHANGE);
	}
	if (modules_request.get_request_set_energy() == TURN_ON){

	//	hardware.setEnergy(low_en);   #308458272
		hardware2.setValue(HW_ENERGY_MODULE,low_en);
		modules_request.request_set_energy(NO_CHANGE);
	}

	if (modules_request.get_request_set_energy_new() == TURN_ON){

		//	hardware.setEnergy(low_en);   #308458272
			hardware2.setValue(HW_ENERGY_MODULE,modules_request.get_energy_to_set());
			modules_request.request_set_energy_new(NO_CHANGE,0);
	}

	if (modules_request.get_request_set_temp() == TURN_ON){

		//hardware.setTemperature(high_temp);  #308458272
		hardware2.setValue(HW_TEMP_MODULE,high_temp);
		modules_request.request_set_temp(NO_CHANGE);
	}

	if (modules_request.get_attitude_new_request() == TURN_ON){

		//	hardware.setEnergy(low_en);   #308458272
			hardware2.setValue(HW_ATTITUDE_MODULE,modules_request.get_attitude_to_set());
			modules_request.request_set_attitude_new(NO_CHANGE,0);
	}
}

void LifeCycleTask::thermal_ctrl(){
	/*//printf(" * LifeCycle TASK:: thermal ctrl *\n");
	//if (hardware.getTemperatureStatus() == MODULE_MALFUNCTION){ #308458272
	if (hardware2.getStatus(HW_TEMP_MODULE)== MODULE_MALFUNCTION){
		printf(" * LifeCycle TASK:: thermal ctrl - module malfunction *\n");
		hardware.setThermalControlStatus(MODULE_ON);


		//int temp = hardware.getTemperature(false); #308458272
		int temp = hardware2.getValue(HW_TEMP_MODULE,false);
		temp--;
		//hardware.setTemperature(temp); #308458272
		hardware2.setValue(HW_TEMP_MODULE,temp);
		printf(" * LifeCycle TASK:: thermal ctrl - temp is now: %d *\n", temp);

	}
	//else if (hardware.getTemperatureStatus() == MODULE_ON){ #308458272
	else if (hardware2.getStatus(HW_TEMP_MODULE) == MODULE_ON){
		hardware.setThermalControlStatus(MODULE_STANDBY);
	}*/
}

void LifeCycleTask::body(rtems_task_argument argument){
	// TODO refactor each function into object
	int count = 0;
	for (;;){
		//printf(" * LifeCycle TASK! *\n");
		obtain_state();
		/*if (state != INIT_STATE){*/
		attitude_control(count); // collect samples and send packets
		logics(); 					//change stat if has problem
		perform_cmd();				//get command and execute (input)
		monitoring();				// check moduls stats and tell manufactions(change sensors status)
		module_ctrl(); 				// turn on or off modules
		thermal_ctrl();				//fix problem with temature
		count++; // this counter can be removed/modified - used to delay to samples rate (1/3 rounds)
		count = count % 3;
		/*}*/
	}
	exit(0);
}


