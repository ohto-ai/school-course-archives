#include<iostream>
#include<ctime>
#include<stdlib.h>
#include"Elevator.h"
#include"ElevatorState.h"
void ElevatorState::DestroyPerson(int DestroyPersonNumber)//减少电梯中的人数
{
	ElevatorPersonNumer-=DestroyPersonNumber;
}
void ElevatorState::AddPerson(int AddPersonNumber)//增加电梯中的人数
{
	ElevatorPersonNumer+=AddPersonNumber;
}
int ElevatorState::GetDrectionState()//用于获取现在电梯的走向向上，向下或停止
{
	return DeractionState;
}
int ElevatorState::GetCurrentfloor()
{
	return Currentfloor;//获取当前层数
}
void ElevatorState::InitCurrentfloor()//利用随机数，随机生成一开始电梯的位置
{
	//srand((unsigned)time(NULL));
	Currentfloor=rand()%7+2;
}

void ElevatorState::InitStopTime()//初始化静止时间
{
	StopTime=Fifteen;
}
void ElevatorState::DecreaseStopTime()//减小静止时间，每次减小5s
{
	StopTime-=Five;
}
void ElevatorState::SetCurrentfloor(int floornumber)//设置当前层
{
	Currentfloor=floornumber;
}
void ElevatorState::SetDeractionState(int State)//设置电梯走向
{
	DeractionState=State;
}
int ElevatorState::GetElevatorPersonNumber()
{
    return ElevatorPersonNumer;
}
void ElevatorState::CheckStopState()//设置该电梯是否应为StopState
{
	  if(ElevatorPersonNumer==0)
		DeractionState=StopState;
}//其实只要没人了就是StopState的状态