#include"ElevatorState.h"
#include"Person.h"
#ifndef identi_EleVator
#define identi_EleVator
#define ButtonPress 1
#define Un_ButtonPress 0
class Elevator//����ֻҪ��Button�Ĳ������У������Ĺ�������ElevatorState��
{
public:
	ElevatorState m_State;
	/////////////////////Test/////////////
	int m_Button[11];
	////////////////////////
	Elevator()//��ʼ������Button���飬����ȫ����Ϊ�㣬��ʾ��Ŀ���
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
	void ChangState(Person* PersonArray);//�ı䵱ǰ״̬�����õ�ǰ����,��������,��������״̬������Ϊ���ϵ��ݵ��˵��б����ڻ�ȡ�˿͵�Ŀ�������Ƴ˿�����
	//ע������ı��˵��ݵ�����״̬����Ӧ����ChangButton����
	void AddOneButton(int Button,int* PersonList,int PersonNumber);//�������һ��Ŀ������ʱButton������Button���飬�����Ҫ���ϸõ��ݵ��˵ı��
	//����m_AddPersonButton[10][500]����Ҫ����̨���ݵ��˵��б��������
	void GetButton(int* &ButtonArray);//��ȡButton����,��ButtonAray
	void ChangeButton();//���¼����Button����Button�����У����е��ݵ���һ���ƶ�
	void CheckAndChangeButton();//����ElevatorState�еĵ�ǰ�����ı�Button���飬��վ������Un_ButtonPress
	//�Ƿ���Ҫ������
	//void AddTime();//�˴�Ӧ��Ӳ������ò������˵�λ���йأ��ú�������
    void SetButton(int* LeftPersonList,Person* PersonArray,int LeftPerListLength);//����Ҫ���ϵ��ݵ���,ͣ��֮����ͣ�µ���һ��˿�Ŀ��㼯�Ͼ���,�ú�������һ������
	//����Ӧ��ѡ����һ��������һ����һ�������ݶ�
private:
	//int m_Button[11];//Button�����ʾ��Ҫͣ���Ĳ�,�ֱ���ButtonPress��Un_ButtonPerss��ʾ
	int m_TempButton[11];//����һ����ʱ��Button���飬���������´��������ݷ����෴��¥���
	LinkList m_AddPersonButton[11];//���ڴ���AddOneButton�����Button����ʾ���ݵ���ò�󣬻����������������˵ı��
	
};
#endif