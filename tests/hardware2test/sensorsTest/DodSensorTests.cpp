/*
 * DodSensorTests.cpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#include <tests/hardware2test/sensorsTest/DodSensorTests.hpp>

char* DodSensorTests::runTests(){

	dodSensor->setValue(6);
		if(dodSensor->getSample(true)!=6){
			return fail_assert;
		}

		dodSensor->setValue(-6);
				if(dodSensor->getSample(true)!=-6){
					return fail_assert;
		}

				dodSensor->setValue(0);
				if(dodSensor->getSample(true)!=0){
					return fail_assert;
		}
		return 0;
}
DodSensorTests::DodSensorTests() {
	this->dodSensor = new DodSensor();
}
DodSensorTests::~DodSensorTests() {
	// TODO Auto-generated destructor stub
}
