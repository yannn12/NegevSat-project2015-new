/*
 * StateMachineTask.cpp
 *
 *  Created on: May 20, 2014
 *      Author: boris
 */

#include <logics/tasks/StateMachineTask.hpp>
#include "third_party/Macho.hpp"
#include <stdio.h>
#include "logics/NegevSatConstants.hpp"
#include <rtems++/rtemsEvent.h>
#include "logics/Global.hpp"
#include <stdlib.h>
#include "logics/Timer.hpp"
#include "logics/Flag.hpp"
#include <rtems++/rtemsSemaphore.h>
#define ROUNDS_TO_RESEND		10

// Basic state machine of the satellite
namespace Satellite {

Flag flag;


rtems_timer_service_routine Timer_Routine( rtems_id id, void *ignored )
{

	flag.setFlag(true);


}
//////////////////////////////////////////////////////////////////////
// State declarations

// Machine's top state
TOPSTATE(Top) {

	// Top state data (visible to all substates)
	struct Box {
		Box() : state(INIT_STATE), counter(0),timer(rtems_build_name( 'T', 'M', 'R', '1' )) {

		}
		rtems_status_code alarmTimer(rtems_interval ticks,rtems_timer_service_routine_entry routine,void *user_data){
			timer.alarmTimer(ticks,routine,user_data);
		}

		void send_event(int type, int index) {
			rtems_event_set out;
			out = type;
			rtems_status_code status = event.send(*(task_table[index]),out);
			//printf(" * StateMachine TASK:: send event returned with %d *\n", status);
		}

		rtems_event_set receive_event(){
			rtems_event_set out;
			// TODO consider adding timeout to wait for receive
			rtems_status_code status = event.receive(RTEMS_ALL_EVENTS , out, 0, rtemsEvent::no_wait, rtemsEvent::any);
			if (status != RTEMS_SUCCESSFUL){
				return NO_EVENT_RECEIVED;
			}
			return out;
		}

		bool increase_counter (){
			counter++;
			counter = counter % ROUNDS_TO_RESEND;
			if (counter == 0)
				return true;
			return false;
		}

		void reset_counter(){
			counter = 0;
		}
	public:
		Timer timer;
	private:
		int state;
		int counter;
		rtemsEvent event;

	};

	STATE(Top)

	// Machine's event protocol
	virtual void work() {}		// Do operations

private:
	// Initial init action
	void init();
};

// Satellite's initialize state
SUBSTATE(InitState, Top) {
	STATE(InitState)

	void work();

private:
	void init();
};


// Satellite is ready to work
SUBSTATE(Operational, Top) {
	STATE(Operational)

	void work();

private:
	void init();
};

// Satellite is facing the ground station - doing autonomous operations and sending telemetry
SUBSTATE(FacingGroundStation, Top) {
	STATE(FacingGroundStation)

	void work();

private:
	void init();
};

// Satellite is not facing the ground station and doing autonomous operations
SUBSTATE(RegularOperations, Operational) {
	STATE(RegularOperations)

	void work();

private:
	void init();
};

SUBSTATE(Idle, Operational) {
	STATE(Idle)

	void work();

private:
	void init();
};

// Satellite is in safe mode
SUBSTATE(Safe, Top) {
	STATE(Safe)

	void work();

private:
	void init();
};

// Satellite is in standby mode
SUBSTATE(Standby, Top) {
	STATE(Standby)

	void work();

private:
	void init();
};

//////////////////////////////////////////////////////////////////////
// Event handler and box implementations

// Top state
void Top::init() {
	//printf(" * StateMachine TASK:: TopState::init *\n");
	setState<InitState>();
}

// InitState state
void InitState::init() {
	printf(" * StateMachine TASK:: Entering Launch Mode *\n");
	flag.setFlag(false);
	printf("* Start 30 Minutes Timer *\n");
	// TODO check
	TOP::box().alarmTimer(TIME_FACTOR_LAUNCH_MODE*30 *60* rtems_clock_get_ticks_per_second(),Timer_Routine,NULL);
}

void InitState::work() {
	//printf(" * StateMachine TASK:: InitState::work *\n");
	if(flag.getFlag() == true){
		printf("* Timer Elapsed *\n");
		setState<Operational>();
		return;
	}
}
// State Operational
void Operational::init() {
	printf(" * StateMachine TASK:: Entering Operational State *\n");

}
void Operational::work(){
	//printf(" * StateMachine TASK:: Operational::work *\n");
	setState<Idle>();
}

// State Operational
void Idle::init() {
	printf(" * StateMachine TASK:: Entering Idle State *\n");
	TOP::box().reset_counter();
	for (int i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(IDLE_STATE_EVENT, i);
	}



}
void Idle::work(){


	rtems_event_set set = TOP::box().receive_event();
	//printf(" * StateMachine TASK:: Operational::work *\n");
	if (set != NO_EVENT_RECEIVED){
		if (set & START_EXPIRIMENT_EVENT){
			setState<RegularOperations>();
		}
		else if (set & RECEIVED_COMMUNICATION_EVENT){
			setState<FacingGroundStation>();
		}
	}
	if (TOP::box().increase_counter()){
		for (int i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
			TOP::box().send_event(IDLE_STATE_EVENT, i);
		}
	}
}

// State RegularOperations
void RegularOperations::init() {
	printf(" * StateMachine TASK:: Entering RegularOperations State *\n");
	TOP::box().reset_counter();
	for (int i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(REGULAR_OPS_STATE_EVENT, i);
	}
	rtems_id timerid;
	flag.setFlag(false);
	printf(" * StateMachine TASK:: Start 2.5 Minuts timer *\n");
	// TODO check
	TOP::box().alarmTimer(TIME_FACTOR*2.5 *60* rtems_clock_get_ticks_per_second(),Timer_Routine,NULL);

}

void RegularOperations::work() {
	if(flag.getFlag() == true){
		printf("* Timer Elapsed *\n");
		setState<Idle>();
		return;
	}
	//printf(" * StateMachine TASK:: RegularOperations::work *\n");
	rtems_event_set set = TOP::box().receive_event();
	//printf(" * StateMachine TASK:: set received: %d *\n", (int)set);
	if (set != NO_EVENT_RECEIVED){
		if (set & MOVE_TO_SAFE_EVENT){
			setState<Safe>();
		}
		else if (set & RECEIVED_COMMUNICATION_EVENT){
			setState<FacingGroundStation>();
		}
		else if (set & MOVE_TO_STANDBY_EVENT){
			setState<Standby>();
		}
	}
	if (TOP::box().increase_counter()){
		for (int i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
			TOP::box().send_event(REGULAR_OPS_STATE_EVENT, i);
		}
	}
}

// State FacingGroundStation
void FacingGroundStation::init() {
	printf(" * StateMachine TASK:: Entering FacingGroundStation State *\n");
	TOP::box().reset_counter();
	for (int i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(FACING_GROUND_STATE_EVENT, i);
	}
	flag.setFlag(false);
	printf(" * StateMachine TASK:: Start 4 Minuts timer *\n");
	// TODO check
	TOP::box().alarmTimer(TIME_FACTOR*9 *60* rtems_clock_get_ticks_per_second(),Timer_Routine,NULL);

}

void FacingGroundStation::work() {
	if(flag.getFlag() == true){
		printf("* Timer Elapsed *\n");
		setState<Safe>();
		return;
	}
	//printf(" * StateMachine TASK:: FacingGroundStation::work *\n");
	rtems_event_set set = TOP::box().receive_event();
	//printf(" * StateMachine TASK:: set received: %d *\n", (int)set);
	if (set != NO_EVENT_RECEIVED){
		if (set & MOVE_TO_SAFE_EVENT){
			setState<Safe>();
		}
		else if (set & LOST_COMMUNICATION_EVENT){
			setState<RegularOperations>();
		}
		else if (set & MOVE_TO_STANDBY_EVENT){
			setState<Standby>();
		}
	}
	if (TOP::box().increase_counter()){
		for (int i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
			TOP::box().send_event(FACING_GROUND_STATE_EVENT, i);
		}
	}
}

// State Safe
void Safe::init() {
	printf(" * StateMachine TASK:: Entering Safe State *\n");
	TOP::box().reset_counter();
	for (int i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(SAFE_STATE_EVENT, i);
	}
}

void Safe::work() {
	//printf(" * StateMachine TASK:: FacingGroundStation::work *\n");

	//todo cancel
	printf(" * The System Is OK Exiting Safe *\n");
	setState<Operational>();
	return;

	rtems_event_set set = TOP::box().receive_event();
	if (set != NO_EVENT_RECEIVED){
		if (set & MOVE_TO_OP_EVENT){
			setState<Operational>();
		}
		else if (set & MOVE_TO_STANDBY_EVENT){
			setState<Standby>();
		}
	}
	if (TOP::box().increase_counter()){
		for (int i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
			TOP::box().send_event(REGULAR_OPS_STATE_EVENT, i);
		}
	}
}

// State Standby
void Standby::init() {
	printf(" * StateMachine TASK:: Entering Standby State *\n");
	TOP::box().reset_counter();
	for (int i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(STANDBY_STATE_EVENT, i);
	}
}

void Standby::work() {
	//printf(" * StateMachine TASK:: Standby::work *\n");
	rtems_event_set set = TOP::box().receive_event();
	if (set != NO_EVENT_RECEIVED){
		if (set & MOVE_TO_STANDBY_EVENT){
			setState<Standby>();
		}
	}
	if (TOP::box().increase_counter()){
		for (int i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
			TOP::box().send_event(REGULAR_OPS_STATE_EVENT, i);
		}
	}
}

} // namespace Satellite


StateMachineTask::StateMachineTask() {
	// TODO Auto-generated constructor stub

}

StateMachineTask::~StateMachineTask() {
	// TODO Auto-generated destructor stub
}

void StateMachineTask::body(rtems_task_argument argument){

	Macho::Machine<Satellite::Top> m;
	rtems_id timerid =0;



	for (;;){

		m->work();

		rtems_task_wake_after(
					1 * 2 * rtems_clock_get_ticks_per_second());

	}
	exit(0);
}
