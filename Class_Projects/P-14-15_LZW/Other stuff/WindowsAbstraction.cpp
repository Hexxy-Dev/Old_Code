#include "windows.h"
#include "psapi.h"
#include <iostream>
#include "WindowsAbstraction.h"

#include "TCHAR.h"
#include "pdh.h"

//static PDH_HQUERY cpuQuery;
//static PDH_HCOUNTER cpuTotal;
//
//void init() {
//	PdhOpenQuery(NULL, NULL, &cpuQuery);
//	// You can also use L"\\Processor(*)\\% Processor Time" and get individual CPU values with PdhGetFormattedCounterArray()
//	PdhAddEnglishCounter(cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
//	PdhCollectQueryData(cpuQuery);
//}
//
//double getCurrentValue() {
//	PDH_FMT_COUNTERVALUE counterVal;
//
//	PdhCollectQueryData(cpuQuery);
//	PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
//	return counterVal.doubleValue;
//}


//static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
//static int numProcessors;
//static HANDLE self;
//
//void init2() {
//	SYSTEM_INFO sysInfo;
//	FILETIME ftime, fsys, fuser;
//
//	GetSystemInfo(&sysInfo);
//	numProcessors = sysInfo.dwNumberOfProcessors;
//
//	GetSystemTimeAsFileTime(&ftime);
//	memcpy(&lastCPU, &ftime, sizeof(FILETIME));
//
//	self = GetCurrentProcess();
//	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
//	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
//	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
//}
//
//double getCurrentValue2() {
//	FILETIME ftime, fsys, fuser;
//	ULARGE_INTEGER now, sys, user;
//	double percent;
//
//	GetSystemTimeAsFileTime(&ftime);
//	memcpy(&now, &ftime, sizeof(FILETIME));
//
//	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
//	memcpy(&sys, &fsys, sizeof(FILETIME));
//	memcpy(&user, &fuser, sizeof(FILETIME));
//	percent = (sys.QuadPart - lastSysCPU.QuadPart) +
//		(user.QuadPart - lastUserCPU.QuadPart);
//	percent /= (now.QuadPart - lastCPU.QuadPart);
//	percent /= numProcessors;
//	lastCPU = now;
//	lastUserCPU = user;
//	lastSysCPU = sys;
//
//	return percent * 100;
//}

void WINDOWS_HMM()
{
	//init();
	//init2();
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
	DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

	DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
	DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;



	std::cout << "\nTOTAL VIRTUAL MEM:" << totalVirtualMem << " KB"
		<< "\nUSED VITRUAL MEM:" << virtualMemUsed << " KB"
		<< "\nVIRTUAL MEM USAGE: " << virtualMemUsedByMe << " KB";
	std::cout << "\nTOTAL PHYSICAL MEM:" << totalPhysMem << " KB"
		<< "\nUSED PHYSICAL MEM:" << physMemUsed << " KB"
		<< "\nPHYSICAL MEM USAGE: " << physMemUsedByMe << " KB";
	//std::cout << "\nTOTAL CPU USAGE:" << getCurrentValue();
	//std::cout << "\nCPU USED:" << getCurrentValue2();
}

