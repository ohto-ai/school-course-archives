#include<iostream>
#include<ctime>
#include<stdlib.h>
#include"Person.h"
int Person::GetState()//获取工作状态，5表示工作，6表示等待电梯
{
	return m_WorkState;
}
void Person::SetInWorkState()//设置工作状态，将状态设置为工作状态
{
	m_WorkState=InWork;
	InitWorkTime();
}
void Person::SetOutWorkState()//设置为非工作状态
{
	m_WorkState=OutWork;

}

void Person::SetInBuiding()//将参数m_InBuiding设为1，表示在大楼中
{
	m_InBuiding=1;
}
int Person::GetAimfloor()//获取目标层,用于操作电梯
{
	return m_Aimfloor;
}
void Person::SetCurrentfloor()//只要一旦搭上电梯或者超过了忍耐时间，便直接将m_PositionFloor=m_Aimfloor
{
	m_PositionFloor=m_Aimfloor;
}
void Person::InitCurrentfloor()//初始化楼层，仅用于第一层，将人置于第一层
{
	m_PositionFloor=1;
}
int Person::GetCurrentfloor()//获得所在层数
{
	return m_PositionFloor;
}
void Person::InitWorkTime()//初始化工作时间
{
	//m_WorkTime=5;

	m_WorkTime=rand()%40+20;
}
void Person::InitAimFloor()//初始化目标层，注意目标层不能为所在层
{
	//srand((unsigned)time(NULL));
	while(1)
	{
		
		m_Aimfloor=rand()%9+1;
		if(m_Aimfloor!=m_PositionFloor)
			break;
	}
}
void Person::InitPatientTime()
{
	//srand((unsigned)time(NULL));
	m_PatientTime=rand()%180+180;
}
int Person::GetPatientTime()
{
	return m_PatientTime;
}
