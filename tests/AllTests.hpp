/*
 * AllTests.hpp
 *
 *  Created on: May 25, 2014
 *      Author: boris
 */

#ifndef ALLTESTS_HPP_
#define ALLTESTS_HPP_

#include <stdio.h>
#include "minunit.h"
#include "CMDParserTests.hpp"
#include "TLMParserTests.hpp"
#include "XMLValidatorTests.hpp"
#include "SendTests.hpp"
#include "ReceiveTests.hpp"
#include "WorkQueueTests.hpp"
#include "SendReceiveQueueTests.hpp"

#include <tests/hardware2test/sensorsTest/AttitudeSensorTests.hpp>
#include <tests/hardware2test/sensorsTest/CurrentSensorTests.hpp>
#include <tests/hardware2test/sensorsTest/DodSensorTests.hpp>
#include <tests/hardware2test/sensorsTest/SunSensorTest.hpp>
#include <tests/hardware2test/sensorsTest/TemperatureSensorTest.hpp>

#include <tests/hardware2test/modulesTest/AttitudeControlTest.hpp>
#include <tests/hardware2test/modulesTest/ThermalControlTest.hpp>
#include <tests/hardware2test/modulesTest/AntennaTest.hpp>

#define ALL_TESTS					 	0xFFFF

#define CMD_PARSER_TESTS				0x0001
#define TLM_PARSER_TESTS				0x0002
#define SEND_TESTS						0x0004
#define VALIDATOR_TESTS					0x0008
#define WORK_QUEUE_TESTS				0x0010
#define SEND_RECEIVE_TESTS				0x0020
#define RECEIVE_TESTS					0x0040

#define ATTITUDE_SENSORE_TESTS			0x0080
#define DOD_SENSORE_TESTS		    	0x0100
#define SUN_SENSORE_TESTS		    	0x0200
#define TEMPERATURESENSOR_SENSORE_TESTS	0x0400
#define CURRENT_SENSORE_TESTS			0x0800

#define ATTITUDE_CONTROL_TESTS			0x1000
#define THERMAL_CONTROL_TESTS			0x2000
#define ANTENA_TESTS					0x4000

class AllTests {
private:
	int type_tests;
	CMDParserTests::CMDParserTests cmdtests;
	TLMParserTests::TLMParserTests tlmtests;
	ReceiveTests::ReceiveTests rcvtests;
	XMLValidatorTests::XMLValidatorTests validatortests;
	SendTests::SendTests sendtests;
	WorkQueueTests::WorkQueueTests workqueuetests;
	SendReceiveQueueTests::SendReceiveQueueTests sendreceivequeuetests;
	AttitudeSensorTests::AttitudeSensorTests attitudeSensortests;
	CurrentSensorTests::CurrentSensorTests currentSensorTests;
	DodSensorTests::DodSensorTests dodSensorTests;
	SunSensorTest::SunSensorTest sunSensorTest;
	TemperatureSensorTest::TemperatureSensorTest temperatureSensorTest;

	AttitudeControlTest::AttitudeControlTest attitudeControlTest;
	ThermalControlTest::ThermalControlTest thermalControlTest;
	AntennaTest::AntennaTest antennaTest;
public:
	AllTests(int _type);
	virtual ~AllTests();
	void run_all_tests();
	char* all_tests();
};

#endif /* ALLTESTS_HPP_ */
