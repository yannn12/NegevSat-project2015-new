/*
 * AttitudeControl.hpp
 *
 *  Created on: 17 ???? 2015
 *      Author: hod amran
 */

#ifndef ATTITUDECONTROL_HPP_
#define ATTITUDECONTROL_HPP_

class AttitudeControl {
	// TODO
public:
	virtual void StartReduceSpinRate()=0;
	virtual void StopReduceSpinRate()=0;
	virtual void StartIncreaseSpinRate()=0;
	virtual void StopIncreaseSpinRate()=0;
	virtual void WorkCycle()=0;

	virtual ~AttitudeControl(){}

};




#endif /* ATTITUDECONTROL_HPP_ */
