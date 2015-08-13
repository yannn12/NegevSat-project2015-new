/*
 * CurrentSensorTests.cpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#include <tests/hardware2test/sensorsTest/CurrentSensorTests.hpp>

char* CurrentSensorTests::runTests(){

	currentSensor->setValue(6);
		if(currentSensor->getSample(true)!=6){
			return fail_assert;
		}

		currentSensor->setValue(-6);
				if(currentSensor->getSample(true)!=-6){
					return fail_assert;
		}

				currentSensor->setValue(0);
				if(currentSensor->getSample(true)!=0){
					return fail_assert;
		}
		return 0;
}
CurrentSensorTests::CurrentSensorTests() {
	this->currentSensor = new CurrentSensor();
}
CurrentSensorTests::~CurrentSensorTests() {
	// TODO Auto-generated destructor stub
}

