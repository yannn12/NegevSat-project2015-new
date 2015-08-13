/*
 * SunSensorTest.cpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#include <tests/hardware2test/sensorsTest/SunSensorTest.hpp>

char* SunSensorTest::runTests(){

	sunSensor->setValue(6);
		if(sunSensor->getSample(true)!=6){
			return fail_assert;
		}

		sunSensor->setValue(-6);
				if(sunSensor->getSample(true)!=-6){
					return fail_assert;
		}

				sunSensor->setValue(0);
				if(sunSensor->getSample(true)!=0){
					return fail_assert;
		}
		return 0;
}
SunSensorTest::SunSensorTest() {
	this->sunSensor = new SunSensor();
}
SunSensorTest::~SunSensorTest() {
	// TODO Auto-generated destructor stub
}
