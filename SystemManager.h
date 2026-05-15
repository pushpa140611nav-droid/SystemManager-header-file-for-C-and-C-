#include <windows.h>

template <class DataType>
class SystemInfo{
    private:
      float TD ,FD;
      float TC ,FC;
      float TE ,FE;
    public:
      DataType CPU(void);
      DataType RAM(void);
      DataType DISK(const char*, const char*, const char*);
      DataType POWER(void);  
};
ULONGLONG FileTimeToULL(const FILETIME& ft) {
    return ((ULONGLONG)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
};

template <class DataType>
DataType SystemInfo <DataType> :: CPU() {
    FILETIME idleTime, kernelTime, userTime;
    
    // First sample
    if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) return -1.0;

    Sleep(1000); // Wait 1 second for the second sample

    FILETIME idleTime2, kernelTime2, userTime2;
    // Second sample
    if (!GetSystemTimes(&idleTime2, &kernelTime2, &userTime2)) return -1.0;

    ULONGLONG idle = FileTimeToULL(idleTime2) - FileTimeToULL(idleTime);
    ULONGLONG kernel = FileTimeToULL(kernelTime2) - FileTimeToULL(kernelTime);
    ULONGLONG user = FileTimeToULL(userTime2) - FileTimeToULL(userTime);

    // Total system time is kernel + user
    // Note: kernelTime already includes idleTime
    ULONGLONG totalSystemTime = kernel + user;

    if (totalSystemTime == 0) return 0.0;

    // CPU Usage = (Total - Idle) / Total
    return (double)(totalSystemTime - idle) * 100.0 / totalSystemTime;
};

template <class DataType>
DataType SystemInfo <DataType> ::RAM() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memInfo)) {
        return memInfo.dwMemoryLoad;
    }
    return static_cast<DataType>(0);
};

template <class DataType>
DataType SystemInfo <DataType> :: DISK(const char* driveC, const char* driveD, const char* driveE) {
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;
    if (true){
        if (GetDiskFreeSpaceExA(driveC, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
            double totalGBofC = (double)totalNumberOfBytes.QuadPart / (1024 * 1024 * 1024);
            double freeGB = (double)totalNumberOfFreeBytes.QuadPart / (1024 * 1024 * 1024);
            //return 
            TC = totalGBofC;
            FC = freeGB;
        }

        if (GetDiskFreeSpaceExA(driveD, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
            double totalGBofD = (double)totalNumberOfBytes.QuadPart / (1024 * 1024 * 1024);
            double freeGB = (double)totalNumberOfFreeBytes.QuadPart / (1024 * 1024 * 1024);
            //return 
            TD = totalGBofD;
            FD = freeGB;
        }
        if (GetDiskFreeSpaceExA(driveE, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
            double totalGBofE = (double)totalNumberOfBytes.QuadPart / (1024 * 1024 * 1024);
            double freeGB = (double)totalNumberOfFreeBytes.QuadPart / (1024 * 1024 * 1024);
            //return 
            TE = totalGBofE;
            FE = freeGB;
        }
        return  ((FD + FC + FE) / (TD + TC + TE)) * 100;
    }
    return static_cast<DataType>(0);
}

template <class DataType>
DataType SystemInfo <DataType> :: POWER() {
    SYSTEM_POWER_STATUS sps;
    if (GetSystemPowerStatus(&sps)) {
        if (sps.BatteryLifePercent != 255) {
           return static_cast <DataType> (sps.BatteryLifePercent);
           
        }
    }
    return static_cast <DataType> (sps.BatteryLifePercent);
}