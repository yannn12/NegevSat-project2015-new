/*
 * ThermalControl.hpp
 *
 *  Created on: 8 ???? 2015
 *      Author: hod amran
 */

#ifndef THERMALCONTROL_HPP_
#define THERMALCONTROL_HPP_

class ThermalControl {
	// TODO
public:
	virtual void StartCooling();
	virtual void StopCooling();
	virtual void StartHeating();
	virtual void StopHeating();

	virtual void WorkCycle(){}
	ThermalControl();
	virtual ~ThermalControl();

};

#endif /* THERMALCONTROL_HPP_ */
