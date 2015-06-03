/*
 * SunSensor.cpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/sensors/SunSensor.hpp>


int SunSensor::getSample(){
	return this->SunExposure;
}

void SunSensor::setSunExposure(int SunExposure){
	this->SunExposure=SunExposure;
}
SunSensor::SunSensor() {
   this->SunExposure=0;

}

SunSensor::~SunSensor() {
	// TODO Auto-generated destructor stub
}

