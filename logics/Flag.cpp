/*
 * Flag.cpp
 *
 *  Created on: 6 במאי 2015
 *      Author: Yaniv
 */

#include <logics/Flag.hpp>
#include <assert.h>

Flag::Flag() {
	rtems_status_code status;
	// create semaphore with 1 permit
	status = rtems_semaphore_create(
			rtems_build_name( 'F', 'L', 'G', '1' ),
			1,
			RTEMS_DEFAULT_ATTRIBUTES,
			0,
			&mutex_id
	);

	assert( status == RTEMS_SUCCESSFUL );

}

bool Flag::getFlag(){
	bool result;
	 rtems_semaphore_obtain(
			mutex_id,
			RTEMS_DEFAULT_OPTIONS,
			RTEMS_NO_TIMEOUT
	);

	 result = flag;


	 rtems_semaphore_release( mutex_id );
	 return result;
}
void Flag::setFlag(bool flag){
	 rtems_semaphore_obtain(
			mutex_id,
			RTEMS_DEFAULT_OPTIONS,
			RTEMS_NO_TIMEOUT
	);

	 this->flag = flag;


	 rtems_semaphore_release( mutex_id );
}

Flag::~Flag() {
	// TODO Auto-generated destructor stub
}

