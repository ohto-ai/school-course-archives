#include<iostream>
#include<ctime>
#include<stdlib.h>
#include"Person.h"
int Person::GetState()//��ȡ����״̬��5��ʾ������6��ʾ�ȴ�����
{
	return m_WorkState;
}
void Person::SetInWorkState()//���ù���״̬����״̬����Ϊ����״̬
{
	m_WorkState=InWork;
	InitWorkTime();
}
void Person::SetOutWorkState()//����Ϊ�ǹ���״̬
{
	m_WorkState=OutWork;

}

void Person::SetInBuiding()//������m_InBuiding��Ϊ1����ʾ�ڴ�¥��
{
	m_InBuiding=1;
}
int Person::GetAimfloor()//��ȡĿ���,���ڲ�������
{
	return m_Aimfloor;
}
void Person::SetCurrentfloor()//ֻҪһ�����ϵ��ݻ��߳���������ʱ�䣬��ֱ�ӽ�m_PositionFloor=m_Aimfloor
{
	m_PositionFloor=m_Aimfloor;
}
void Person::InitCurrentfloor()//��ʼ��¥�㣬�����ڵ�һ�㣬�������ڵ�һ��
{
	m_PositionFloor=1;
}
int Person::GetCurrentfloor()//������ڲ���
{
	return m_PositionFloor;
}
void Person::InitWorkTime()//��ʼ������ʱ��
{
	//m_WorkTime=5;

	m_WorkTime=rand()%40+20;
}
void Person::InitAimFloor()//��ʼ��Ŀ��㣬ע��Ŀ��㲻��Ϊ���ڲ�
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
