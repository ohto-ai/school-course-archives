#include"LinkList.h"
#ifndef identi_ElevatorState
#define identi_ElevatorState
#define UpState 0
#define DownState 1
#define StopState 2//��һ��stopState����ʾ����ʱ�õ���û������
#define Fifteen 3
#define Ten 2
#define Five 1
class ElevatorState
{
public:
	int StopTime;//��Ҫ�����ж�5s��õ����Ƿ�仯״̬��Fifteen��ʾ15���ı� Ten��ʾʮ���ı� Five ��ʾ5���ı�
	ElevatorState()
	{
		ElevatorPersonNumer=0;
		InitCurrentfloor();
		DeractionState=StopState;
		CreateList(ElevatorList);
	}
	LinkList ElevatorList;//��ʾ�����е������б�
	void DestroyPerson(int DestroyPersonNumber);//��ɾ�����е�����,ֻ���������
	void AddPerson(int AddPersonNumber);
	void SetCurrentfloor(int floornumber);//���õ�ǰ��
	int GetDrectionState();//���ڻ�ȡ���ڵ��ݵ��������ϣ����»�ֹͣ
	int GetCurrentfloor();//��ȡ��ǰ����
	void InitCurrentfloor();//������������������һ��ʼ���ݵ�λ��
	void InitStopTime();//��ʼ����ֹʱ��
	void DecreaseStopTime();//��С��ֹʱ�䣬ÿ�μ�С5s
	void SetDeractionState(int State);//���õ�������
	int GetElevatorPersonNumber();//��ȡ�����е�����
	void CheckStopState();//���øõ����Ƿ�ӦΪStopState
private:
	int Currentfloor;
	int DeractionState;//��ʾ���ڵ��ݵ��������ϣ����»�ֹͣ,�ֱ���UpState,DownState,StopState��ʾ
	//ʵ���ϴӳ���ĽǶ�������ÿһ���ҽ���״̬����ʱ�����ݶ��Ǿ�ֹ�ģ�
	//���Ը�������Ҫ��ʾ��ֹ��һ״̬
	int ElevatorPersonNumer;//��ʾ�����е�����
	
};
#endif
