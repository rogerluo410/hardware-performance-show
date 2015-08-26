#include "DevicePerformance.h"
#include "iostream"

int main()
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
  string strTempFile = "/sys/class/hwmon/hwmon0/temp1_input";
  int val = get_device_temperature(iTemperature, strTempFile, strErrMsg);
  std::cout << " get_device_temperature :  "<< iTemperature << ",Return Value: "<<val <<std::endl;

 unsigned long send    = 0;
 int sendVal = get_device_send_bytes(send,"eth0",strErrMsg);
  std::cout << " get_device_send_bytes :  "<<send  << ",Return Value: "<<sendVal <<std::endl;

 unsigned long recv    = 0;
 int recvVal = get_device_recv_bytes(recv,"eth0",strErrMsg);
 std::cout << " get_device_recv_bytes :  "<< recv  << ",Return Value: "<<recvVal <<std::endl;

 unsigned long bandwidth = 0;
 int bandwidthVal = get_device_bandwidth(bandwidth,"eth0",strErrMsg);
 std::cout << " get_device_bandwidth :  "<< bandwidth  << ",Return Value: "<<bandwidthVal <<std::endl;

  return 0;
}


//
//
