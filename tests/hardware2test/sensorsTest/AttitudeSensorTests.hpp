/*
 * AttitudeSensorTests.hpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#ifndef ATTITUDESENSORTESTS_HPP_
#define ATTITUDESENSORTESTS_HPP_

#include <hardware2/sensors/AttitudeSensor.hpp>
#include <tests/minunit.h>


class AttitudeSensorTests {
private:
	AttitudeSensor::AttitudeSensor * attitudeSensor;

public:
	AttitudeSensorTests();
	virtual ~AttitudeSensorTests();
	char* runTests();
};

#endif /* ATTITUDESENSORTESTS_HPP_ */
