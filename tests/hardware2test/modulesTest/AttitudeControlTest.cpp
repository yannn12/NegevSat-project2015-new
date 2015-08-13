/*
 * AttitudeControlTest.cpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#include <tests/hardware2test/modulesTest/AttitudeControlTest.hpp>


char* AttitudeControlTest::runTests(){




	hardware->attitudeSensor->setValue(50);
	this->attitudeControl->StartReduceSpinRate();
	this->attitudeControl->WorkCycle();

	if(hardware->attitudeSensor->getSample(true)!=49){
						return fail_assert;
	}
	this->attitudeControl->StopReduceSpinRate();



	this->hardware->attitudeSensor->setValue(-10);
	this->attitudeControl->StartIncreaseSpinRate();
	this->attitudeControl->WorkCycle();

	if(hardware->attitudeSensor->getSample(true)!=-9){
						return fail_assert;
	}
	this->attitudeControl->StopIncreaseSpinRate();



	return 0;
}
AttitudeControlTest::AttitudeControlTest() {
	this->hardware =new HardwareStub();
	this->attitudeControl = new AttitudeControlStub(hardware);
}
AttitudeControlTest::~AttitudeControlTest() {
	// TODO Auto-generated destructor stub
}
