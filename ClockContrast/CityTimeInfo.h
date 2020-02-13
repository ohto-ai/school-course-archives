#pragma once
#ifndef CITY_TIME_INFO
#define CITY_TIME_INFO

#include "pch.h"
#include <vector>

struct CityTimeInfo
{
	CTime Time;
	CString TimeString;
	const CTimeSpan TimeSpan;
	const CString CityName;
	const INT TimeZone;
	CityTimeInfo(const CityTimeInfo& Info)
		: Time(Info.Time)
		, TimeString(Info.TimeString)
		, TimeSpan(Info.TimeSpan)
		, CityName(Info.CityName)
		, TimeZone(Info.TimeZone)
	{
		CityList.push_back(this);
	}
	CityTimeInfo(const CString& name, INT zone)
		: Time()
		, TimeString()
		, TimeSpan(0, zone, 0, 0)
		, CityName(name)
		, TimeZone(zone)
	{
		CityList.push_back(this);
	}
	~CityTimeInfo()
	{
		for (auto it = CityList.begin(); it != CityList.end(); ++it)
		{
			if (*it == this)
			{
				CityList.erase(it);
				return;
			}
		}
	}
	static void UpdateAllCityTime(bool bCity = false);
	static std::vector<CityTimeInfo*> CityList;
	static const CString TimeFormat;
	static const CString CityTimeFormat;
};
struct WorldCityTimeInfo
	: public CityTimeInfo
{
	const CPoint CityPosition;

	WorldCityTimeInfo(const WorldCityTimeInfo& city)
		: CityTimeInfo(city)
		, CityPosition(city.CityPosition)
	{}
	WorldCityTimeInfo(const CString& name, const CPoint& pos, INT zone)
		: CityTimeInfo(name, zone) 
		, CityPosition(pos)
	{}

};


#endif // !CITY_TIME_INFO