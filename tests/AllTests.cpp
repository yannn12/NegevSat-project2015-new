/*
 * AllTests.cpp
 *
 *  Created on: May 25, 2014
 *      Author: boris
 */

#include <tests/AllTests.hpp>

int tests_run = 0;

AllTests::AllTests(int _type) {
	type_tests = _type;
}

AllTests::~AllTests() {
	// TODO Auto-generated destructor stub
}

char* AllTests::all_tests(){

	if (type_tests & CMD_PARSER_TESTS)
		mu_run_test(cmdtests.runTests);
	if (type_tests & TLM_PARSER_TESTS)
		mu_run_test(tlmtests.runTests);
	if (type_tests & SEND_TESTS)
		mu_run_test(sendtests.runTests);
	if (type_tests & RECEIVE_TESTS)
		mu_run_test(rcvtests.runTests);
	if (type_tests & VALIDATOR_TESTS)
		mu_run_test(validatortests.runTests);
	if (type_tests & WORK_QUEUE_TESTS)
		mu_run_test(workqueuetests.runTests);
	if (type_tests & SEND_RECEIVE_TESTS)
		mu_run_test(sendreceivequeuetests.runTests);

	if(type_tests & ATTITUDE_SENSORE_TESTS){
		printf ("ATTITUDE_SENSORE_TESTS\n");
		mu_run_test(attitudeSensortests.runTests);
	}
	if(type_tests & DOD_SENSORE_TESTS){
			printf ("DOD_SENSORE_TESTS\n");
			mu_run_test(dodSensorTests.runTests);
	}
	if(type_tests & SUN_SENSORE_TESTS){
			printf ("SUN_SENSORE_TESTS\n");
			mu_run_test(sunSensorTest.runTests);
	}
	if(type_tests & TEMPERATURESENSOR_SENSORE_TESTS){
			printf ("TEMPERATURESENSOR_SENSORE_TESTS\n");
			mu_run_test(temperatureSensorTest.runTests);
	}
	if(type_tests & CURRENT_SENSORE_TESTS){
			printf ("CURRENT_SENSORE_TESTS\n");
			mu_run_test(currentSensorTests.runTests);
	}


	if(type_tests & ATTITUDE_CONTROL_TESTS){
			printf ("ATTITUDE_CONTROL_TESTS\n");
			mu_run_test(attitudeControlTest.runTests);
	}
	if(type_tests & THERMAL_CONTROL_TESTS){
			printf ("THERMAL_CONTROL_TESTS\n");
			mu_run_test(thermalControlTest.runTests);
	}
	if(type_tests & ANTENA_TESTS){
			printf ("ANTENA_TESTS\n");
			mu_run_test(antennaTest.runTests);
	}


	return 0;
}

void AllTests::run_all_tests(){
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);
}

