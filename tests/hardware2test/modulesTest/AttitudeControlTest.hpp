/*
 * AttitudeControlTest.hpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#ifndef ATTITUDECONTROLTEST_HPP_
#define ATTITUDECONTROLTEST_HPP_

#include <hardware2/modules/AttitudeControlStub.hpp>
#include <hardware2/HardwareStub.hpp>
#include <tests/minunit.h>

class AttitudeControlTest {
private:

	AttitudeControlStub::AttitudeControlStub * attitudeControl;
	HardwareStub * hardware;
public:
	AttitudeControlTest();
	virtual ~AttitudeControlTest();
	char* runTests();
};

#endif /* ATTITUDECONTROLTEST_HPP_ */
