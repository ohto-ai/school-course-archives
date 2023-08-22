#include<iostream>
#include"Elevator.h"
#include"buidingfloors.h"
#include"Person.h"
void buidingfloors::GetWaitingPersonList(int* &WaitingList)
{//可得到当层的等待列表
	int i;
	LinkList p;
	for(i=0,p=m_WaitingPersonList->next;p!=NULL;p=p->next,i++)
		WaitingList[i]=p->data;
}

void buidingfloors::AddWaitingPerList(int person)
{//将Person的编号加入等待列表数组中
	AddData(m_WaitingPersonList,person);
}
void buidingfloors::AddAllPersonList(int person)
{//将编号为Person的人加入楼层人数列表中
	AddData(m_AllPersonList,person);
}

void buidingfloors::DeleteWaitingPerList(int person)
{//将编号为Person的人从列表数组中删除
	DeleteData(m_WaitingPersonList,person);
}
void buidingfloors::SetWaitingPerNumber(int AddPersonNumber)
{//在此可以添加或删除等待人数，仅第一层使用
	m_WaitingPerNumber+=AddPersonNumber;
}
void buidingfloors::SetAllPerNumber(int AddPersonNumber)
{
	m_AllPerNumber+=AddPersonNumber;
}
int buidingfloors::GetAllPerNumber()
{//获取本层全部人数
	return m_AllPerNumber;
}

int buidingfloors::GetWaitingPerNumber()
{//获取本层等待人数
	return m_WaitingPerNumber;
}
void  buidingfloors::GetDeleteWaitingPersonListLength(Person* PersonArray)
//该函数获取该层的乘客列表用于获取忍受时间，
{//并且在该函数中逐步减少乘客的忍耐时间（十分重要）
//逐步减少工作时间，获取工作时间完成的人，改变其状态，改变楼层的状态
	LinkList p;
	for(p=m_AllPersonList->next;p!=NULL;p=p->next)
	{
		if(PersonArray[p->data].GetState()==OutWork)//如果没有在工作
		PersonArray[p->data].m_PatientTime-=5;
		else//如果在工作
		{
		    PersonArray[p->data].m_WorkTime-=5;//减少工作时间
			if(PersonArray[p->data].m_WorkTime<=0)
			{//改变状态，该人加入完成工作列表中
				PersonArray[p->data].SetOutWorkState();//表示处于非工作状态
				AddWorkFinishedList(p->data);//加入该层的完成工作列表中
				PersonArray[p->data].InitAimFloor();
			}
		}
	}

}

void buidingfloors::GetFloorButton(int *FloorButton,int* &ElevatorNumber,Elevator* EleVatorArray,Person* PersonArray)
{//在此初始化层按钮，其中有上下键，参数为该层乘客的目标层集合，第二个参数为所选择的电梯号，用于传给相应的电梯Button数组，以控制电梯
//该函数用于选择电梯，选出一台或两台电梯，因为可能有上有下
	int* Up=new int[GetWorkFinishedNumber()];//用于存储要上楼的乘客的目标集合
	int* Down=new int[GetWorkFinishedNumber()];//用于存储要下楼的乘客的目标集合
	int DownCount=0;
	int UpCount=0;
	LinkList p;
	for(p=m_WorkFinishedList->next;p!=NULL;p=p->next)
	{
		if(PersonArray[p->data].GetAimfloor()>m_CurrentFloor)//如果该乘客目标层大于该层
			Up[UpCount++]=p->data;//将该乘客编号存入Up数组中
		else if(PersonArray[p->data].GetAimfloor()<m_CurrentFloor)//如果该乘客目标层小于该层
			Down[DownCount++]=p->data;//将该乘客编号存入Down数组中
	}
	
	   int SuitableUpElevatorNumber[10];
	   int ElevatorCount=0;
		int flagDownUpState=0;
		int flagDownDownState=0;
		int flagUpDownState=0;
		int flagCurrentState=0;
		int flagStop=0;
		for(int i=0;i<10;i++)
		{
           if(EleVatorArray[i].m_State.GetCurrentfloor()==m_CurrentFloor&&EleVatorArray[i].m_State.GetDrectionState()==UpState)
			{
					flagCurrentState=1;//表示该层有向上的电梯
					SuitableUpElevatorNumber[ElevatorCount++]=i;
			}
		}
		if(flagCurrentState==1)//如果当层有电梯
			ElevatorNumber[0]=SuitableUpElevatorNumber[0];///则直接选一台
		else{
			////////////////////应该修改选电梯操作
			/////////////////////////////////
			

		for(int i=0;i<10;i++)
		{
			if(EleVatorArray[i].m_State.GetCurrentfloor()<m_CurrentFloor&&(EleVatorArray[i].m_State.GetDrectionState()==UpState||EleVatorArray[i].m_State.GetDrectionState()==StopState))
			{
					flagDownUpState=1;//表示有在该层下方而且向上或静止的电梯
					SuitableUpElevatorNumber[ElevatorCount++]=i;
			}
		}
		if(flagDownUpState==1)//如有在该层下方而且向上的电梯
		{
			//在此选出一台电梯，并结束选择
			int i;
			int Max=0;
			int MaxNumber=0;
			for(i=0;i<ElevatorCount;i++)
			{
				if(EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor()>Max)
				{//所在层最高的电梯，即为Up集合乘客要选出的电梯
						Max=EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor();
				        MaxNumber=SuitableUpElevatorNumber[i];
				}  
			}
			ElevatorNumber[0]=MaxNumber;//选出电梯给数组ElevatorNumber

		}
		else if(flagDownUpState!=1)
		{
			for(int i=0;i<10;i++)
			{
			if(EleVatorArray[i].m_State.GetCurrentfloor()<m_CurrentFloor&&EleVatorArray[i].m_State.GetDrectionState()==DownState)
			{
				flagDownDownState=1;//表示有在该层下方而且向下的电梯
				SuitableUpElevatorNumber[ElevatorCount++]=i;
			}
			}
			if(flagDownDownState==1)//如有在该层下方而且向下的电梯
			{
				//在此选出一台电梯，并结束选择
				int i;
				int Min=11;
				int MinNumber=0;
				for(i=0;i<ElevatorCount;i++)
			{
				if(EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor()<Min)
				{//所在层最低的电梯，即为Up集合乘客要选出的电梯
						Min=EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor();
				        MinNumber=SuitableUpElevatorNumber[i];
				}  
			}
			ElevatorNumber[0]=MinNumber;//选出电梯给数组ElevatorNumber
			}
			else if(flagDownDownState!=1)
			{
				for(int i=0;i<10;i++)
				{
					if(EleVatorArray[i].m_State.GetCurrentfloor()>m_CurrentFloor&&(EleVatorArray[i].m_State.GetDrectionState()==DownState||EleVatorArray[i].m_State.GetDrectionState()==StopState))
					{
							flagUpDownState=1;//表示有在该层上方且向下或静止的电梯
							SuitableUpElevatorNumber[ElevatorCount++]=i;
					}
				}
				if(flagUpDownState==1)//如有在该层上方而且向下或静止的电梯
				{
					//在此选出一台电梯，并结束选择
				int i;
				int Min=11;
				int MinNumber=0;
				for(i=0;i<ElevatorCount;i++)
			    {
				if(EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor()<Min)
				{//所在层最低的电梯，即为Up集合乘客要选出的电梯
						Min=EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor();
				        MinNumber=SuitableUpElevatorNumber[i];
				}  
			    }
			    ElevatorNumber[0]=MinNumber;//选出电梯给数组ElevatorNumber

				}
				else if(flagUpDownState!=1)
				{
					for(int i=0;i<10;i++)
					{
						if(EleVatorArray[i].m_State.GetCurrentfloor()>m_CurrentFloor&&EleVatorArray[i].m_State.GetDrectionState()==UpState)
					     SuitableUpElevatorNumber[ElevatorCount++]=i;
					}
			int i;
			int Max=0;
			int MaxNumber=0;
			for(i=0;i<ElevatorCount;i++)
			{
				if(EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor()>Max)
				{//所在层最高的电梯，即为Up集合乘客要选出的电梯
						Max=EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor();
				        MaxNumber=SuitableUpElevatorNumber[i];
				}  
			}
			ElevatorNumber[0]=MaxNumber;//选出电梯给数组ElevatorNumber
					//在此选择一台电梯，并结束选择
				}
			}
		}
		}

		int SuitableDownElevatorNumber[10];
		int flagUpUpState=0;
		flagCurrentState=0;
		ElevatorCount=0;
		flagDownUpState=0;
		flagUpDownState=0;


		for(int i=0;i<10;i++)
		{
           if(EleVatorArray[i].m_State.GetCurrentfloor()==m_CurrentFloor&&EleVatorArray[i].m_State.GetDrectionState()==DownState)
			{
					flagCurrentState=1;//表示该层有向下的电梯
					SuitableUpElevatorNumber[ElevatorCount++]=i;
			}
		}
		if(flagCurrentState==1)//如果当层有电梯
			ElevatorNumber[1]=SuitableUpElevatorNumber[0];///则直接选一台
		else{

		for(int i=0;i<10;i++)
		{
			if(EleVatorArray[i].m_State.GetCurrentfloor()>m_CurrentFloor&&(EleVatorArray[i].m_State.GetDrectionState()==DownState||EleVatorArray[i].m_State.GetDrectionState()==StopState))
			{
					flagUpDownState=1;//表示有在该层上方且向下或静止的电梯
					SuitableDownElevatorNumber[ElevatorCount++]=i;
			}
		}
		if(flagUpDownState==1)//如有在该层上方且向下或静止的电梯
		{
			    int i;
				int Min=11;
				int MinNumber=0;
				for(i=0;i<ElevatorCount;i++)
			    {
				if(EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor()<Min)
				{//所在层最低的电梯，即为Down集合乘客要选出的电梯
						Min=EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor();
				        MinNumber=SuitableDownElevatorNumber[i];
				}  
			    }
			    ElevatorNumber[1]=MinNumber;//选出电梯给数组ElevatorNumber
			//在此选出一台电梯，并结束选择
		}
		else if(flagUpDownState!=1)
		{
			for(int i=0;i<10;i++)
			{
				if(EleVatorArray[i].m_State.GetCurrentfloor()>m_CurrentFloor&&EleVatorArray[i].m_State.GetDrectionState()==UpState)
			{
					flagUpUpState=1;//表示有在该层上方且向上的电梯
					SuitableDownElevatorNumber[ElevatorCount++]=i;
			}
			}
			if(flagUpUpState==1)//表示如有在该层上方且向上的电梯
			{
			int i;
			int Max=0;
			int MaxNumber=0;
			for(i=0;i<ElevatorCount;i++)
			{
				if(EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor()>Max)
				{//所在层最高的电梯，即为Down集合乘客要选出的电梯
						Max=EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor();
				        MaxNumber=SuitableDownElevatorNumber[i];
				}  
			}
			ElevatorNumber[1]=MaxNumber;//选出电梯给数组ElevatorNumber
				//在此选择一台电梯，并结束选择
			}
			else if(flagUpUpState!=1)
			{
				for(int i=0;i<10;i++)
				{
					if(EleVatorArray[i].m_State.GetCurrentfloor()<m_CurrentFloor&&(EleVatorArray[i].m_State.GetDrectionState()==UpState||EleVatorArray[i].m_State.GetDrectionState()==StopState))
			    {
					flagDownUpState=1;//表示有在该层下方且向上或静止的电梯
					SuitableDownElevatorNumber[ElevatorCount++]=i;
			    }
				}
				if(flagDownUpState==1)
				{
			int i;
			int Max=0;
			int MaxNumber=0;
			for(i=0;i<ElevatorCount;i++)
			{
				if(EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor()>Max)
				{//所在层最高的电梯，即为Down集合乘客要选出的电梯
						Max=EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor();
				        MaxNumber=SuitableDownElevatorNumber[i];
				}  
			}
			ElevatorNumber[1]=MaxNumber;//选出电梯给数组ElevatorNumber
					//在此选择一台电梯，并结束选择
				}
				else if(flagDownUpState!=1)
				{
					for(int i=0;i<10;i++)
					{
						if(EleVatorArray[i].m_State.GetCurrentfloor()<m_CurrentFloor&&EleVatorArray[i].m_State.GetDrectionState()==DownState)
			        {
					//表示有在该层下方且向下的电梯
					SuitableDownElevatorNumber[ElevatorCount++]=i;
			        }
					}
				int i;
				int Min=11;
				int MinNumber=0;
				for(i=0;i<ElevatorCount;i++)
			    {
				if(EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor()<Min)
				{//所在层最低的电梯，即为Down集合乘客要选出的电梯
						Min=EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor();
				        MinNumber=SuitableDownElevatorNumber[i];
				}  
			    }
			    ElevatorNumber[1]=MinNumber;//选出电梯给数组ElevatorNumber
					//在此选择一台电梯，并结束选择
				}
			}
		}
		}
		if(UpCount==0)//如果无人向上
			ElevatorNumber[0]=-1;//则置-1
		if(DownCount==0)//如果无人向下
			ElevatorNumber[1]=-1;//则置-1
		delete [] Up;//释放内存
		delete [] Down;//释放内存
}
int buidingfloors::GetWorkFinishedNumber()//获取工作刚刚完成的人的人数
{
	int i=0;
	LinkList p;
	for(p=m_WorkFinishedList->next;p!=NULL;p=p->next)
		i++;
	return i;
}
void buidingfloors::AddWorkList(int Person)//将编号为Person的人加入，工作列表中
{
	AddData(m_WorkList,Person);
}

void buidingfloors::GetWorkFinishedList(int* &WorkFinishedList)//可以获得刚刚完成工作的人，并改变其状态
{
	LinkList p;
	int i=0;
	for(p=m_WorkFinishedList->next;p!=NULL;p=p->next,i++)
		WorkFinishedList[i]=p->data;
}
void buidingfloors::AddWorkFinishedList(int Person)//将编号为Person的人加入工作完成列表中，进第一层使用，并改变其状态
{
	AddData(m_WorkFinishedList,Person);
}
void buidingfloors::SetCurrentFloor(int FloorNumber)//初始化该层层号
{
	m_CurrentFloor=FloorNumber;
}
void  buidingfloors::SetElevatorAndPersonNumber(Elevator* ElevatorArray,Person* PersonArray)
{//本函数，更新该层的所有状态
	//现将所有列表置空
	DestroyData(m_WorkList);
	DestroyData(m_WaitingPersonList);
	DestroyData(m_AllPersonList);

	int ElevatorCount=0;
	int AllNumberPeople=0;
	int WorkPeopleNumber=0;
	int WaitingPeopleNumber=0;
	for(int i=0;i<10;i++)
	{
		if(ElevatorArray[i].m_State.GetCurrentfloor()==m_CurrentFloor)
		{//选出处于当层的电梯
			ElevatorCount++;
		}
	}
	m_ElevatorNumber=ElevatorCount;//选出电梯数
	for(int i=1;PersonArray[i].m_InBuiding!=0;i++)
	{
		if(PersonArray[i].GetCurrentfloor()==m_CurrentFloor)//如果此人处于当前层
		{
				AllNumberPeople++;
				AddData(m_AllPersonList,i);
		}
		if(PersonArray[i].GetCurrentfloor()==m_CurrentFloor&&PersonArray[i].GetState()==InWork)
		{
				WorkPeopleNumber++;
				AddData(m_WorkList,i);
		}
		if(PersonArray[i].GetCurrentfloor()==m_CurrentFloor&&PersonArray[i].GetState()==OutWork)
		{
				WaitingPeopleNumber++;
				AddData(m_WaitingPersonList,i);
		}
	}
	m_AllPerNumber=AllNumberPeople;
	m_ElevatorNumber=ElevatorCount;
	m_WaitingPerNumber=WaitingPeopleNumber;
	m_WorkPersonNumber=WorkPeopleNumber;
}
int  buidingfloors::GetElevatorNumber()//获取当层的电梯数量，以供显示
{
	return m_ElevatorNumber;
}