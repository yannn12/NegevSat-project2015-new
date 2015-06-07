/*
 * CurrentSensor.cpp
 *
 *  Created on: 5 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/sensors/CurrentSensor.hpp>
using namespace std;

int CurrentSensor::getSample(bool useI2C){
	if (useI2C){
	// will be implemented using read from i2c
		return this->current;
		}
	else {
		return this->current;
	}
}

void CurrentSensor::setValue(int val){
 this->current=val;
}



CurrentSensor::CurrentSensor():ISensor("Current") {
	this->current=0;
}

CurrentSensor::~CurrentSensor() {
	// TODO Auto-generated destructor stub
}

