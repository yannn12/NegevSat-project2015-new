/*
 * TemperatureSensor.cpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/sensors/TemperatureSensor.hpp>
using namespace std;

int TemperatureSensor::getSample(bool useI2C){
	if (useI2C){
		// will be implemented using read from i2c
			return this->temperature;
			}
		else {
			return this->temperature;
		}
}

void TemperatureSensor::setValue(int val){
 this->temperature=val;
}

TemperatureSensor::TemperatureSensor():ISensor("Exposure") {
	this->temperature=0;

}

TemperatureSensor::~TemperatureSensor() {
	// TODO Auto-generated destructor stub
}

