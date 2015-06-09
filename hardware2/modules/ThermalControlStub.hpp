/*
 * ThermalControlStub.hpp
 *
 *  Created on: 9 ???? 2015
 *      Author: hod amran
 */

#ifndef THERMALCONTROLSTUB_HPP_
#define THERMALCONTROLSTUB_HPP_
#include <hardware2/HardwareStub.hpp>
#include <hardware2/modules/ThermalControl.hpp>

class ThermalControlStub : public ThermalControl {
public:


	virtual void StartCooling();
	virtual void StopCooling();
	virtual void StartHeating();
	virtual void StopHeating();
	virtual void WorkCycle();
	ThermalControlStub(HardwareStub* hardware);
	virtual ~ThermalControlStub();
private:
	HardwareStub* hardware;
	int isCooling;
	int isHeating;
};

#endif /* THERMALCONTROLSTUB_HPP_ */
