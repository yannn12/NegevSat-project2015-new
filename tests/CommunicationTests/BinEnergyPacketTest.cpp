/*
 * BinEnergyPacketTest.cpp
 *
 *  Created on: 20 баев 2015
 *      Author: Yaniv
 */

#include <data_protocol/abstract_datatype/EnergyPacket.hpp>
#include <data_protocol/binary_protocol/BinEnergyPacket.hpp>
#include <tests/CommunicationTests/BinEnergyPacketTest.hpp>
#include <tests/CommunicationTests/ComTestUtils.hpp>
#include <tests/minunit.h>
#include <climits>

char msg1[] = {1,0};

char msg2[] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

char msg3[] = {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		ullMaxBytes[0],ullMaxBytes[1],ullMaxBytes[2],ullMaxBytes[3],ullMaxBytes[4],ullMaxBytes[5],ullMaxBytes[6],ullMaxBytes[7],
		intMaxBytes[0],intMaxBytes[1],intMaxBytes[2],intMaxBytes[3],
		intMaxBytes[0],intMaxBytes[1],intMaxBytes[2],intMaxBytes[3]};

char msg4[] = {1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		ullMaxBytes[0],ullMaxBytes[1],ullMaxBytes[2],ullMaxBytes[3],ullMaxBytes[4],ullMaxBytes[5],ullMaxBytes[6],ullMaxBytes[7],
		intMaxBytes[0],intMaxBytes[1],intMaxBytes[2],intMaxBytes[3],
		intMaxBytes[0],intMaxBytes[1],intMaxBytes[2],intMaxBytes[3],
		ullMinBytes[0],ullMinBytes[1],ullMinBytes[2],ullMinBytes[3],ullMinBytes[4],ullMinBytes[5],ullMinBytes[6],ullMinBytes[7],
		intMinBytes[0],intMinBytes[1],intMinBytes[2],intMinBytes[3],
		intMinBytes[0],intMinBytes[1],intMinBytes[2],intMinBytes[3]};


BinEnergyPacketTest::BinEnergyPacketTest() {
	// TODO Auto-generated constructor stub

}

BinEnergyPacketTest::~BinEnergyPacketTest() {
	// TODO Auto-generated destructor stub
}

char* BinEnergyPacketTest::runTests() {
	BinEnergyPacket enePacket;
	vector<char> msg;
	vector<BattaryInfo> samples;
	BattaryInfo bi1;
	BattaryInfo bi2;
	BattaryInfo bi3;
	initBattaryInfo(bi1,0,0,0);
	initBattaryInfo(bi2,ULLONG_MAX,INT_MAX,INT_MAX);
	initBattaryInfo(bi3,0,INT_MIN,INT_MIN);
	enePacket.toBytes(msg);
	mu_assert("error, msg1 compare failed", arrayCompare(msg1,sizeof(msg1),&msg[0],msg.size()) == 0);

	samples.push_back(bi1);
	enePacket.setSamples(samples);
	enePacket.toBytes(msg);
	mu_assert("error, msg2 compare failed", arrayCompare(msg2,sizeof(msg2),&msg[0],msg.size()) == 0);

	samples.push_back(bi2);
	enePacket.setSamples(samples);
	enePacket.toBytes(msg);
	mu_assert("error, msg3 compare failed", arrayCompare(msg3,sizeof(msg3),&msg[0],msg.size()) == 0);

	samples.push_back(bi3);
	enePacket.setSamples(samples);
	enePacket.toBytes(msg);
	mu_assert("error, msg4 compare failed", arrayCompare(msg4,sizeof(msg4),&msg[0],msg.size()) == 0);

	return 0;
}
