// DevicePerformance.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "DevicePerformance.h"
#include "DevicePerformanceInstance.h"

int get_system_id(string &strSystemId, string &strErrMsg)
{
   return CDevicePerformanceInstance::instance()->get_system_id(strSystemId, strErrMsg);
}
int get_cpu_usage(int &iCpuUsage, string &strErrMsg)
{
   return CDevicePerformanceInstance::instance()->get_cpu_usage(iCpuUsage, strErrMsg);
}
int get_memory_usage(int &iMemUsage, string &strErrMsg)
{
   return CDevicePerformanceInstance::instance()->get_memory_usage(iMemUsage, strErrMsg);
}
int get_disk_usage(int &iDiskUsage, string &strErrMsg)
{
   return CDevicePerformanceInstance::instance()->get_disk_usage(iDiskUsage, strErrMsg);
}
int get_device_temperature(int &iTemperature, const string strTempFile, string &strErrMsg)
{
   return CDevicePerformanceInstance::instance()->get_device_temperature(iTemperature, strTempFile, strErrMsg);
}
int get_device_send_bytes(unsigned long &SendBytes, string strGUID, string &strErrMsg)
{
   return CDevicePerformanceInstance::instance()->get_device_send_bytes(SendBytes, strGUID, strErrMsg);
}
int get_device_recv_bytes(unsigned long &RecvBytes, string strGUID, string &strErrMsg)
{
   return CDevicePerformanceInstance::instance()->get_device_recv_bytes(RecvBytes, strGUID, strErrMsg);
}
int get_device_bandwidth(unsigned long &Bandwidth, string strGUID, string &strErrMsg)
{
   return CDevicePerformanceInstance::instance()->get_device_bandwidth(Bandwidth, strGUID, strErrMsg);
}

string get_mac_by_ip(const string strIP)
{
   return CDevicePerformanceInstance::instance()->get_mac_by_ip(strIP);
}

int get_device_send_bytes_by_ip(unsigned long &SendBytes, string strIP, string &strErrMsg)
{
	return CDevicePerformanceInstance::instance()->get_device_send_bytes_by_ip(SendBytes, strIP, strErrMsg);
}
int get_device_recv_bytes_by_ip(unsigned long &RecvBytes, string strIP, string &strErrMsg)
{
	return CDevicePerformanceInstance::instance()->get_device_recv_bytes_by_ip(RecvBytes, strIP, strErrMsg);
}
int get_device_bandwidth_by_ip(unsigned long &Bandwidth, string strIP, string &strErrMsg)
{
	return CDevicePerformanceInstance::instance()->get_device_bandwidth_by_ip(Bandwidth, strIP, strErrMsg);
}


//标准C接口
int get_system_id_ex(char *szSystemId, char *szErrMsg)
{
   string strSystemId = "";
   string strErrMsg   = "";
   int retVal = CDevicePerformanceInstance::instance()->get_system_id(strSystemId, strErrMsg);
   if ( retVal > 0 ) return 1;

   if( szSystemId != NULL )
       strcpy(szSystemId,strSystemId.c_str());
   if( szErrMsg != NULL)
	   strcpy(szErrMsg,strErrMsg.c_str());

   return 0;

}
int get_cpu_usage_ex(int *iCpuUsage, char *szErrMsg)
{
	int cupUsage = 0;
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_cpu_usage(cupUsage, strErrMsg);
	if ( retVal > 0 ) return 1;

	if( iCpuUsage != NULL )
	    *iCpuUsage = cupUsage;
	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return 0;
}

int get_memory_usage_ex(int *iMemUsage, char *szErrMsg)
{
	int memUsage = 0;
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_memory_usage(memUsage, strErrMsg);
	if ( retVal > 0 ) return 1;

	if( iMemUsage != NULL )
		*iMemUsage = memUsage;
	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return 0;
}

int get_disk_usage_ex(int *iDiskUsage, char *szErrMsg)
{
	int diskUsage = 0;
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_disk_usage(diskUsage, strErrMsg);
	if ( retVal > 0 ) return 1;

	if( iDiskUsage != NULL )
		*iDiskUsage = diskUsage;
	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return 0;
}

int get_device_temperature_ex(int *iTemperature,const char *szTempFile/*Used for Linux*/, char *szErrMsg)
{
	int temperature = 0;
	string strTempFile = string(szTempFile);
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_device_temperature(temperature, strTempFile, strErrMsg);
	if ( retVal > 0 ) return 1;

	if( iTemperature != NULL )
		*iTemperature = temperature;
	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return 0;
}

int get_device_temperature_ex_1(const char *szTempFile/*Used for Linux*/, char *szErrMsg)
{
	int temperature = 0;
	string strTempFile = string(szTempFile);
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_device_temperature(temperature, strTempFile, strErrMsg);
	if ( retVal > 0 ) return -1;

	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return temperature;
}

int get_device_send_bytes_ex(unsigned long *SendBytes, const char *szGUID, char *szErrMsg)
{
	unsigned long sendBytes = 0;
	string strGUID = string(szGUID);
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_device_send_bytes(sendBytes, strGUID, strErrMsg);
	if ( retVal > 0 ) return 1;

	if( SendBytes != NULL )
		*SendBytes = sendBytes;
	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return 0;
}

int get_device_recv_bytes_ex(unsigned long *RecvBytes, const char *szGUID, char *szErrMsg)
{
	unsigned long recvBytes = 0;
	string strGUID = string(szGUID);
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_device_recv_bytes(recvBytes, strGUID, strErrMsg);
	if ( retVal > 0 ) return 1;

	if( RecvBytes != NULL )
		*RecvBytes = recvBytes;
	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return 0;
}

int get_device_bandwidth_ex(unsigned long *Bandwidth, const char *szGUID, char *szErrMsg)
{
	unsigned long bandwidth = 0;
	string strGUID = string(szGUID);
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_device_bandwidth(bandwidth, strGUID, strErrMsg);
	if ( retVal > 0 ) return 1;

	if( Bandwidth != NULL )
		*Bandwidth = bandwidth;
	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return 0;
}

int get_device_send_bytes_by_ip_ex(unsigned long *SendBytes, const char *szIP, char *szErrMsg)
{
	unsigned long sendBytes = 0;
	string strIP = string(szIP);
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_device_send_bytes_by_ip(sendBytes, strIP, strErrMsg);
	if ( retVal > 0 ) return 1;

	if( SendBytes != NULL )
		*SendBytes = sendBytes;
	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return 0;
}

int get_device_recv_bytes_by_ip_ex(unsigned long *RecvBytes, const char *szIP, char *szErrMsg)
{
	unsigned long recvBytes = 0;
	string strIP = string(szIP);
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_device_recv_bytes_by_ip(recvBytes, strIP, strErrMsg);
	if ( retVal > 0 ) return 1;

	if( RecvBytes != NULL )
		*RecvBytes = recvBytes;
	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return 0;
}

int get_device_bandwidth_by_ip_ex(unsigned long  *Bandwidth, const char *szIP, char *szErrMsg)
{
	unsigned long bandwidth = 0;
	string strIP = string(szIP);
	string strErrMsg   = "";
	int retVal = CDevicePerformanceInstance::instance()->get_device_bandwidth_by_ip(bandwidth, strIP, strErrMsg);
	if ( retVal > 0 ) return 1;

	if( Bandwidth != NULL )
		*Bandwidth = bandwidth;
	if( szErrMsg != NULL)
		strcpy(szErrMsg,strErrMsg.c_str());

	return 0;
}