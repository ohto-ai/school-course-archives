#include<iostream>
#include<ctime>
#include<Windows.h>
#include<stdlib.h>
#include"Buiding.h"
#include"Person.h"
#include"Run.h"
#include"TimeStateChange.h"
#define PersonNumberMax 501
using namespace std;
void GetTimeChangeButton();
Buiding LXN_Building;//初始化整栋大楼，作为文件变量
Person LXN_Person[PersonNumberMax];//初始化五百个人，此时所有人均还不在大楼中,第一号元素不用
int PersonNumberFirstLimit=1;
int PersonNumberLastLimit=1;
int AddPersonNumber;
void InitFloors();
void GetAllElevatorNumber();
void Door();
void Run()//该函数中激活整栋大楼，初始化大楼，此时楼层，电梯也将被初始化
{
	int i,j;

	Door();//开始有人进入大楼，随机产生人数
	///////////////Test/////////////
	/*if(flag==1)
	{
		AddPersonNumber=1;
		PersonNumberFirstLimit=1;
        PersonNumberLastLimit=2;
	}
	else
	{
		AddPersonNumber=0;
		 PersonNumberFirstLimit=2;
         PersonNumberLastLimit=2;
	}
	*/
	//////////////////////////////
	LXN_Building.m_floor[1].SetWaitingPerNumber(AddPersonNumber);//每隔一段时间，有人进入大楼，而且都是进入第一层，且均等待
	LXN_Building.m_floor[1].SetAllPerNumber(AddPersonNumber);//加入该层总人数中
	if(AddPersonNumber!=0)
	for(i=PersonNumberFirstLimit;i<PersonNumberLastLimit;i++)
	{
		LXN_Building.m_floor[1].AddAllPersonList(i);//此时i即为要进入大楼的人的编号，且都是进入第一层
		LXN_Building.m_floor[1].AddWorkFinishedList(i);//均为等待状态，加入工作刚刚完成的人列表中
		LXN_Building.m_floor[1].AddWaitingPerList(i);
		LXN_Person[i].SetInBuiding();//表示该人进入大楼了
		LXN_Person[i].InitCurrentfloor();//表示一开始该人处于第一层
	}
	//在此要求每个楼层的人都进行活动，电梯也进行活动
	
	for( i=1;i<11;i++)//表示十个电梯的编号
	{
		int WaitingPersonSize;
		WaitingPersonSize=LXN_Building.m_floor[i].GetWorkFinishedNumber();//获取该层的等待人数,应该获取工作完成了的人数
		int* FloorButton=new int[WaitingPersonSize];//构造该层乘客的目标层集合
		int* WaitingPersonList=new int[WaitingPersonSize];//构造乘客列表
		LXN_Building.m_floor[i].GetWorkFinishedList(WaitingPersonList);
		//获取在该层中乘客的列表
		
		
		for(j=0;j<WaitingPersonSize;j++)//获取该列表中乘客的目标层集合
			FloorButton[j]=LXN_Person[WaitingPersonList[j]].GetAimfloor();
		int* ElevatorNumberList=new int[2];//定义数组存储选出的电梯号
		LXN_Building.m_floor[i].GetFloorButton(FloorButton,ElevatorNumberList,LXN_Building.m_Elevator,LXN_Person);//选出要在该层停下的电梯号,存入ElevatorNumberList中
		//ElevatorNumberList[0]中的电梯运载该层向上的乘客，ElevatorNumberList[1]中的电梯运载该层向下的乘客
	//注意他没有返回值
	
	
	//LXN_Building.m_floor[i].InitDeletePersonList(DeletePersonList);//将因超过忍耐时间而要走楼梯的人的列表存入该层对象中
	/*for(k=0;k<DeleteListSize;k++)
	{
		//从该层的等待人列表中删除因超过忍耐时间而要走楼梯的人，该列表为两架电梯的总列表
		//LXN_Building.m_floor[i].DeleteWaitingPerList(DeletePersonList[k]);该句放到外面用于控制时间
		LXN_Person[DeletePersonList[k]].SetCurrentfloor();//表示该人已经选择走楼梯，且已经到达
		//LXN_Person[DeletePersonList[k]].GetStairseWorkStateTime();该函数可返回该乘客下一次按电梯按钮的时间间隔
	}
	*/
	////////////////
	//注意在这里要进行乘客的忍耐时间的减少
	//需要插入时间模拟，该模拟在选择乘客的函数中进行
	///////////////

	//此处应该将LeftPersonList分类，分别给两个电梯
	int* Up=new int[LXN_Building.m_floor[i].GetWorkFinishedNumber()];//用于存储要上楼的乘客的目标集合
	int* Down=new int[LXN_Building.m_floor[i].GetWorkFinishedNumber()];//用于存储要下楼的乘客的目标集合
	int UpCount=0;
	int DownCount=0;
	for(int j=0;j<LXN_Building.m_floor[i].GetWorkFinishedNumber();j++)
	{//刚刚完成工作的人
		if(LXN_Person[WaitingPersonList[j]].GetAimfloor()>i)//如果该乘客目标层大于该层
			Up[UpCount++]=WaitingPersonList[j];//将该乘客编号存入Up数组中
		else if(LXN_Person[WaitingPersonList[j]].GetAimfloor()<i)//如果该乘客目标层小于该层
			Down[DownCount++]=WaitingPersonList[j];//将该乘客编号存入Down数组中
	}
	if(ElevatorNumberList[0]!=-1)
	{
LXN_Building.m_Elevator[ElevatorNumberList[0]].AddOneButton(i,Up,UpCount);//通知所选择的电梯，使其能在该层停留
//应加入乘客列表
LXN_Building.m_Elevator[ElevatorNumberList[0]].SetButton(Up,LXN_Person,
					UpCount);//将该层Up乘客的目标层集合导入所选电梯中，改变电梯的按钮数组,应导入Up
	}
	if(ElevatorNumberList[1]!=-1)
	{
LXN_Building.m_Elevator[ElevatorNumberList[1]].AddOneButton(i,Down,DownCount);//通知所选择的电梯，使其能在该层停留
//应加入乘客列表
LXN_Building.m_Elevator[ElevatorNumberList[1]].SetButton(Down,LXN_Person,
					DownCount);		
	}
	//将该层Down乘客的目标层集合导入所选电梯中，改变电梯的按钮数组,应导入Down
    //此时已经将乘客分类并且，将不同的目标层集合，导入了不同的电梯中
    //ElevatorNumberList[0]中的电梯运载该层向上的乘客，ElevatorNumberList[1]中的电梯运载该层向下的乘客
	//电梯知道了要走到什么层之后，便可以随时间模拟改变其状态

	/*for(k=0;k<LXN_Building.m_floor[i].GetLeftPersonNumber();k++)
	{
		//LXN_Building.m_floor[i].DeleteWaitingPerList(LeftPersonList[k]);//从该层等待乘客列表中删除搭上电梯的乘客,该句放在外面，用于改变楼层的状态
		LXN_Person[LeftPersonList[k]].SetCurrentfloor();//表示该人已经上电梯，并且到达了目标层（注意程序规定人一上电梯立即修改人的状态，使其进入目标层）
		//LXN_Person[LeftPersonList[k]].GetElevatorWorkStateTime(FloorButton);//该函数可返回坐电梯的人下一次按电梯按钮的时间间隔
		//可用于与Sleep()做时间模拟
	}*///上电梯之后应该到电梯状态改变时在进行改变
	 //到此人与电梯与楼层三者之间的关系描述就结束了
	//开始进行所有状态的改变，将Sleep(500);与状态修改放入一个同一个while，控制状态的变化
	//立即清空WorkFinishedList乘客列表
	DestroyData(LXN_Building.m_floor[i].m_WorkFinishedList);
			
	LXN_Building.m_floor[i].GetDeleteWaitingPersonListLength(LXN_Person);
	//将该楼层中正在等待的人减去5s的忍耐时间，求出忍耐时间小于0的人的列表，构造DeletePersonList，不能计算出搭上电梯的人，搭上电梯的人应放在电梯状态改变时计算
	delete [] FloorButton;//释放内存
	delete [] WaitingPersonList;
	delete [] ElevatorNumberList;
	delete [] Up;
	delete [] Down;
	
		//剩下电梯与楼层的状态，人只需要根据工作时间变化即可
	}

		//此处加入状态改变函数
	
		//TimeStateChange();
		//该函数可以以5秒为一个周期，5秒之后退出while
		//该函数结合OpenGL即可绘制出图形界面
		//该函数可以检验是否改变当前电梯的状态，比如是否到达另一层，因为电梯停靠为15s，上下楼为5s
		//所以，当该循环结束时，所有的电梯都正好在某一层的位置，不会出现在某两层中间
		//人是否等待是受到电梯状态控制的，所以应该将人的忍耐时间与电梯的状态相关联
		//Sleep(500);
	       GetTimeChangeButton();
			for(i=0;i<10;i++)//该改变的改变，没变的继续保持原状
			{
				    //改变电梯的状态，关于参数的问题，虽然，传入的是总人数，但是该函数内部可进行筛选
				    //搭上电梯的人应放在电梯状态改变时计算
				    LXN_Building.m_Elevator[i].ChangState(LXN_Person);
			}
			for(i=1;i<11;i++)
			{
				//改变楼层状态,根据LXN_Person可以更新所有状态
					LXN_Building.m_floor[i].SetElevatorAndPersonNumber(LXN_Building.m_Elevator,LXN_Person);
					
			}
			//此时电梯，楼层的状态均已改	
			GetAllElevatorNumber();
			
		//需要将DeletePersonList,LeftPersonList作为buidingfloors对象的成员
		//需要在Person类中添加两个时间成员，该成员表示下一次按按钮的时间间隔，分别为坐电梯和走楼梯的间隔。
}
void Door()//仅仅产生进入大楼的人数，并且初始化Person对象数组
{
	//AddPersonNumber=rand()%50;
	////////Test////////////////
	//srand((unsigned)time(NULL));
	int Number=rand()%5;
	
	////////////////////
	if(PersonNumberLastLimit+Number<=PersonNumberMax)//注意总数不能超过五百
	{
		AddPersonNumber=Number;
	PersonNumberFirstLimit=PersonNumberLastLimit;
	PersonNumberLastLimit+=AddPersonNumber;
	LXN_Building.ChangeTotalpeopleNumber(AddPersonNumber);//增加大楼里的人数
	}
	else
		AddPersonNumber=0;
}
void InitFloors()
{
	int i;
	for(i=1;i<11;i++)
		LXN_Building.m_floor[i].SetCurrentFloor(i);
}

void GetTimeChangeButton()
{
	for(int i=0;i<10;i++)
		for(int j=1;j<11;j++)
		TimeButton[i][j]=LXN_Building.m_Elevator[i].m_Button[j];
	for(int i=0;i<10;i++)
	{
		AllStopTime[i]=LXN_Building.m_Elevator[i].m_State.StopTime;
	}
	for(int i=0;i<10;i++)
	{
		AllCurrentfloor[i]=LXN_Building.m_Elevator[i].m_State.GetCurrentfloor();
	}
	for(int i=0;i<10;i++)
	{
		AllElevatorPersonNumber[i]=LXN_Building.m_Elevator[i].m_State.GetElevatorPersonNumber();
		AllElevatorState[i]=LXN_Building.m_Elevator[i].m_State.GetDrectionState();
	}
	for(int i=1;i<11;i++)
	{
		AllFloorPersonNumber[i]=LXN_Building.m_floor[i].GetAllPerNumber();
		AllFloorPersonNumber[i]=LXN_Building.m_floor[i].GetAllPerNumber();
	}
}
void GetAllElevatorNumber()
{
	for(int i=1;i<11;i++)
	{
	AllFloorElevatorNumber[i]=LXN_Building.m_floor[i].GetElevatorNumber();
	}
}