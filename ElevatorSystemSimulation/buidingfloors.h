#include"Elevator.h"
#include"Person.h"
#include"LinkList.h"
#ifndef identi_buidingfloors
#define identi_buidingfloors
class buidingfloors
{
public:
	int m_CurrentFloor;
	LinkList m_WorkFinishedList;//��ʾ�ո���ɹ��������б�
	LinkList m_WorkList;//��ʾ���ڹ������˵��б�
	LinkList m_WaitingPersonList;//�ò��еȴ��������б�
	LinkList m_AllPersonList;//�ò��������������б��洢�˵Ķ���ı�ż���
	buidingfloors()
	{
		CreateList(m_WaitingPersonList);
		CreateList(m_AllPersonList);
	    CreateList(m_WorkList);
		CreateList(m_WorkFinishedList);
	 m_AllPerNumber=0;//�ò�������
	 m_ElevatorNumber=0;//���ݵ�����
	 m_WaitingPerNumber=0;//�ȴ�������
	 m_WorkPersonNumber=0;//��������
	}
	int GetWorkFinishedNumber();//��ȡ�����ո���ɵ��˵�����
	void AddWorkList(int Person);//�����ΪPerson���˼��룬�����б���
	void GetWorkFinishedList(int* &WorkFinishedList);//���Ի�øո���ɹ������ˣ����ı���״̬
	void AddWorkFinishedList(int Person);//�����ΪPerson���˼��빤������б��У�����һ��ʹ�ã����ı���״̬

	void SetCurrentFloor(int FloorNumber);//��ʼ���ò���
	void GetWaitingPersonList(int* &WaitingList);//�˴�һ����סWaitingList�빤��״̬�йأ���ȡ��ǰ�ȴ��б�
	void AddWaitingPerList(int person);//��Person�ı�ż���ȴ��б�������
	void AddAllPersonList(int Person);//�����ΪPerson���˼���¥�������б���
	void DeleteWaitingPerList(int person);//�����ΪPerson���˴��б�������ɾ��
	void SetWaitingPerNumber(int AddPersonNumber);//�ڴ˿�����ӻ�ɾ���ȴ��������ɲ����������ʽ�洢�˿ͣ�����һ��ʹ��
	void SetAllPerNumber(int AddPersonNumber);
	int  GetWaitingPerNumber();//��ȡ����ĵȴ��������Թ���ʾ
	int  GetAllPerNumber();//��ȡ���������������Թ���ʾ
	void  GetDeleteWaitingPersonListLength(Person* PersonArray);//�ú�����ȡ�ò�ĳ˿��б����ڻ�ȡ����ʱ�䣬
	//�����ڸú������𲽼��ٳ˿͵�����ʱ�䣨ʮ����Ҫ��

	void  SetElevatorAndPersonNumber(Elevator* ElevatorArray,Person* PersonArray);//��ʮ�ܵ��ݵ�״̬���õ�����������������ڴ˿����ӻ���ٵ�����
	int  GetElevatorNumber();//��ȡ����ĵ����������Թ���ʾ
	void GetFloorButton(int *FloorButton,int* &ElevatorNumber,Elevator* ElevatorArray,Person* PersonArray);//�ڴ˳�ʼ���㰴ť�����������¼�������Ϊ�ò�˿͵�Ŀ��㼯�ϣ��ڶ�������Ϊ��ѡ��ĵ��ݺţ����ڴ�����Ӧ�ĵ���Button���飬�Կ��Ƶ���
	//�ú�������ѡ����ݣ�ѡ��һ̨����̨���ݣ���Ϊ������������
private:
	int m_AllPerNumber;//�ò�������
	int m_ElevatorNumber;//���ݵ�����
	int m_WaitingPerNumber;//�ȴ�������
	int m_WorkPersonNumber;//��������
};
#endif
