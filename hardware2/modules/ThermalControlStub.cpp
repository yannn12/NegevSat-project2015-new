/*
 * ThermalControlStub.cpp
 *
 *  Created on: 9 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/modules/ThermalControlStub.hpp>
#include <stdio.h>

ThermalControlStub::ThermalControlStub(HardwareStub* hardware) {
	this->hardware = hardware;
	this->isCooling = false;
	this->isHeating = false;

}

void ThermalControlStub::StartCooling() {
	printf("ThermalControl Module - Start Cooling");
	this->isCooling = true;
}

void ThermalControlStub::StopCooling() {
	printf("ThermalControl Module - Stop Cooling");
	this->isCooling = false;
}

void ThermalControlStub::StartHeating() {
	printf("ThermalControl Module - Start Heating");
	this->isHeating = true;
}

void ThermalControlStub::StopHeating() {
	printf("ThermalControl Module - Stop Heating");
	this->isHeating = false;
}

void ThermalControlStub::WorkCycle() {
	int temp = this->hardware->temperatureSensor->getSample(false);
	if(this->isCooling){
		temp--;
		printf("ThermalControl Module - Cooling Effect Tempature is %d",temp);
	}
	if(this->isHeating){
		temp++;
		printf("ThermalControl Module - Heating Effect Tempature is %d",temp);
	}
	this->hardware->temperatureSensor->setValue(temp);

}

ThermalControlStub::~ThermalControlStub() {
	// TODO Auto-generated destructor stub
}

