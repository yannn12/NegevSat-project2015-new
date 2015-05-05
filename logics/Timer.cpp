/*
 * Timer.cpp
 *
 *  Created on: 5 במאי 2015
 *      Author: Yaniv
 */

#include <logics/Timer.hpp>

Timer::Timer(rtems_name name) {
	rtems_timer_create(name, &timerid);

}

rtems_status_code Timer::alarmTimer(rtems_interval ticks,rtems_timer_service_routine_entry routine,void *user_data){
	return rtems_timer_fire_after(
				timerid,
				ticks,
				routine,
				user_data
		  );
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

