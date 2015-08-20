/*
 * BinTempsPacketTests.cpp
 *
 *  Created on: 20 баев 2015
 *      Author: Yaniv
 */

#include <data_protocol/binary_protocol/BinTempsPacket.hpp>
#include <tests/CommunicationTests/BinTempsPacketTests.hpp>

#include <climits>
#include <tests/CommunicationTests/ComTestUtils.hpp>
#include <tests/minunit.h>

char tempsmsg1[] = {2,0};

char tempsmsg2[] = {2,1,0,0,0,0,0,0,0,0,0,0,0,0};

char tempsmsg3[] = {2,2,0,0,0,0,0,0,0,0,0,0,0,0,
		ullMaxBytes[0],ullMaxBytes[1],ullMaxBytes[2],ullMaxBytes[3],ullMaxBytes[4],ullMaxBytes[5],ullMaxBytes[6],ullMaxBytes[7],
		intMaxBytes[0],intMaxBytes[1],intMaxBytes[2],intMaxBytes[3]};

char tempsmsg4[] = {2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		UCHAR_MAX,
		ullMaxBytes[0],ullMaxBytes[1],ullMaxBytes[2],ullMaxBytes[3],ullMaxBytes[4],ullMaxBytes[5],ullMaxBytes[6],ullMaxBytes[7],
		UCHAR_MAX};



BinTempsPacketTests::BinTempsPacketTests() {
	// TODO Auto-generated constructor stub

}

BinTempsPacketTests::~BinTempsPacketTests() {
	// TODO Auto-generated destructor stub
}

char* BinTempsPacketTests::runTests() {
	BinTempsPacket tempsPacket;
	vector<char> msg;
	TempSample ts1;
	TempSample ts2;
	TempSample ts3;

	initTempSample(ts1,0,0);
	initTempSample(ts2,ULLONG_MAX,INT_MAX);
	initTempSample(ts3,0,INT_MIN);

	tempsPacket.toBytes(msg);
	mu_assert("error, msg1 compare failed", arrayCompare(tempsmsg1,sizeof(tempsmsg1),&msg[0],msg.size()) == 0);

	tempsPacket.getTempSamples() .push_back(ts1);
	tempsPacket.toBytes(msg);
	mu_assert("error, msg2 compare failed", arrayCompare(tempsmsg2,sizeof(tempsmsg2),&msg[0],msg.size()) == 0);

	tempsPacket.getTempSamples().push_back(ts2);
	tempsPacket.toBytes(msg);
	mu_assert("error, msg3 compare failed", arrayCompare(tempsmsg3,sizeof(tempsmsg3),&msg[0],msg.size()) == 0);

	return 0;

}
