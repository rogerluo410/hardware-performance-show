#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


/**
  @Desc
  Get computer name.

  @Param[IN/OUT] 
  strSystemId : Computer name.
  strErrMsg   : Error message.

  @Return
  Success : 0  Failure : 1
*/
int get_system_id(string &strSystemId, string &strErrMsg);

/**
  @Desc
  Get CPU usage.

  @Param[IN/OUT] 
  iCpuUsage : Value range is 0 - 100 , represented  iCpuUsage% percentages.
  strErrMsg : Error message.

  @Return
  Success : 0  Failure : 1

  @Remark
  In Windows OS, the WMI must be able to be called.
*/
int get_cpu_usage(int &iCpuUsage, string &strErrMsg);

/**
  @Desc
  Get physical memory usage.

  @Param[IN/OUT] 
  iMemUsage : Value range is 0 - 100 , represented  iMemUsage% percentages.
  strErrMsg : Error message.

  @Return
  Success : 0  Failure : 1

  @Remark
  In Windows OS, the WMI must be able to be called.
*/
int get_memory_usage(int &iMemUsage, string &strErrMsg);

/**
  @Desc
  Get disk usage.

  @Param[IN/OUT] 
  iDiskUsage : Value range is 0 - 100 , represented  iDiskUsage% percentages.
  strErrMsg  : Error message.

  @Return
  Success : 0  Failure : 1
*/
int get_disk_usage(int &iDiskUsage, string &strErrMsg);

/**
  @Desc
  Get CPU temperature.

  @Param[IN/OUT] 
  iTemperature : the unit of value is centigrade
  strErrMsg    : Error message.

  @Param[IN]
  strTempFile : Specified temperature file in Linux system.

  @Return
  Success : 0  Failure : 1
   
  @Remark
  In Windows OS, the application which calls the DLL must be run under administrator authority, in that case this function can return a correct value, otherwise return 0 centigrade.

  In Linux, we must specify the temperature system file, meanwhile, it depends on a tool named lm_sensors.
*/
int get_device_temperature(int &iTemperature,const string strTempFile/*Used for Linux*/, string &strErrMsg);

/**
  @Desc
  Get total sending bytes of a pointed network interface.

  @Param[IN/OUT] 
  SendBytes : Sending bytes, the unit of value is byte.
  strGUID   : Network interface GUID.
              In Windows OS, we can get the GUID at Wireshark, such as "6F425DF0-B5C1-4430-A836-D134B57D112A" which is shown on Interface setting option.
              In Linux, the GUID is interface name, such as "eth0".
  strErrMsg : Error message.

  @Return
  Success : 0  Failure : 1 
*/
int get_device_send_bytes(unsigned long &SendBytes, string strGUID, string &strErrMsg);

/**
  @Desc
  Get total receive bytes of a pointed network interface.

  @Param[IN/OUT] 
  RecvBytes : Receiving bytes, the unit of value is byte.
  strGUID   : Network interface GUID.
              In Windows OS, we can get the GUID at Wireshark, such as "6F425DF0-B5C1-4430-A836-D134B57D112A" which is shown on Interface setting option.
              In Linux, the GUID is interface name, such as "eth0".
  strErrMsg : Error message.

  @Return
  Success : 0  Failure : 1
*/
int get_device_recv_bytes(unsigned long &RecvBytes, string strGUID, string &strErrMsg);

/**
  @Desc
  Get total throughput of a pointed network interface.

  @Param[IN/OUT] 
  Bandwidth : Interface throughput, the unit of value is BPS(Bits per second).
  strGUID   : Network interface GUID.
              In Windows OS, we can get the GUID at Wireshark, such as "6F425DF0-B5C1-4430-A836-D134B57D112A" which is shown on Interface setting option.
              In Linux, the GUID is interface name, such as "eth0".
  strErrMsg : Error message.

  @Return
  Success : 0  Failure : 1
*/
int get_device_bandwidth(unsigned long &Bandwidth, string strGUID, string &strErrMsg);


/*
  扩展接口： 
     通过IP地址查询网卡参数
*/
string get_mac_by_ip(const string strIP);

int get_device_send_bytes_by_ip(unsigned long &SendBytes, string strIP, string &strErrMsg);

int get_device_recv_bytes_by_ip(unsigned long &RecvBytes, string strIP, string &strErrMsg);

int get_device_bandwidth_by_ip(unsigned long &Bandwidth, string strIP, string &strErrMsg);



/*
  标准C扩展函数调用例子:
  int diskUsage1         = 0;
  char szErrMsg[48]      = "";
  memset(szErrMsg, 0 , sizeof(szErrMsg));
  int diskVal1 = get_disk_usage_ex(&diskUsage1, szErrMsg);
  std::cout << " get_disk_usage_ex :  "<< diskUsage1  << ",Return Value: "<<diskVal1 <<std::endl;
*/

extern "C"{
   int get_system_id_ex(char *szSystemId, char *szErrMsg);
   int get_cpu_usage_ex(int *iCpuUsage, char *szErrMsg);
   int get_memory_usage_ex(int *iMemUsage, char *szErrMsg);
   int get_disk_usage_ex(int *iDiskUsage, char *szErrMsg);
   int get_device_temperature_ex(int *iTemperature,const char *szTempFile/*Used for Linux*/, char *szErrMsg);
   /*
   新增接口 get_device_temperature_ex_1 ：直接返回温度
     失败返回 -1
	 成功返回 CPU温度
   */
   int get_device_temperature_ex_1(const char *szTempFile/*Used for Linux*/, char *szErrMsg);

   int get_device_send_bytes_ex(unsigned long *SendBytes, const char *szGUID, char *szErrMsg);
   int get_device_recv_bytes_ex(unsigned long *RecvBytes, const char *szGUID, char *szErrMsg);
   int get_device_bandwidth_ex(unsigned long *Bandwidth, const char *szGUID, char *szErrMsg);

   /*
     扩展接口： 
         通过IP地址查询网卡参数
   */

   int get_device_send_bytes_by_ip_ex(unsigned long *SendBytes, const char *szIP, char *szErrMsg);

   int get_device_recv_bytes_by_ip_ex(unsigned long *RecvBytes, const char *szIP, char *szErrMsg);

   int get_device_bandwidth_by_ip_ex(unsigned long  *Bandwidth, const char *szIP, char *szErrMsg);
}
