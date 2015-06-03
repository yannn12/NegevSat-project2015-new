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
public:

	int dod;

	int getSample();
	void setDod(int dod);

	DodSensor();
	virtual ~DodSensor();
};

#endif /* DODSENSOR_HPP_ */
