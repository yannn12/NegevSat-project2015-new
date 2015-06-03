/*
 * TemperatureSensor.cpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/sensors/TemperatureSensor.hpp>
using namespace std;

int TemperatureSensor::getSample(){
 return this->temperature;
}

void TemperatureSensor::setTemperature(int temp){
 this->temperature=temp;
}

TemperatureSensor::TemperatureSensor() {
	this->temperature=0;

}

TemperatureSensor::~TemperatureSensor() {
	// TODO Auto-generated destructor stub
}

