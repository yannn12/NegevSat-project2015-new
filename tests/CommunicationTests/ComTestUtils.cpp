#include <tests/CommunicationTests/ComTestUtils.hpp>
#include <climits>

int intMax = INT_MAX;
char * intMaxBytes =(char *) &intMax;

int intMin = INT_MIN;
char * intMinBytes = (char *) &intMin;

unsigned long long ullMax = ULLONG_MAX;
char * ullMaxBytes = (char *) &ullMax;

unsigned long long ullMin = 0;
char * ullMinBytes = (char *) &ullMin;

int arrayCompare(char * arr1,int size1,char * arr2,int size2){
	if(size1 != size2)
		return -1;

	for(int i=0;i<size1;i++){
		if(arr1[i]!=arr2[i])
			return -1;

	}
	return 0;

}


void initBattaryInfo(BattaryInfo& bi,unsigned long long time,int current,int voltage){
	bi.time = time;
	bi.current = current;
	bi.voltage = voltage;
}


void initComponenctInfo(ComponentInfo& ci,unsigned char componentCode,unsigned long long time,unsigned char status)
{
	ci.componentCode = componentCode;
	ci.time = time;
	ci.status = status;

}


void initTempSample(TempSample& bi,unsigned long long time,int temperature){
	bi.time = time;
	bi.temperature = temperature;

}
