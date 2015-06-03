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

int HardwareStub::getStatus(int module){
	switch (module){
	case HW_ENERGY_MODULE:
		return  dodSensor->getStatus();
	}
}
void HardwareStub::setStatus(int module,int  status){
		switch (module){
		case HW_ENERGY_MODULE:
		return dodSensor->setStatus(status);

	}
}
void HardwareStub::setValue(int module,int  value){
		switch (module){
		case HW_ENERGY_MODULE:
		return dodSensor->setValue(value);

	}
}

int HardwareStub::getValue(int module, bool i2c){
	switch (module){
	case HW_ENERGY_MODULE:
		return dodSensor->getSample(i2c);
	}
}

string HardwareStub::getName(int module){
	switch (module){
	case HW_ENERGY_MODULE:
		return dodSensor->getName();

	}
}


