/*
 * AttitudeControlStub.cpp
 *
 *  Created on: 17 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/modules/AttitudeControlStub.hpp>
#include <stdio.h>

AttitudeControlStub::AttitudeControlStub(HardwareStub* hardware) {
	this->hardware=hardware;
	this->isIncreasing=false;
	this->isReducing=false;
}


void AttitudeControlStub::StartReduceSpinRate() {
	if(!this->isReducing){
		printf("AttitudeControlStub Module - Start ReduceSpinRate\n");
		this->isReducing = true;
	}
}

void AttitudeControlStub::StopReduceSpinRate() {
	if(this->isReducing){
		printf("AttitudeControlStub Module - Stop ReduceSpinRate\n");
		this->isReducing = false;
	}
}

void AttitudeControlStub::StartIncreaseSpinRate() {
	if(!this->isIncreasing){
		printf("AttitudeControlStub Module - Start IncreaseSpinRate\n");
		this->isIncreasing = true;
	}
}

void AttitudeControlStub::StopIncreaseSpinRate() {
	if(this->isIncreasing){
		printf("AttitudeControlStub Module - Stop IncreaseSpinRate\n");
		this->isIncreasing = false;
	}
}

void AttitudeControlStub::WorkCycle() {

	int attitude = this->hardware->attitudeSensor->getSample(false);
	if(this->isReducing){
		attitude--;
		printf("AttitudeControlStub Module - Reducing Effect attitude is %d\n",attitude);
	}
	if(this->isIncreasing){
		attitude++;
		printf("AttitudeControlStub Module - Increasing Effect attitude is %d\n",attitude);
	}
	this->hardware->attitudeSensor->setValue(attitude);

}
AttitudeControlStub::~AttitudeControlStub() {
	// TODO Auto-generated destructor stub
}

