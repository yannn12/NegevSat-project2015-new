/*
 * AttitudeSensor.cpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/sensors/AttitudeSensor.hpp>

int AttitudeSensor::getSample(){
	return this->attitude;
}

void AttitudeSensor::setAttitude(int attitude){
	this->attitude=attitude;
}

AttitudeSensor::AttitudeSensor() {
	this->attitude=0;
}

AttitudeSensor::~AttitudeSensor() {
	// TODO Auto-generated destructor stub
}

