/*
 * Flag.hpp
 *
 *  Created on: 6 במאי 2015
 *      Author: Yaniv
 */

#ifndef FLAG_HPP_
#define FLAG_HPP_
#include <rtems++/rtemsSemaphore.h>

class Flag {
public:
	Flag();
	virtual ~Flag();
	bool getFlag();
	void setFlag(bool flag);

private:
	bool flag;
	rtems_id mutex_id;
};

#endif /* FLAG_HPP_ */
