/*
 * AttitudeSensor.cpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/sensors/AttitudeSensor.hpp>

int AttitudeSensor::getSample(bool useI2C){
	if (useI2C){
	// will be implemented using read from i2c
		return this->attitude;
		}
	else {
		return this->attitude;
	}

}

void AttitudeSensor::setValue(int val){
	this->attitude=val;
}

AttitudeSensor::AttitudeSensor():ISensor("Attitude") {
	this->attitude=0;
}

AttitudeSensor::~AttitudeSensor() {
	// TODO Auto-generated destructor stub
}

