#include"Elevator.h"
#include"Person.h"
#include"LinkList.h"
#ifndef identi_buidingfloors
#define identi_buidingfloors
class buidingfloors
{
public:
	int m_CurrentFloor;
	LinkList m_WorkFinishedList;//表示刚刚完成工作的人列表
	LinkList m_WorkList;//表示正在工作的人的列表
	LinkList m_WaitingPersonList;//该层中等待人数的列表
	LinkList m_AllPersonList;//该层中所有人数的列表，存储人的对象的编号即可
	buidingfloors()
	{
		CreateList(m_WaitingPersonList);
		CreateList(m_AllPersonList);
	    CreateList(m_WorkList);
		CreateList(m_WorkFinishedList);
	 m_AllPerNumber=0;//该层总人数
	 m_ElevatorNumber=0;//电梯的数量
	 m_WaitingPerNumber=0;//等待的人数
	 m_WorkPersonNumber=0;//工作人数
	}
	int GetWorkFinishedNumber();//获取工作刚刚完成的人的人数
	void AddWorkList(int Person);//将编号为Person的人加入，工作列表中
	void GetWorkFinishedList(int* &WorkFinishedList);//可以获得刚刚完成工作的人，并改变其状态
	void AddWorkFinishedList(int Person);//将编号为Person的人加入工作完成列表中，进第一层使用，并改变其状态

	void SetCurrentFloor(int FloorNumber);//初始化该层层号
	void GetWaitingPersonList(int* &WaitingList);//此处一定记住WaitingList与工作状态有关，获取当前等待列表
	void AddWaitingPerList(int person);//将Person的编号加入等待列表数组中
	void AddAllPersonList(int Person);//将编号为Person的人加入楼层人数列表中
	void DeleteWaitingPerList(int person);//将编号为Person的人从列表数组中删除
	void SetWaitingPerNumber(int AddPersonNumber);//在此可以添加或删除等待人数，可采用数组的形式存储乘客，仅第一层使用
	void SetAllPerNumber(int AddPersonNumber);
	int  GetWaitingPerNumber();//获取当层的等待人数，以供显示
	int  GetAllPerNumber();//获取当层所有人数，以供显示
	void  GetDeleteWaitingPersonListLength(Person* PersonArray);//该函数获取该层的乘客列表用于获取忍受时间，
	//并且在该函数中逐步减少乘客的忍耐时间（十分重要）

	void  SetElevatorAndPersonNumber(Elevator* ElevatorArray,Person* PersonArray);//有十架电梯的状态设置当层电梯数和人数，在此可增加或减少电梯数
	int  GetElevatorNumber();//获取当层的电梯数量，以供显示
	void GetFloorButton(int *FloorButton,int* &ElevatorNumber,Elevator* ElevatorArray,Person* PersonArray);//在此初始化层按钮，其中有上下键，参数为该层乘客的目标层集合，第二个参数为所选择的电梯号，用于传给相应的电梯Button数组，以控制电梯
	//该函数用于选择电梯，选出一台或两台电梯，因为可能有上有下
private:
	int m_AllPerNumber;//该层总人数
	int m_ElevatorNumber;//电梯的数量
	int m_WaitingPerNumber;//等待的人数
	int m_WorkPersonNumber;//工作人数
};
#endif
