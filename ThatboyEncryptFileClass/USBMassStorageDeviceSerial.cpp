#include "USBMassStorageDeviceSerial.h"

// IOCTL控制码
#define IOCTL_STORAGE_QUERY_PROPERTY   CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)

void getDevicePath(LPGUID lpGuid, std::vector<std::string>& devicePathVector)
{
    using namespace thatboy::USBMassStorageDeviceSerial;
    HDEVINFO hDevInfoSet;    //设备信息集句柄；
    SP_DEVICE_INTERFACE_DATA ifdata;
    PSP_DEVICE_INTERFACE_DETAIL_DATA pDetail;

    devicePathVector.clear();

    // 取得一个该GUID相关的设备信息集句柄
    hDevInfoSet = ::SetupDiGetClassDevs((LPGUID)&UsbClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);    // 目前存在的设备
    if (hDevInfoSet == INVALID_HANDLE_VALUE)
        return;
    // 申请设备接口数据空间
    pDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)::GlobalAlloc(LMEM_ZEROINIT, 1024);
    pDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

    // 设备序号=0,1,2... 逐一测试设备接口，到失败为止
    while (true)
    {
        ifdata.cbSize = sizeof(ifdata);
        // 枚举符合该GUID的设备接口并获得设备路径
        if (!::SetupDiEnumDeviceInterfaces(hDevInfoSet, NULL, lpGuid, (ULONG)devicePathVector.size(), &ifdata)
            || !SetupDiGetInterfaceDeviceDetail(hDevInfoSet, &ifdata, pDetail, 1024, NULL, NULL))
            break;
        // 复制设备路径到输出缓冲区
        devicePathVector.push_back(pDetail->DevicePath);
    }
    // 释放设备接口数据空间
    // 关闭设备信息集句柄
    ::GlobalFree(pDetail);
    ::SetupDiDestroyDeviceInfoList(hDevInfoSet);
}

void thatboy::USBMassStorageDeviceSerial::getUSBMassStorageDeviceList(std::vector<std::string>& usbMSDSerialVector)
{
    // 定义一个 PSTORAGE_DEVICE_DESCRIPTOR 变量，存放设备属性
    PSTORAGE_DEVICE_DESCRIPTOR DeviceDesc;
    // 变量初始化
    DeviceDesc = (PSTORAGE_DEVICE_DESCRIPTOR)new BYTE[sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1];
    DeviceDesc->Size = sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1;
    // 取设备路径
    std::vector<std::string> devicePathList;
    ::getDevicePath((LPGUID)&UsbClassGuid, devicePathList);
    for (auto& devicePath : devicePathList)
    {
        char pdg[1024];
        char serial[256] = { NULL };
        DWORD junk;
        // 打开设备
        HANDLE hDevice = CreateFile(devicePath.c_str(), GENERIC_READ && GENERIC_WRITE, FILE_SHARE_READ && FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        // 跳过无效设备和非存储设备
        if (hDevice == INVALID_HANDLE_VALUE || !::DeviceIoControl(hDevice, IOCTL_STORAGE_GET_MEDIA_TYPES, NULL, 0, pdg, 1024, &junk, NULL))
            continue;

        sscanf(devicePath.c_str(), "%*[^#]#vid_%[^&]", serial);
        sscanf(devicePath.c_str() + 17, "pid_%[^#]", serial + 4);
        sscanf(devicePath.c_str() + 25, "#%[^#]", serial + 8);
        ::CloseHandle(hDevice);

        usbMSDSerialVector.push_back(serial);
    }
}