#include "pch.h"
#include "ToolFunction.h"

CString thatboy::PublicMemory::cardAccount;
CString thatboy::PublicMemory::userName;
BOOL thatboy::PublicMemory::userGender;
float thatboy::PublicMemory::cardBalance;
std::function<void(void)> thatboy::CallBack::updateUserInfo;