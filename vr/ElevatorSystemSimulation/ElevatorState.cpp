#include<iostream>
#include<ctime>
#include<stdlib.h>
#include"Elevator.h"
#include"ElevatorState.h"
void ElevatorState::DestroyPerson(int DestroyPersonNumber)//���ٵ����е�����
{
	ElevatorPersonNumer-=DestroyPersonNumber;
}
void ElevatorState::AddPerson(int AddPersonNumber)//���ӵ����е�����
{
	ElevatorPersonNumer+=AddPersonNumber;
}
int ElevatorState::GetDrectionState()//���ڻ�ȡ���ڵ��ݵ��������ϣ����»�ֹͣ
{
	return DeractionState;
}
int ElevatorState::GetCurrentfloor()
{
	return Currentfloor;//��ȡ��ǰ����
}
void ElevatorState::InitCurrentfloor()//������������������һ��ʼ���ݵ�λ��
{
	//srand((unsigned)time(NULL));
	Currentfloor=rand()%7+2;
}

void ElevatorState::InitStopTime()//��ʼ����ֹʱ��
{
	StopTime=Fifteen;
}
void ElevatorState::DecreaseStopTime()//��С��ֹʱ�䣬ÿ�μ�С5s
{
	StopTime-=Five;
}
void ElevatorState::SetCurrentfloor(int floornumber)//���õ�ǰ��
{
	Currentfloor=floornumber;
}
void ElevatorState::SetDeractionState(int State)//���õ�������
{
	DeractionState=State;
}
int ElevatorState::GetElevatorPersonNumber()
{
    return ElevatorPersonNumer;
}
void ElevatorState::CheckStopState()//���øõ����Ƿ�ӦΪStopState
{
	  if(ElevatorPersonNumer==0)
		DeractionState=StopState;
}//��ʵֻҪû���˾���StopState��״̬