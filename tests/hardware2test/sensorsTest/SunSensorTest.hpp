/*
 * SunSensorTest.hpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#ifndef SUNSENSORTEST_HPP_
#define SUNSENSORTEST_HPP_

#include <hardware2/sensors/SunSensor.hpp>
#include <tests/minunit.h>


class SunSensorTest {
private:
	SunSensor::SunSensor * sunSensor;

public:
	SunSensorTest();
	virtual ~SunSensorTest();
	char* runTests();

};

#endif /* SUNSENSORTEST_HPP_ */
