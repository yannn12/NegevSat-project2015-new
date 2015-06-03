/*
 * DodSensor.hpp
 *
 *  Depth of Discharge
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#ifndef DODSENSOR_HPP_
#define DODSENSOR_HPP_

#include "ISensor.hpp"
using namespace std;

//DOD - Depth of Discharge Sensor.

class DodSensor : public ISensor{

private:
	int dod;
public:
	int getSample(bool useI2C);
	void setValue(int val);

	DodSensor();
	virtual ~DodSensor();
};

#endif /* DODSENSOR_HPP_ */
