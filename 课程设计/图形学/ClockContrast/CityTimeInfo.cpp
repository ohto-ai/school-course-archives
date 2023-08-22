#include "pch.h"
#include "CityTimeInfo.h"

const CString CityTimeInfo::TimeFormat = (TEXT("%m/%d %H:%M:%S"));	// ʱ���ʽ
const CString CityTimeInfo::CityTimeFormat = (TEXT("%H:%M:%S"));	// ʱ���ʽ
std::vector<CityTimeInfo*> CityTimeInfo::CityList;
void CityTimeInfo::UpdateAllCityTime(bool bCity)
{
	CTime GlobalTime;	// ����ʱ��
	GlobalTime = CTime::GetCurrentTime() -CTimeSpan(0, +8, 0, 0);	

	for (auto& pcity : CityList)
	{
		pcity->Time = GlobalTime + pcity->TimeSpan;
		if (bCity)
			pcity->TimeString.Format(TEXT("%s %s"), pcity->CityName, pcity->Time.Format(WorldCityTimeInfo::CityTimeFormat));
		else
			pcity->TimeString = pcity->Time.FormatGmt(WorldCityTimeInfo::TimeFormat);
	}
}
