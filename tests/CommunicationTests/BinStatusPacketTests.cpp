/*
 * BinStatusPacketTests.cpp
 *
 *  Created on: 20 баев 2015
 *      Author: Yaniv
 */

#include <data_protocol/binary_protocol/BinStatusPacket.hpp>
#include <tests/CommunicationTests/BinStatusPacketTests.hpp>
#include <climits>
#include <tests/CommunicationTests/ComTestUtils.hpp>
#include <tests/minunit.h>

char statmsg1[] = {0,0};

char statmsg2[] = {0,1,0,0,0,0,0,0,0,0,0,0};

char statmsg3[] = {0,2,0,0,0,0,0,0,0,0,0,0,
		UCHAR_MAX,
		ullMaxBytes[0],ullMaxBytes[1],ullMaxBytes[2],ullMaxBytes[3],ullMaxBytes[4],ullMaxBytes[5],ullMaxBytes[6],ullMaxBytes[7],
		UCHAR_MAX};

char statmsg4[] = {1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		UCHAR_MAX,
		ullMaxBytes[0],ullMaxBytes[1],ullMaxBytes[2],ullMaxBytes[3],ullMaxBytes[4],ullMaxBytes[5],ullMaxBytes[6],ullMaxBytes[7],
		UCHAR_MAX};



BinStatusPacketTests::BinStatusPacketTests() {
	// TODO Auto-generated constructor stub

}

BinStatusPacketTests::~BinStatusPacketTests() {
	// TODO Auto-generated destructor stub
}

char* BinStatusPacketTests::runTests() {
	BinStatusPacket statPacket;
	vector<char> msg;
	ComponentInfo ci1;
	ComponentInfo ci2;
	ComponentInfo ci3;

	initComponenctInfo(ci1,0,0,0);
	initComponenctInfo(ci2,UCHAR_MAX,ULLONG_MAX,UCHAR_MAX);
	initComponenctInfo(ci3,UCHAR_MAX-1,ULLONG_MAX -1,UCHAR_MAX-1);
	statPacket.toBytes(msg);
	mu_assert("error, msg1 compare failed", arrayCompare(statmsg1,sizeof(statmsg1),&msg[0],msg.size()) == 0);

	statPacket.getComponentsInfo().push_back(ci1);
	statPacket.toBytes(msg);
	mu_assert("error, msg1 compare failed", arrayCompare(statmsg2,sizeof(statmsg2),&msg[0],msg.size()) == 0);
	statPacket.getComponentsInfo().push_back(ci2);
	statPacket.toBytes(msg);
	mu_assert("error, msg1 compare failed", arrayCompare(statmsg3,sizeof(statmsg3),&msg[0],msg.size()) == 0);

	return 0;




}
