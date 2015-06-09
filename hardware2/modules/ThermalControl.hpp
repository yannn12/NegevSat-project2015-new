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
	void StartCooling();
	void StopCooling();
	void StartHeating();
	void StopHeating();
	ThermalControl();
	virtual ~ThermalControl();
};

#endif /* THERMALCONTROL_HPP_ */
