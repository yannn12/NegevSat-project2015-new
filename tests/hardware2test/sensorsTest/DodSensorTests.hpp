/*
 * DodSensorTests.hpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#ifndef DODSENSORTESTS_HPP_
#define DODSENSORTESTS_HPP_

#include <hardware2/sensors/DodSensor.hpp>
#include <tests/minunit.h>


class DodSensorTests {
private:
	DodSensor::DodSensor * dodSensor;

public:
	DodSensorTests();
	virtual ~DodSensorTests();
	char* runTests();

};

#endif /* DODSENSORTESTS_HPP_ */
