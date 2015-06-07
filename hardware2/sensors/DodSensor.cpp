/*
 * DodSensor.cpp
 * DOD - Depth of Discharge Sensor.
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/sensors/DODSensor.hpp>

using namespace std;

int DodSensor::getSample(bool useI2C){
	if (useI2C){
	// will be implemented using read from i2c
		return this->dod;
		}
	else {
		return this->dod;
	}
}

void DodSensor::setValue(int val){
 this->dod=val;
}


DodSensor::DodSensor():ISensor("DepthOfDischarge") {
	this->dod=0;

}

DodSensor::~DodSensor() {
	// TODO Auto-generated destructor stub
}

