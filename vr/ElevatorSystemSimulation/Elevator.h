#include"ElevatorState.h"
#include"Person.h"
#ifndef identi_EleVator
#define identi_EleVator
#define ButtonPress 1
#define Un_ButtonPress 0
class Elevator//该类只要管Button的操作就行，其他的工作交给ElevatorState类
{
public:
	ElevatorState m_State;
	/////////////////////Test/////////////
	int m_Button[11];
	////////////////////////
	Elevator()//初始化三类Button数组，将其全都置为零，表示无目标层
	{
        int i;
		for(i=0;i<11;i++)
		{
			m_Button[i]=0;
			m_TempButton[i]=0;
		}
		for(i=0;i<11;i++)
		CreateList(m_AddPersonButton[i]);
	}
	void ChangState(Person* PersonArray);//改变当前状态，设置当前层数,设置人数,电梯上下状态，参数为搭上电梯的人的列表，用于获取乘客的目标层而控制乘客数量
	//注意如果改变了电梯的上下状态，则应调用ChangButton函数
	void AddOneButton(int Button,int* PersonList,int PersonNumber);//用于添加一个目标层给临时Button数组或给Button数组，并添加要搭上该电梯的人的编号
	//传给m_AddPersonButton[10][500]；将要做这台电梯的人的列表加入其中
	void GetButton(int* &ButtonArray);//获取Button数组,给ButtonAray
	void ChangeButton();//将新加入的Button导入Button数组中，进行电梯的下一轮移动
	void CheckAndChangeButton();//根据ElevatorState中的当前层数改变Button数组，到站了则置Un_ButtonPress
	//是否需要，待定
	//void AddTime();//此处应添加参数，该参数与人的位置有关，该函数待定
    void SetButton(int* LeftPersonList,Person* PersonArray,int LeftPerListLength);//传入要搭上电梯的人,停下之后有停下的这一层乘客目标层集合决定,该函数构建一个数组
	//从中应该选出哪一个给电梯一，哪一个给电梯二
private:
	//int m_Button[11];//Button数组表示将要停留的层,分别用ButtonPress与Un_ButtonPerss表示
	int m_TempButton[11];//创建一个临时的Button数组，用来储存新传入的与电梯方向相反的楼层号
	LinkList m_AddPersonButton[11];//用于储存AddOneButton加入的Button，表示电梯到达该层后，会增加人数，存入人的编号
	
};
#endif