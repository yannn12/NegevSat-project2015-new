/*
 * AttitudeSensorTests.cpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <tests/hardware2test/sensorsTest/AttitudeSensorTests.hpp>

char* AttitudeSensorTests::runTests(){

		attitudeSensor->setValue(6);
		if(attitudeSensor->getSample(true)!=6){
			return fail_assert;
		}

		attitudeSensor->setValue(-6);
				if(attitudeSensor->getSample(true)!=-6){
					return fail_assert;
		}

		attitudeSensor->setValue(0);
				if(attitudeSensor->getSample(true)!=0){
					return fail_assert;
		}
		return 0;
}
AttitudeSensorTests::AttitudeSensorTests() {
	this->attitudeSensor = new AttitudeSensor();
}
AttitudeSensorTests::~AttitudeSensorTests() {
	// TODO Auto-generated destructor stub
}
