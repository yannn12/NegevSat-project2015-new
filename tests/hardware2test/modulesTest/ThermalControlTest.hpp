/*
 * ThermalControlTest.hpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#ifndef THERMALCONTROLTEST_HPP_
#define THERMALCONTROLTEST_HPP_

#include <hardware2/modules/ThermalControlStub.hpp>
#include <hardware2/HardwareStub.hpp>
#include <tests/minunit.h>

class ThermalControlTest {
private:

	ThermalControlStub::ThermalControlStub * thermalControlStub;
	HardwareStub * hardware;
public:
	ThermalControlTest();
	virtual ~ThermalControlTest();
	char* runTests();
};



#endif /* THERMALCONTROLTEST_HPP_ */
