// dlltest.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#pragma comment(lib,"DevicePerformance.lib")
#include "DevicePerformance.h"
#using "GetCPUTemperature.dll"
using namespace std;
using namespace GetCPUTemperature;


int _tmain(int argc, _TCHAR* argv[])
{
	std::string strSystemId = "";
	std::string strErrMsg   = "";
	int i = get_system_id(strSystemId, strErrMsg);
	std::cout << " system id :  "<< strSystemId  << ",Return Value: "<<i <<std::endl;

	int cpuUsage          = 0;
	int cpuVal = get_cpu_usage(cpuUsage, strErrMsg);
	std::cout << " cpu :  "<< cpuUsage  << ",Return Value: "<<cpuVal <<std::endl;

	int memoryUsage       = 0;
	int memVal = get_memory_usage(memoryUsage,strErrMsg);
	std::cout << " memory_usage :  "<< memoryUsage  << ",Return Value: "<<memVal <<std::endl;

	int diskUsage         = 0;
	int diskVal = get_disk_usage(diskUsage, strErrMsg);
	std::cout << " get_disk_usage :  "<< diskUsage  << ",Return Value: "<<diskVal <<std::endl;

	int iTemperature      = 0;
	int val = get_device_temperature(iTemperature,"", strErrMsg);
	std::cout << " get_device_temperature :  "<< iTemperature << ",Return Value: "<<val <<std::endl;

	unsigned long send    = 0;
	int sendVal = get_device_send_bytes(send,"6F425DF0-B5C1-4430-A836-D134B57D112A",strErrMsg);
	std::cout << " get_device_send_bytes :  "<<send  << ",Return Value: "<<sendVal <<std::endl;

	unsigned long recv    = 0;
	int recvVal = get_device_recv_bytes(recv,"6F425DF0-B5C1-4430-A836-D134B57D112A",strErrMsg);
	std::cout << " get_device_recv_bytes :  "<< recv  << ",Return Value: "<<recvVal <<std::endl;

	unsigned long bandwidth = 0;
	int bandwidthVal = get_device_bandwidth(bandwidth,"6F425DF0-B5C1-4430-A836-D134B57D112A",strErrMsg);
	std::cout << " get_device_bandwidth :  "<< bandwidth  << ",Return Value: "<<bandwidthVal <<std::endl;

	system("pause");
}