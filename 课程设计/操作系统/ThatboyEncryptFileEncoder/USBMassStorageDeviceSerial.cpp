
#include "pch.h"
#include "USBMassStorageDeviceSerial.h"

void getDevicePath(LPGUID lpGuid, std::vector<std::string>& devicePathVector)
{
    using namespace thatboy::USBMassStorageDeviceSerial;
    HDEVINFO hDevInfoSet;    //�豸��Ϣ�������
    SP_DEVICE_INTERFACE_DATA ifdata;
    PSP_DEVICE_INTERFACE_DETAIL_DATA pDetail;

    devicePathVector.clear();

    // ȡ��һ����GUID��ص��豸��Ϣ�����
    hDevInfoSet = ::SetupDiGetClassDevs((LPGUID)&UsbClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);    // Ŀǰ���ڵ��豸
    if (hDevInfoSet == INVALID_HANDLE_VALUE)
        return;
    // �����豸�ӿ����ݿռ�
    pDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)::GlobalAlloc(LMEM_ZEROINIT, 1024);
    if (pDetail == NULL)
        return;
    pDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

    // ��һ�����豸�ӿ�
    while (true)
    {
        ifdata.cbSize = sizeof(ifdata);
        // ö�ٷ��ϸ�GUID���豸�ӿڲ�����豸·��
        if (!::SetupDiEnumDeviceInterfaces(hDevInfoSet, NULL, lpGuid, (ULONG)devicePathVector.size(), &ifdata)
            || !SetupDiGetInterfaceDeviceDetail(hDevInfoSet, &ifdata, pDetail, 1024, NULL, NULL))
            break;
        // �����豸·�������������
        devicePathVector.push_back(pDetail->DevicePath);
    }
    // �ͷ��豸�ӿ����ݿռ�
    // �ر��豸��Ϣ�����
    ::GlobalFree(pDetail);
    ::SetupDiDestroyDeviceInfoList(hDevInfoSet);
}

void thatboy::USBMassStorageDeviceSerial::getUSBMassStorageDeviceList(std::vector<std::string>& usbMSDSerialVector)
{
    // ����豸����
    PSTORAGE_DEVICE_DESCRIPTOR DeviceDesc;
    DeviceDesc = (PSTORAGE_DEVICE_DESCRIPTOR)new BYTE[sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1];
    DeviceDesc->Size = sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1;
    // ȡ�豸·��
    std::vector<std::string> devicePathList;
    ::getDevicePath((LPGUID)&UsbClassGuid, devicePathList);
    for (auto& devicePath : devicePathList)
    {
        char pdg[1024];
        char serial[MAX_PATH] = { NULL };
        ::DWORD junk;
        // ���豸
        HANDLE hDevice = CreateFile(devicePath.c_str(), GENERIC_READ && GENERIC_WRITE, FILE_SHARE_READ && FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        // ������Ч�豸
        if (hDevice == INVALID_HANDLE_VALUE || !::DeviceIoControl(hDevice, IOCTL_STORAGE_GET_MEDIA_TYPES, NULL, 0, pdg, 1024, &junk, NULL))
            continue;
        // ȡ�����к�
        sscanf_s(devicePath.c_str(), "%*[^#]#vid_%[^&]", serial, MAX_PATH);
        sscanf_s(devicePath.c_str() + 17, "pid_%[^#]", serial + 4, MAX_PATH - 4);
        sscanf_s(devicePath.c_str() + 25, "#%[^#]", serial + 8, MAX_PATH - 8);
        ::CloseHandle(hDevice);

        usbMSDSerialVector.push_back(serial);
    }
}