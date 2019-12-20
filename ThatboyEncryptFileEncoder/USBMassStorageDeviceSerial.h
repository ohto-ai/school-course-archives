#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include <winioctl.h>
#include <initguid.h>
#include <setupapi.h>
#pragma comment(lib,"setupapi.lib")

namespace thatboy
{
	namespace USBMassStorageDeviceSerial
	{
		DEFINE_GUID(UsbClassGuid, 0xa5dcbf10L, 0x6530, 0x11d2, 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed);

		void getUSBMassStorageDeviceList(std::vector<std::string>& usbMSDSerialVector);
	}
}

