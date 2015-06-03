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
using namespace std;

class HardwareStub {
private:
	ISensor::ISensor* temperatureSensor;
	ISensor::ISensor* dodSensor;
	ISensor::ISensor* attitudeSensor;
	ISensor::ISensor* sunlightSensor;

public:
	HardwareStub();
	virtual ~HardwareStub();
};

#endif /* HARDWARESTUB_HPP_ */
