/*
 * HardwareState.cpp
 *
 *  Created on: May 8, 2014
 *      Author: dariaz
 */

#include <hardware/HardwareState.hpp>
void HardwareState::SetHardware2(HardwareStub * hardware2){
	this->hardware2 =hardware2;
}

HardwareState::HardwareState(HardwareStub * hardware2) {
	// set initial states and values of modules
	this->hardware2 =hardware2;
	setEnergy((MIN_PROPER_VOLTAGE + MAX_PROPER_VOLTAGE)/2);
	setEnergyCurrent(MAX_PROPER_CURRENT);
	setEnergyStatus(MODULE_ON);

	setTemperature((MAX_PROPER_TEMPERATURE + MIN_PROPER_TEMPERATURE)/2);
	setTemperatureStatus(MODULE_ON);

	setPayload(1);
	setPayloadStatus(MODULE_STANDBY);
	setSband(1);
	setSbandStatus(MODULE_STANDBY);
	setSolarPanels(1);
	setSolarPanelsStatus(MODULE_ON);
	setThermalControl(1);
	setThermalControlStatus(MODULE_STANDBY);
}

HardwareState::HardwareState() {
	// set initial states and values of modules
	setEnergy((MIN_PROPER_VOLTAGE + MAX_PROPER_VOLTAGE)/2);
	setEnergyCurrent(MAX_PROPER_CURRENT);
	setEnergyStatus(MODULE_ON);

	setTemperature((MAX_PROPER_TEMPERATURE + MIN_PROPER_TEMPERATURE)/2);
	setTemperatureStatus(MODULE_ON);

	setPayload(1);
	setPayloadStatus(MODULE_STANDBY);
	setSband(1);
	setSbandStatus(MODULE_STANDBY);
	setSolarPanels(1);
	setSolarPanelsStatus(MODULE_ON);
	setThermalControl(1);
	setThermalControlStatus(MODULE_STANDBY);
}

HardwareState::~HardwareState() {
	// TODO Auto-generated destructor stub
}

int HardwareState::getStatus(int module){
	switch (module){
	case HW_ENERGY_MODULE:
		return hardware2->getStatus(HW_ENERGY_MODULE);
	case HW_PAYLOAD_MODULE:
		return getPayloadStatus();
	case HW_SBAND_MODULE:
		return getSbandStatus();
	case HW_SOLARP_MODULE:
		return getSolarPanelsStatus();
	case HW_TEMP_MODULE:
		return hardware2->getStatus(HW_TEMP_MODULE);
	case HW_TERMAL_CTRL_MODULE:
		return getThermalControlStatus();
	case HW_ATTITUDE_MODULE:
		return hardware2->getStatus(HW_ATTITUDE_MODULE);
	}
}

int HardwareState::getValue(int module, bool i2c){
	switch (module){
	case HW_ENERGY_MODULE:
		return hardware2->getValue(HW_ENERGY_MODULE,i2c);
	case HW_PAYLOAD_MODULE:
		return getPayload(i2c);
	case HW_SBAND_MODULE:
		return getSband(i2c);
	case HW_SOLARP_MODULE:
		return getSolarPanels(i2c);
	case HW_TEMP_MODULE:
		return hardware2->getValue(HW_TEMP_MODULE,i2c);
	case HW_TERMAL_CTRL_MODULE:
		return getThermalControl(i2c);
	case HW_ATTITUDE_MODULE:
			return hardware2->getValue(HW_ATTITUDE_MODULE,i2c);

	}
}

string HardwareState::getName(int module){
	switch (module){
	case HW_ENERGY_MODULE:
		return hardware2->getName(module);
	case HW_PAYLOAD_MODULE:
		return getPayloadName();
	case HW_SBAND_MODULE:
		return getSbandName();
	case HW_SOLARP_MODULE:
		return getSolarPanelsName();
	case HW_TEMP_MODULE:
		return hardware2->getName(module);
	case HW_TERMAL_CTRL_MODULE:
		return getThermalControlName();
	case HW_ATTITUDE_MODULE:
		return hardware2->getName(module);

	}
}
