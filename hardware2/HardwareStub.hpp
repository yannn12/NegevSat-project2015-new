/*
 * HardwareStub.hpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#ifndef HARDWARESTUB_HPP_
#define HARDWARESTUB_HPP_
#include "sensors/ISensor.hpp"
#include "sensors/AttitudeSensor.hpp"
#include "sensors/DodSensor.hpp"
#include "sensors/SunSensor.hpp"
#include "sensors/TemperatureSensor.hpp"

#define HW_ENERGY_MODULE				0
#define HW_PAYLOAD_MODULE				1
#define HW_SBAND_MODULE					2
#define HW_TEMP_MODULE					3
#define HW_SOLARP_MODULE				4
#define HW_TERMAL_CTRL_MODULE			5

#define TEMP_COEFFICIENT				5
#define MIN_PROPER_TEMPERATURE			0
#define MAX_PROPER_TEMPERATURE			40
#define MIN_PROPER_VOLTAGE				3
#define MAX_PROPER_VOLTAGE				5
#define MIN_PROPER_CURRENT				1
#define MAX_PROPER_CURRENT				2

class HardwareStub {
private:
	ISensor::ISensor* temperatureSensor;
	ISensor::ISensor* dodSensor;
	ISensor::ISensor* attitudeSensor;
	ISensor::ISensor* sunlightSensor;

public:
	int getStatus(int module);
	int getValue(int module, bool i2c);
	string getName(int module);
	void setValue(int module,int  value);
	void setStatus(int module,int  status);
	HardwareStub();
	virtual ~HardwareStub();
};

#endif /* HARDWARESTUB_HPP_ */
