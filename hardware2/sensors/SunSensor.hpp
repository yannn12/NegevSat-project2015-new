/*
 * SunSensor.hpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#ifndef SUNSENSOR_HPP_
#define SUNSENSOR_HPP_
#include "ISensor.hpp"
using namespace std;

class SunSensor: public ISensor {

private:
	int SunExposure;

public:
	int getSample(bool useI2C);
	void setValue(int val);

	SunSensor();
	virtual ~SunSensor();
};

#endif /* SUNSENSOR_HPP_ */
