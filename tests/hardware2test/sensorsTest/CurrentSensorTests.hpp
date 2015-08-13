/*
 * CurrentSensorTests.hpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#ifndef CURRENTSENSORTESTS_HPP_
#define CURRENTSENSORTESTS_HPP_


#include <hardware2/sensors/CurrentSensor.hpp>
#include <tests/minunit.h>

class CurrentSensorTests {

private:
	CurrentSensor::CurrentSensor * currentSensor;

public:
	CurrentSensorTests();
	virtual ~CurrentSensorTests();
	char* runTests();
};
#endif /* CURRENTSENSORTESTS_HPP_ */
