#pragma once

#include "framework.h"

namespace thatboy
{
	namespace Tool {

		// UTF-8 UNICODE×ª»»
		inline CString UTF8UnicodeConvert(const CString& strSource, UINT nSourceCodePage, UINT nTargetCodePage)
		{
			CString strTarget;

			wchar_t* pWideBuf;
			int nWideBufLen;

			char* pMultiBuf;
			int nMiltiBufLen;

			nWideBufLen = MultiByteToWideChar(nSourceCodePage, 0, strSource, -1, NULL, NULL);
			pWideBuf = new wchar_t[nWideBufLen + 1]();
			MultiByteToWideChar(nSourceCodePage, 0, strSource, -1, pWideBuf, nWideBufLen);

			nMiltiBufLen = WideCharToMultiByte(nTargetCodePage, 0, pWideBuf, -1, 0, 0, NULL, FALSE);
			pMultiBuf = new char[nMiltiBufLen + 1]();
			WideCharToMultiByte(nTargetCodePage, 0, pWideBuf, -1, pMultiBuf, nMiltiBufLen, NULL, FALSE);

			strTarget.Format(_T("%s"), pMultiBuf);

			delete[]pWideBuf;
			delete[]pMultiBuf;

			return strTarget;
		}
		inline CString Unicode2UTF8(const CString& strSource)
		{
			return UTF8UnicodeConvert(strSource, CP_ACP, CP_UTF8);
		}
		inline CString UTF82Unicode(const CString& strSource)
		{
			return UTF8UnicodeConvert(strSource, CP_UTF8, CP_ACP);
		}
	}

	namespace PublicMemory
	{
		extern CString cardAccount;
		extern CString userName;
		extern BOOL userGender;
		extern float cardBalance;
	}

	namespace CallBack {
		extern std::function<void(void)> updateUserInfo;
	}
}