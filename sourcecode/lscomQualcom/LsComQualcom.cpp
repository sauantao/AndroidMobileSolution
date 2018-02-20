#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

#ifndef ARM
#include "setupapi.h"
#define INITGUID 1    
#include "devpkey.h"
#endif //ARM

int InitDiskList()
{
#ifndef ARM
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_COMPORT, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	DEVPROPTYPE ulPropertyType = DEVPROP_TYPE_STRING;
	DWORD dwSize;
#endif //ARM

	//wprintf(_T("Tim kiem tat ca cac thiet bi o che do 9008 ...\n\n"));
	cout << "tim kiem tat ca cac thiet bi 9008\n";
#ifndef ARM
	if (hDevInfo != INVALID_HANDLE_VALUE) {
		// Successfully got a list of ports
		for (int i = 0; ; i++) {
			WCHAR szBuffer[512];
			SP_DEVINFO_DATA DeviceInfoData;
			DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
			if (!SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData) && (GetLastError() == ERROR_NO_MORE_ITEMS)) {
				// No more ports
				break;
			}
			// successfully found entry print out the info
			if (SetupDiGetDeviceProperty(hDevInfo, &DeviceInfoData, &DEVPKEY_Device_FriendlyName, &ulPropertyType, (BYTE*)szBuffer, sizeof(szBuffer), &dwSize, 0)) {
				if ((GetLastError() == ERROR_SUCCESS) && wcsstr(szBuffer, L"QDLoader 9008") != NULL) {
					wprintf(szBuffer);
					cout << endl;
					//cout << szBuffer << endl;
				}
			}
		}
		
	}
#endif //ARM
return ERROR_SUCCESS;	
}


int main()
{
	InitDiskList();
	system("pause");

		return 0;
}