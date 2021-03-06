/*
 * HardwareStub.cpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/HardwareStub.hpp>
#include <hardware2/modules/ThermalControlStub.hpp>
#include <hardware2/modules/AttitudeControlStub.hpp>
#include "sensors/AttitudeSensor.hpp"
#include "sensors/DodSensor.hpp"
#include "sensors/SunSensor.hpp"
#include "sensors/TemperatureSensor.hpp"
#include "sensors/CurrentSensor.hpp"

HardwareStub::HardwareStub() {
	this->attitudeSensor = new AttitudeSensor();
	this->dodSensor = new DodSensor();
	this->sunlightSensor = new SunSensor();
	this->temperatureSensor = new TemperatureSensor();
	this->currentSensor = new CurrentSensor();
	this->thermalControl = new ThermalControlStub(this);
	this->attitudeControler=new AttitudeControlStub(this);
	this->antenna = new Antenna();
}

HardwareStub::~HardwareStub() {
	// TODO Auto-generated destructor stub
}

int HardwareStub::getStatus(int module){
	switch (module){
	case HW_ENERGY_MODULE:
		return  dodSensor->getStatus();
	case HW_CURRENT_MODULE:
		return  currentSensor->getStatus();
	case HW_ATTITUDE_MODULE:
		return attitudeSensor->getStatus();
	case HW_TEMP_MODULE:
		return temperatureSensor->getStatus();
	}
}

void HardwareStub::setStatus(int module,int  status){
	switch (module){
	case HW_ENERGY_MODULE:
		return dodSensor->setStatus(status);
	case HW_CURRENT_MODULE:
		return  currentSensor->setStatus(status);
	case HW_ATTITUDE_MODULE:
		return attitudeSensor->setStatus(status);
	case HW_TEMP_MODULE:
		return temperatureSensor->setStatus(status);
	}
}
void HardwareStub::setValue(int module,int  value){
	switch (module){
	case HW_ENERGY_MODULE:
		return dodSensor->setValue(value);
	case HW_CURRENT_MODULE:
		return  currentSensor->setValue(value);
	case HW_ATTITUDE_MODULE:
		return attitudeSensor->setValue(value);
	case HW_TEMP_MODULE:
		return temperatureSensor->setValue(value);
	}
}

int HardwareStub::getValue(int module, bool i2c){
	switch (module){
	case HW_ENERGY_MODULE:
		return dodSensor->getSample(i2c);
	case HW_CURRENT_MODULE:
		return  currentSensor->getSample(i2c);
	case HW_ATTITUDE_MODULE:
		return attitudeSensor->getSample(i2c);
	case HW_TEMP_MODULE:
		return temperatureSensor->getSample(i2c);
	}
}

string HardwareStub::getName(int module){
	switch (module){
	case HW_ENERGY_MODULE:
		return dodSensor->getName();
	case HW_CURRENT_MODULE:
		return  currentSensor->getName();
	case HW_ATTITUDE_MODULE:
		return attitudeSensor->getName();
	case HW_TEMP_MODULE:
		return temperatureSensor->getName();
	}
}


