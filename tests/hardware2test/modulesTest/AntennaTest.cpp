/*
 * AntennaTest.cpp
 *
 *  Created on: 13 ???? 2015
 *      Author: hod amran
 */

#include <tests/hardware2test/modulesTest/AntennaTest.hpp>


char* AntennaTest::runTests(){

	antenna->Open();
	if(!antenna->getStatus()){
			return fail_assert;
	}

	antenna->Close();
		if(antenna->getStatus()){
			return fail_assert;
	}

	antenna->TurnOn();
		if(!antenna->getPower()){
			return fail_assert;
	}

	antenna->TurnOff();
		if(antenna->getPower()){
			return fail_assert;
	}


	return 0;
}
AntennaTest::AntennaTest() {
	this->antenna = new Antenna();
}
AntennaTest::~AntennaTest() {
	// TODO Auto-generated destructor stub
}
