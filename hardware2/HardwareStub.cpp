/*
 * HardwareStub.cpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/HardwareStub.hpp>
#include "sensors/AttitudeSensor.hpp"
#include "sensors/DodSensor.hpp"
#include "sensors/SunSensor.hpp"
#include "sensors/TemperatureSensor.hpp"

HardwareStub::HardwareStub() {
	this->attitudeSensor = new AttitudeSensor();
	this->dodSensor = new DodSensor();
	this->sunlightSensor = new SunSensor();
	this->temperatureSensor = new TemperatureSensor();
}

HardwareStub::~HardwareStub() {
	// TODO Auto-generated destructor stub
}

