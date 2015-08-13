/*
 * AntennaTest.hpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#ifndef ANTENNATEST_HPP_
#define ANTENNATEST_HPP_


#include <hardware2/modules/Antenna.hpp>
#include <hardware2/HardwareStub.hpp>
#include <tests/minunit.h>


class AntennaTest {
private:

	Antenna::Antenna * antenna;
public:
	AntennaTest();
	virtual ~AntennaTest();
	char* runTests();

};

#endif /* ANTENNATEST_HPP_ */
