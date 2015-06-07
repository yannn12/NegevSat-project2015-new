/*
 * CurrentSensor.hpp
 *
 *  Created on: 5 ???? 2015
 *      Author: hod amran
 */

#ifndef CURRENTSENSOR_HPP_
#define CURRENTSENSOR_HPP_
#include "ISensor.hpp"
using namespace std;
class CurrentSensor  : public ISensor {
private:
	int current;

public:
	int getSample(bool useI2C);
	void setValue(int val);
	CurrentSensor();
	virtual ~CurrentSensor();
};

#endif /* CURRENTSENSOR_HPP_ */
