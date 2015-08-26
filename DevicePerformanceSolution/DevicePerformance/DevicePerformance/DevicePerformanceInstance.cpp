#include "stdafx.h"
#include "DevicePerformanceInstance.h"



CDevicePerformanceInstance CDevicePerformanceInstance::m_Obj;

CDevicePerformanceInstance::CDevicePerformanceInstance(void)
{
#ifdef _WINDOWS_
	IWbemLocator         *pLoc        = NULL;
	IWbemServices        *pSvc        = NULL;
	IEnumWbemClassObject *pEnumerator = NULL;
	IWbemClassObject     *pclsObj     = NULL;

	InitializeWMI();
#endif	

}

CDevicePerformanceInstance::~CDevicePerformanceInstance(void)
{
#ifdef _WINDOWS_	
// 	if( pSvc != NULL )        pSvc->Release();
// 	if( pLoc != NULL )        pLoc->Release();
// 	if( pEnumerator != NULL ) pEnumerator->Release();
// 	if( pclsObj != NULL )     pclsObj->Release();
 	CoUninitialize();
#endif
}

#ifdef _WINDOWS_	
int CDevicePerformanceInstance::InitializeWMI()
{
	hres =  CoInitializeEx(0, COINIT_MULTITHREADED); 
	if (FAILED(hres))
	{
		cout << "Failed to initialize COM library. Error code = 0x" 
			<< hex << hres << endl;
		return 1;                  // Program has failed.
	}

	hres =  CoInitializeSecurity(
		NULL, 
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
		);


	if (FAILED(hres))
	{
		cout << "Failed to initialize security. Error code = 0x" 
			<< hex << hres << endl;
		return 1;                    // Program has failed.
	}


	hres = CoCreateInstance(
		CLSID_WbemLocator,             
		0, 
		CLSCTX_INPROC_SERVER, 
		IID_IWbemLocator, (LPVOID *) &pLoc);

	if (FAILED(hres))
	{
		cout << "Failed to create IWbemLocator object."
			<< " Err code = 0x"
			<< hex << hres << endl;
		return 1;                 // Program has failed.
	}

	return 0;
}

int CDevicePerformanceInstance::get_connectCIMV2(string strSql)
{
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority (for example, Kerberos)
		0,                       // Context object 
		&pSvc                    // pointer to IWbemServices proxy
		);

	if (FAILED(hres))
	{
		cout << "Could not connect. Error code = 0x" 
			<< hex << hres << endl;
		return 1;                // Program has failed.
	}

	// Step 5: --------------------------------------------------
	// Set security levels on the proxy -------------------------
	hres = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
		);

	if (FAILED(hres))
	{
		cout << "Could not set proxy blanket. Error code = 0x" 
			<< hex << hres << endl;
		return 1;               // Program has failed.
	}

	// Step 6: --------------------------------------------------
	// Use the IWbemServices pointer to make requests of WMI ----

	// For example, get the name of the operating system
	hres = pSvc->ExecQuery(
		bstr_t("WQL"), 
		bstr_t(strSql.c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
		NULL,
		&pEnumerator);

	if (FAILED(hres))
	{
		cout << "Query for operating system name failed."
			<< " Error code = 0x" 
			<< hex << hres << endl;
		return 1;               // Program has failed.
	}

	return 0;
}
#endif

int  CDevicePerformanceInstance::get_system_id(string &strSystemId, string &strErrMsg)
{
#ifdef _WINDOWS_	
      string strSql = "SELECT * FROM CIM_System";
	int iRetVal   = get_connectCIMV2(strSql);
	if(iRetVal > 0) 
    { 
      strErrMsg = "Failed to establish WMI environment";
      return iRetVal;
    }

	// Step 7: -------------------------------------------------
	// Get the data from the query in step 6 -------------------
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, 
			&pclsObj, &uReturn);

		if(0 == uReturn)
		{
			break;
		}

		VARIANT vtProp;

		// Get the value of the Name property
		hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
#ifdef _DEBUG
		wcout << " Computer name: " << vtProp.bstrVal << endl;
#endif

		char * lpszText = _com_util::ConvertBSTRToString(vtProp.bstrVal);
		strSystemId = string(lpszText);  
        delete[] lpszText;
		VariantClear(&vtProp);

		break;
	}
#else
	//Linux version
    char hostName[50];
    memset(hostName,0,sizeof(hostName));
    gethostname(hostName,sizeof(hostName));
    strSystemId = string(hostName);
#endif	

	return 0;
}

#ifndef _WINDOWS_
//For linux version using
typedef struct _cpuOccupy {
	char name[20];
	unsigned int user;
	unsigned int nice;
	unsigned int system;
	unsigned int idle;
	unsigned int iowait;
	unsigned int irq;
	unsigned int softirq;
} cpuOccupy;

int calCpuOccupy(cpuOccupy *c1, cpuOccupy *c2)
{
  unsigned long total1,total2,id,sd,xd;
  int cpuUsage = 0;

  total1 = c1->user + c1->nice + c1->system + c1->idle + c1->iowait + c1->irq + c1->softirq;
  total2 = c2->user + c2->nice + c2->system + c2->idle + c2->iowait + c2->irq + c2->softirq;

  id = c2->user   - c1->user;
  sd = c2->system - c1->system;
  xd = c2->nice   - c1->nice;

  if( (total2 - total1 ) != 0 ) 
	 cpuUsage = ((sd + id + xd) * 100) / (total2 - total1) ;
  else
	 cpuUsage = 0;

  return cpuUsage;	  
}

void getCpuOccupy(cpuOccupy *cpust)
{
  FILE *fp;
  char buf[256];
  cpuOccupy *cpuOcc;
  cpuOcc = cpust;
  fp = fopen("/proc/stat","r");
  if(!fp){
	 std::cout<<"open /proc/stat error!"<<std::endl;
	 return;
  }
  fgets(buf,sizeof(buf),fp);
  sscanf(buf,"%s %u %u %u %u %u %u %u",cpuOcc->name,&cpuOcc->user,&cpuOcc->nice,&cpuOcc->system,&cpuOcc->idle,&cpuOcc->iowait,&cpuOcc->irq,&cpuOcc->softirq);
  fclose(fp);
}
#endif

int CDevicePerformanceInstance::get_cpu_usage(int &iCpuUsage, string &strErrMsg)
{
#ifdef _WINDOWS_	
	string strSql = "SELECT * FROM Win32_Processor";
	int iRetVal   = get_connectCIMV2(strSql);
	if(iRetVal > 0) 
    { 
      strErrMsg = "Failed to establish WMI environment";
      return iRetVal;
    }

	// Step 7: -------------------------------------------------
	// Get the data from the query in step 6 -------------------
	ULONG uReturn = 0;

	int count               = 0;
	int totalLoadPercentage = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, 
			&pclsObj, &uReturn);

		if(0 == uReturn)
		{
			break;
		}

		VARIANT vtProp;

		// Get the value of the LoadPercentage property
		hr = pclsObj->Get(L"LoadPercentage", 0, &vtProp, 0, 0);
#ifdef _DEBUG
		wcout << " LoadPercentage : " << vtProp.bVal << endl;
#endif

		totalLoadPercentage += vtProp.bVal;  
		count++;

		VariantClear(&vtProp);

	}

   iCpuUsage = totalLoadPercentage / count;

#else
   //Linux version
   cpuOccupy cpuStat1;
   cpuOccupy cpuStat2;
   memset(&cpuStat1, 0, sizeof(cpuOccupy));
   memset(&cpuStat2, 0, sizeof(cpuOccupy));
   getCpuOccupy(&cpuStat1);
   sleep(3);
   getCpuOccupy(&cpuStat2);

   iCpuUsage = calCpuOccupy(&cpuStat1,&cpuStat2);
#endif

	return 0;
}

int CDevicePerformanceInstance::get_memory_usage(int &iMemUsage, string &strErrMsg)
{
#ifdef _WINDOWS_	
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength  = sizeof(MEMORYSTATUSEX);

	GlobalMemoryStatusEx(&meminfo);

    if( 0 == meminfo.ullTotalPhys )
	{
	   iMemUsage = 0;
	}
	else
	{
	    double usagePercentage =  (double)(meminfo.ullTotalPhys - meminfo.ullAvailPhys) / (double)meminfo.ullTotalPhys;
#ifdef _DEBUG
	cout << "Memory usage percentage : "<<usagePercentage<<",Used memory : "<<meminfo.ullTotalPhys - meminfo.ullAvailPhys << ", Total memory : " <<meminfo.ullTotalPhys << endl;
#endif  
	    iMemUsage = (int) (usagePercentage*100);
	}

#else
    //Linux version 
	FILE *fp;
	char buf[256];

	fp = fopen("/proc/meminfo","r");
	if(!fp){
	   strErrMsg = "Can't open /proc/meminfo";
	   return 1;
	}
	unsigned long totalMem,freeMem;
	char name[256];
	memset(name,0,sizeof(name));
	fgets(buf,sizeof(buf),fp);
	sscanf(buf,"%s %lu %s",name,&totalMem,name);
	fgets(buf,sizeof(buf),fp);
	sscanf(buf,"%s %lu %s",name,&freeMem,name);

    if( 0 == totalMem )
	{
	  iMemUsage = 0;
	}
	else
	{
      double usagePercentage = (double)(totalMem - freeMem) / (double) totalMem;
      iMemUsage = (usagePercentage*100);
	}
#endif

	return 0;
}


int CDevicePerformanceInstance::get_disk_usage(int &iDiskUsage, string &strErrMsg)
{
#ifdef _WINDOWS_	
	  ULARGE_INTEGER FreeAvailable,TotalNum, TotalFreeNum;
	  char p[10];
	  bool b_flag;
	  long totalDisk = 0;
	  long freeDisk  = 0;
      for (int drive = 1 ; drive <= 26 ; drive++)
	  {
		  if(!_chdrive(drive))
		  {
			  memset(p,0,sizeof(p));
			  p[0]   = drive + 'A' - 1;
			  p[1]   = ':';
			  p[2]   = '\\';
			  WCHAR wszStr[32];
			  memset(wszStr,0,sizeof(wszStr));
			  MultiByteToWideChar(CP_ACP,0,p,strlen(p)+1,wszStr,sizeof(wszStr) / sizeof(wszStr[0]) );
			  b_flag = GetDiskFreeSpaceEx(wszStr,&FreeAvailable,&TotalNum,&TotalFreeNum);
			  if(b_flag)
			  {
				  totalDisk += TotalNum.QuadPart/1024/1024;
				  freeDisk  += FreeAvailable.QuadPart/1024/1024;
#ifdef _DEBUG
				  cout << p << endl;
				  cout << "Total : " << TotalNum.QuadPart/1024/1024 << "MB"<<endl;
				  cout << "Freespace : " << FreeAvailable.QuadPart/1024/1024 << "MB"<<endl;
				  cout << "Used percentage : " << (double)( TotalNum.QuadPart - FreeAvailable.QuadPart)/(double)TotalNum.QuadPart<<endl;
#endif
			  }
		  }
	  }

   double diskUsagePercentage =  (double)(totalDisk - freeDisk) / (double)totalDisk;
#ifdef _DEBUG
   cout << "Disk usage percentage : "<<diskUsagePercentage<<",Used disk : "<<totalDisk - freeDisk << "MB , Total disk : " <<totalDisk << "MB"<<endl;
#endif

   iDiskUsage = (int) (diskUsagePercentage*100);
#else
   //Linux version
   struct statfs diskStatfs;
   statfs("/",&diskStatfs);
   unsigned long long totalBlocks = diskStatfs.f_blocks;
   unsigned long long totalSize   = totalBlocks * diskStatfs.f_bsize/1024/1024 ;
   unsigned long long freeBlocks  = diskStatfs.f_bfree;
   unsigned long long freeSize    = freeBlocks * diskStatfs.f_bsize/1024/1024;
  
   double diskUsagePercentage = (double)(totalSize - freeSize) / (double)totalSize;
   
   iDiskUsage = (int) (diskUsagePercentage*100);
#endif   
   return 0;
}

int CDevicePerformanceInstance::get_device_temperature(int &iTemperature,const string strTempFile/*Used for Linux*/, string &strErrMsg)
{    
#ifdef _WINDOWS_
   TemperatureWatcher ^ _temperatureWatcher =gcnew  TemperatureWatcher();

   _temperatureWatcher->Start();
	   
   float temp  =  _temperatureWatcher->LastMeasuredTemperature;

   if(temp > 0 ) iTemperature = (int)temp;
   else          iTemperature = 0;

#else
   int tempTemperature = 0;
   int sensors_input   = 1000;
   ifstream tempfile(strTempFile.c_str());
   if(!tempfile.is_open())
   {
     strErrMsg = "Can't open " + strTempFile;
     return 1;
   }
   tempfile >>  tempTemperature;
   tempfile.close();

   iTemperature = tempTemperature / sensors_input;
#endif 	

  return 0;
}

int CDevicePerformanceInstance::get_network_interface_relevant(unsigned long &ulValue, string strGUID, int iSwitch, string &strErrMsg)
{
#ifdef _WINDOWS_	
	// Declare and initialize variables.
	DWORD dwSize   = 0;
	DWORD dwRetVal = 0;

	int i;
	unsigned long tempValue = 0;

	/* variables used for GetIfTable and GetIfEntry */
	MIB_IFTABLE *pIfTable;
	MIB_IFROW *pIfRow;

	// Allocate memory for our pointers.
	pIfTable = (MIB_IFTABLE *) MALLOC(sizeof (MIB_IFTABLE));
	if (pIfTable == NULL) {
        strErrMsg = "Error allocating memory needed to call GetIfTable";
		return 1;
	}
	// Make an initial call to GetIfTable to get the
	// necessary size into dwSize
	dwSize = sizeof (MIB_IFTABLE);
	if (GetIfTable(pIfTable, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER)
	{
		FREE(pIfTable);
		pIfTable = (MIB_IFTABLE *) MALLOC(dwSize);
		if (pIfTable == NULL)
		{
			strErrMsg = "Error allocating memory needed to call GetIfTable";
			return 1;
		}
	}
	// Make a second call to GetIfTable to get the actual
	// data we want.
	if ((dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE)) == NO_ERROR)
	{
#ifdef _DEBUG
		printf("Num Entries: %ld\n", pIfTable->dwNumEntries);
#endif
		for (i = 0; i < (int) pIfTable->dwNumEntries; i++)
		{
			pIfRow         = (MIB_IFROW *) & pIfTable->table[i];
			char *lpszText = _com_util::ConvertBSTRToString(pIfRow->wszName);
			string strName = string(lpszText);
			delete[] lpszText;
			if (pIfRow->dwType == MIB_IF_TYPE_ETHERNET && strName == "\\DEVICE\\TCPIP_{"+ strGUID + "}" )
			{
                        switch(iSwitch)
                        {
                          case 0:
				                 tempValue += pIfRow->dwOutOctets;
                                 break;
                          case 1:
                                 tempValue += pIfRow->dwInOctets;
			     		         break;
                          case 2:
                                 tempValue += pIfRow->dwSpeed;
                                 break;
                          default:
                                 break;
                        }   
			}
		}
	}

	ulValue = tempValue;
#else
	//Linux version
	unsigned long tempValue = 0;
	string netInterfaceFile;
    switch(iSwitch)
    {
        case 0:
             netInterfaceFile = "/sys/class/net/"+ strGUID +"/statistics/tx_bytes";
             break;
        case 1:
             netInterfaceFile = "/sys/class/net/"+ strGUID + "/statistics/rx_bytes" ;
	       break;
        case 2:
             netInterfaceFile = "/sys/class/net/"+ strGUID + "/speed";
             break;
        default:
             break;
    }  


	ifstream netfile(netInterfaceFile.c_str());
	if(!netfile.is_open())
	{
	  strErrMsg = "Can't open " + netInterfaceFile;
	  return 1;
	}
	netfile >> tempValue;
	netfile.close();
	if( 2==iSwitch ) ulValue = tempValue * 1024 * 1024 ; 
	else ulValue = tempValue;
#endif
	return 0;
}

int CDevicePerformanceInstance::get_device_send_bytes(unsigned long &SendBytes, string strGUID, string &strErrMsg)
{
     return get_network_interface_relevant(SendBytes, strGUID, 0, strErrMsg);
}
int CDevicePerformanceInstance::get_device_recv_bytes(unsigned long &RecvBytes, string strGUID, string &strErrMsg)
{
     return get_network_interface_relevant(RecvBytes, strGUID, 1, strErrMsg);
}

int CDevicePerformanceInstance::get_device_bandwidth(unsigned long &Bandwidth, string strGUID, string &strErrMsg)
{
     return get_network_interface_relevant(Bandwidth, strGUID, 2, strErrMsg);
}
