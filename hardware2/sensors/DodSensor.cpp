/*
 * DodSensor.cpp
 * DOD - Depth of Discharge Sensor.
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/sensors/DODSensor.hpp>

using namespace std;

int DodSensor::getSample(){
 return this->dod;
}

void DodSensor::setDod(int dod){
 this->dod=dod;
}

DodSensor::DodSensor() {
	this->dod=0;

}

DodSensor::~DodSensor() {
	// TODO Auto-generated destructor stub
}

