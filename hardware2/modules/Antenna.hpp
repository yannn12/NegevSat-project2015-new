/*
 * Antenna.hpp
 *
 *  Created on: 8 ???? 2015
 *      Author: hod amran
 */

#ifndef ANTENNA_HPP_
#define ANTENNA_HPP_

class Antenna {
	bool status; // true if open, false if close.
	bool power;   // true if on, false if off.

public:
	void Open();
	void Colse();
	void TurnOn();
	void TurnOff();
	Antenna();
	virtual ~Antenna();
};

#endif /* ANTENNA_HPP_ */
