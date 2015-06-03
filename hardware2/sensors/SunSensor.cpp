/*
 * SunSensor.cpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/sensors/SunSensor.hpp>


int SunSensor::getSample(bool useI2C){
	if (useI2C){
	// will be implemented using read from i2c
		return this->SunExposure;
		}
	else {
		return this->SunExposure;
	}
}

void SunSensor::setValue(int val){
	this->SunExposure=val;
}
SunSensor::SunSensor():ISensor("Exposure") {
   this->SunExposure=0;

}

SunSensor::~SunSensor() {
	// TODO Auto-generated destructor stub
}

