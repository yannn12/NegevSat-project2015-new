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
	if(!this->isCooling){
		printf("ThermalControl Module - Start Cooling\n");
		this->isCooling = true;
	}
}

void ThermalControlStub::StopCooling() {
	if(this->isCooling){
		printf("ThermalControl Module - Stop Cooling\n");
		this->isCooling = false;
	}
}

void ThermalControlStub::StartHeating() {
	if(!this->isHeating){
		printf("ThermalControl Module - Start Heating\n");
		this->isHeating = true;
	}
}

void ThermalControlStub::StopHeating() {
	if(this->isHeating){
		printf("ThermalControl Module - Stop Heating\n");
		this->isHeating = false;
	}
}

void ThermalControlStub::WorkCycle() {
	int temp = this->hardware->temperatureSensor->getSample(false);
	if(this->isCooling){
		temp--;
		printf("ThermalControl Module - Cooling Effect Tempature is %d\n",temp);
	}
	if(this->isHeating){
		temp++;
		printf("ThermalControl Module - Heating Effect Tempature is %d\n",temp);
	}
	this->hardware->temperatureSensor->setValue(temp);

}

ThermalControlStub::~ThermalControlStub() {
	// TODO Auto-generated destructor stub
}

