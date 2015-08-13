/*
 * TemperatureSensorTest.cpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#include <tests/hardware2test/sensorsTest/TemperatureSensorTest.hpp>

char* TemperatureSensorTest::runTests(){

	temperatureSensor->setValue(6);
		if(temperatureSensor->getSample(true)!=6){
			return fail_assert;
		}

		temperatureSensor->setValue(-6);
				if(temperatureSensor->getSample(true)!=-6){
					return fail_assert;
		}

				temperatureSensor->setValue(0);
				if(temperatureSensor->getSample(true)!=0){
					return fail_assert;
		}
		return 0;
}
TemperatureSensorTest::TemperatureSensorTest() {
	this->temperatureSensor = new TemperatureSensor();
}
TemperatureSensorTest::~TemperatureSensorTest() {
	// TODO Auto-generated destructor stub
}

