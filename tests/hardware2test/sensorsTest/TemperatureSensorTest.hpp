/*
 * TemperatureSensorTest.hpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#ifndef TEMPERATURESENSORTEST_HPP_
#define TEMPERATURESENSORTEST_HPP_
#include <hardware2/sensors/TemperatureSensor.hpp>
#include <tests/minunit.h>


class TemperatureSensorTest {
private:
	TemperatureSensor::TemperatureSensor * temperatureSensor;

public:
	TemperatureSensorTest();
	virtual ~TemperatureSensorTest();
	char* runTests();

};

#endif /* TEMPERATURESENSORTEST_HPP_ */
