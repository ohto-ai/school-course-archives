#ifndef identi_Person
#define identi_Person
#define InWork 5
#define OutWork 6
class Person
{
public:
	int m_InBuiding;//0表示不在大楼中，1表示在大楼中
	int m_PatientTime;
	int m_WorkTime;
	Person()
	{
		InitPatientTime();//初始化最大忍受时间
		m_PositionFloor=1;//每个人都初始化为在第一层开始进入大楼
		m_InBuiding=0;//表示不在大楼中
		m_WorkState=OutWork;//一开始每个人都没有在工作
		InitAimFloor();
	}
	int GetState();//获取工作状态，5表示工作，6表示等待电梯
	void SetInWorkState();//设置工作状态，将状态设置为工作状态
	void SetOutWorkState();//设置为非工作状态
	void SetInBuiding();//将参数m_InBuiding设为1，表示在大楼中
    int GetAimfloor();//获取目标层,用于操作电梯
	void SetCurrentfloor();//只要一旦搭上电梯或者超过了忍耐时间，便直接将m_PositionFloor=m_Aimfloor
	void InitCurrentfloor();//初始化楼层，仅用于第一层，将人置于第一层
	int GetCurrentfloor();//获得所在层数
	void InitWorkTime();//初始化工作时间
	void InitAimFloor();//初始化目标层，注意目标层不能为所在层
	int GetPatientTime();
	void InitPatientTime();
private:
	int m_Aimfloor;
	int m_WorkState;//用Inwork，outwork表示
	int m_PositionFloor;//所在层数
};
#endif