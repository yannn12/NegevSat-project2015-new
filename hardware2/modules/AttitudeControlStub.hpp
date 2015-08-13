/*
 * AttitudeControlStub.hpp
 *
 *  Created on: 17 ???? 2015
 *      Author: hod amran
 */

#ifndef ATTITUDECONTROLSTUB_HPP_
#define ATTITUDECONTROLSTUB_HPP_

#include <hardware2/HardwareStub.hpp>
#include <hardware2/modules/AttitudeControl.hpp>


class AttitudeControlStub : public AttitudeControl {
public:
	virtual void StartReduceSpinRate();
	virtual void StopReduceSpinRate();
	virtual void StartIncreaseSpinRate();
	virtual void StopIncreaseSpinRate();
	virtual void WorkCycle();

	AttitudeControlStub(HardwareStub* hardware);
	virtual ~AttitudeControlStub();

private:
	HardwareStub* hardware;
	int isReducing;
	int isIncreasing;
};

#endif /* ATTITUDECONTROLSTUB_HPP_ */
