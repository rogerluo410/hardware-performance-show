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
