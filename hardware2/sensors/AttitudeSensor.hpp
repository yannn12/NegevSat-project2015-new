/*
 * AttitudeSensor.hpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#ifndef ATTITUDESENSOR_HPP_
#define ATTITUDESENSOR_HPP_
#include "ISensor.hpp"
using namespace std;

class AttitudeSensor: public ISensor  {
public:

	int attitude;
	int getSample();
	void setAttitude(int attitude);

	AttitudeSensor();
	virtual ~AttitudeSensor();
};

#endif /* ATTITUDESENSOR_HPP_ */
