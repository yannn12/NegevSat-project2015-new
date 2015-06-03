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

public:
	int SunExposure;

	int getSample();
	void setSunExposure(int SunExposure);

	SunSensor();
	virtual ~SunSensor();
};

#endif /* SUNSENSOR_HPP_ */
