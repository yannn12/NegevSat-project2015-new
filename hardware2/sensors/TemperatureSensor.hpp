/*
 * TemperatureSensor.hpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#ifndef TEMPERATURESENSOR_HPP_
#define TEMPERATURESENSOR_HPP_
#include "ISensor.hpp"
using namespace std;

class TemperatureSensor: public ISensor {

public:
	int temperature;

	int getSample();
	void setTemperature(int temp);

	TemperatureSensor();
	virtual ~TemperatureSensor();


};



#endif /* TEMPERATURESENSOR_HPP_ */
