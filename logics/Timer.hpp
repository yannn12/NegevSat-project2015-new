/*
 * Timer.hpp
 *
 *  Created on: 5 במאי 2015
 *      Author: Yaniv
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_


//#include <rtems++/rtemsEvent.h>
#include <rtems++/rtemsTimer.h>
#include <rtems++/rtemsInterrupt.h>
class Timer {
public:
	Timer(rtems_name name);
	virtual ~Timer();
	rtems_status_code alarmTimer(rtems_interval ticks,rtems_timer_service_routine_entry,void *user_data);
private:
	rtems_id timerid;
};

#endif /* TIMER_HPP_ */
