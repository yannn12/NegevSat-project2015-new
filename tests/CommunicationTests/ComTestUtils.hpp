#include <data_protocol/abstract_datatype/EnergyPacket.hpp>
#include <data_protocol/abstract_datatype/StatusPacket.hpp>
#include <data_protocol/abstract_datatype/TempsPacket.hpp>

extern char * intMaxBytes;

extern char * intMinBytes;

extern char * ullMaxBytes;

extern char * ullMinBytes;

int arrayCompare(char * arr1,int size1,char * arr2,int size2);

void initBattaryInfo(BattaryInfo& bi,unsigned long long time,int current,int voltage);

void initComponenctInfo(ComponentInfo& bi,unsigned char componentCode,unsigned long long time,unsigned char status);

void initTempSample(TempSample& bi,unsigned long long time,int temperature);
