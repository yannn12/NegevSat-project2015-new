/*
 * ThermalControlTest.cpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#include <tests/hardware2test/modulesTest/ThermalControlTest.hpp>

char* ThermalControlTest::runTests(){

	this->hardware->temperatureSensor->setValue(70);
	this->thermalControlStub->StartCooling();
	this->thermalControlStub->WorkCycle();

	if(hardware->temperatureSensor->getSample(true)!=69){
						return fail_assert;
	}
	this->thermalControlStub->StopCooling();



	this->hardware->temperatureSensor->setValue(-20);
	this->thermalControlStub->StartHeating();
	this->thermalControlStub->WorkCycle();

	if(hardware->temperatureSensor->getSample(true)!=-19){
						return fail_assert;
	}
	this->thermalControlStub->StopHeating();



	return 0;
}
ThermalControlTest::ThermalControlTest() {
	this->hardware =new HardwareStub();
	this->thermalControlStub = new ThermalControlStub(hardware);
}
ThermalControlTest::~ThermalControlTest() {
	// TODO Auto-generated destructor stub
}
