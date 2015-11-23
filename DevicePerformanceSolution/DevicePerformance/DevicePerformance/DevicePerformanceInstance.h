#pragma once
#include "stdafx.h"

#include <iostream>
#include <string>
#ifdef _WINDOWS_
#define _WIN32_DCOM
#include <comdef.h>
#include <Wbemidl.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include "windows.h"
#include "direct.h"
#include "winbase.h"

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "iphlpapi.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
#using "GetCPUTemperature.dll"
using namespace GetCPUTemperature;
#else
#include<fstream>
#include<unistd.h>
#include<sys/vfs.h>
#include<stdlib.h>
#include<string.h>
#endif
using namespace std;


class CDevicePerformanceInstance
{
public:
	static CDevicePerformanceInstance* instance()
	{
		return &m_Obj;
	}

	int get_system_id(string &strSystemId, string &strErrMsg);
	int get_cpu_usage(int &iCpuUsage, string &strErrMsg);
	int get_memory_usage(int &iMemUsage, string &strErrMsg);
	int get_disk_usage(int &iDiskUsage, string &strErrMsg);
    int get_device_temperature(int &iTemperature,const string strTempFile/*Used for Linux*/, string &strErrMsg);
	int get_device_send_bytes(unsigned long &SendBytes, string strGUID, string &strErrMsg);
	int get_device_recv_bytes(unsigned long &RecvBytes, string strGUID, string &strErrMsg);
	int get_device_bandwidth(unsigned long &Bandwidth, string strGUID, string &strErrMsg);
	int get_device_send_bytes_by_ip(unsigned long &SendBytes, string strIP, string &strErrMsg);
	int get_device_recv_bytes_by_ip(unsigned long &RecvBytes, string strIP, string &strErrMsg);
	int get_device_bandwidth_by_ip(unsigned long &Bandwidth, string strIP, string &strErrMsg);
    int get_network_interface_relevant(unsigned long &ulValue, string strCondition, int iSwitch, int iSwitch1, string &strErrMsg);
	string get_mac_by_ip(const string strIP);
 
private:
	CDevicePerformanceInstance(void);
	~CDevicePerformanceInstance(void);
	CDevicePerformanceInstance(CDevicePerformanceInstance& m){} 
	void operator=(CDevicePerformanceInstance& m){}

#ifdef _WINDOWS_
	//WMI
	int InitializeWMI();
	int get_connectWMI(string strSql);
	int get_connectCIMV2(string strSql);
#endif

private:
	static CDevicePerformanceInstance  m_Obj;
#ifdef _WINDOWS_	
	HRESULT hres;
	IWbemLocator         *pLoc;
	IWbemServices        *pSvc;
	IEnumWbemClassObject *pEnumerator;
	IWbemClassObject     *pclsObj;
#endif	
};
