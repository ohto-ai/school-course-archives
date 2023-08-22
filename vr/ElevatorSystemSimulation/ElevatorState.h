#include"LinkList.h"
#ifndef identi_ElevatorState
#define identi_ElevatorState
#define UpState 0
#define DownState 1
#define StopState 2//加一个stopState，表示，此时该电梯没有任务
#define Fifteen 3
#define Ten 2
#define Five 1
class ElevatorState
{
public:
	int StopTime;//主要用于判断5s后该电梯是否变化状态，Fifteen表示15秒后改变 Ten表示十秒后改变 Five 表示5秒后改变
	ElevatorState()
	{
		ElevatorPersonNumer=0;
		InitCurrentfloor();
		DeractionState=StopState;
		CreateList(ElevatorList);
	}
	LinkList ElevatorList;//表示电梯中的人数列表
	void DestroyPerson(int DestroyPersonNumber);//增删电梯中的人数,只需添加数量
	void AddPerson(int AddPersonNumber);
	void SetCurrentfloor(int floornumber);//设置当前层
	int GetDrectionState();//用于获取现在电梯的走向向上，向下或停止
	int GetCurrentfloor();//获取当前层数
	void InitCurrentfloor();//利用随机数，随机生成一开始电梯的位置
	void InitStopTime();//初始化静止时间
	void DecreaseStopTime();//减小静止时间，每次减小5s
	void SetDeractionState(int State);//设置电梯走向
	int GetElevatorPersonNumber();//获取电梯中的人数
	void CheckStopState();//设置该电梯是否应为StopState
private:
	int Currentfloor;
	int DeractionState;//表示现在电梯的走向向上，向下或停止,分别用UpState,DownState,StopState表示
	//实际上从程序的角度来讲，每一次我进行状态检验时，电梯都是静止的，
	//所以根本不需要表示静止这一状态
	int ElevatorPersonNumer;//表示电梯中的人数
	
};
#endif
