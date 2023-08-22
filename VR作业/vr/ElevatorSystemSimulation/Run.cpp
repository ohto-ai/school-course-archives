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
Buiding LXN_Building;//��ʼ��������¥����Ϊ�ļ�����
Person LXN_Person[PersonNumberMax];//��ʼ����ٸ��ˣ���ʱ�����˾������ڴ�¥��,��һ��Ԫ�ز���
int PersonNumberFirstLimit=1;
int PersonNumberLastLimit=1;
int AddPersonNumber;
void InitFloors();
void GetAllElevatorNumber();
void Door();
void Run()//�ú����м���������¥����ʼ����¥����ʱ¥�㣬����Ҳ������ʼ��
{
	int i,j;

	Door();//��ʼ���˽����¥�������������
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
	LXN_Building.m_floor[1].SetWaitingPerNumber(AddPersonNumber);//ÿ��һ��ʱ�䣬���˽����¥�����Ҷ��ǽ����һ�㣬�Ҿ��ȴ�
	LXN_Building.m_floor[1].SetAllPerNumber(AddPersonNumber);//����ò���������
	if(AddPersonNumber!=0)
	for(i=PersonNumberFirstLimit;i<PersonNumberLastLimit;i++)
	{
		LXN_Building.m_floor[1].AddAllPersonList(i);//��ʱi��ΪҪ�����¥���˵ı�ţ��Ҷ��ǽ����һ��
		LXN_Building.m_floor[1].AddWorkFinishedList(i);//��Ϊ�ȴ�״̬�����빤���ո���ɵ����б���
		LXN_Building.m_floor[1].AddWaitingPerList(i);
		LXN_Person[i].SetInBuiding();//��ʾ���˽����¥��
		LXN_Person[i].InitCurrentfloor();//��ʾһ��ʼ���˴��ڵ�һ��
	}
	//�ڴ�Ҫ��ÿ��¥����˶����л������Ҳ���л
	
	for( i=1;i<11;i++)//��ʾʮ�����ݵı��
	{
		int WaitingPersonSize;
		WaitingPersonSize=LXN_Building.m_floor[i].GetWorkFinishedNumber();//��ȡ�ò�ĵȴ�����,Ӧ�û�ȡ��������˵�����
		int* FloorButton=new int[WaitingPersonSize];//����ò�˿͵�Ŀ��㼯��
		int* WaitingPersonList=new int[WaitingPersonSize];//����˿��б�
		LXN_Building.m_floor[i].GetWorkFinishedList(WaitingPersonList);
		//��ȡ�ڸò��г˿͵��б�
		
		
		for(j=0;j<WaitingPersonSize;j++)//��ȡ���б��г˿͵�Ŀ��㼯��
			FloorButton[j]=LXN_Person[WaitingPersonList[j]].GetAimfloor();
		int* ElevatorNumberList=new int[2];//��������洢ѡ���ĵ��ݺ�
		LXN_Building.m_floor[i].GetFloorButton(FloorButton,ElevatorNumberList,LXN_Building.m_Elevator,LXN_Person);//ѡ��Ҫ�ڸò�ͣ�µĵ��ݺ�,����ElevatorNumberList��
		//ElevatorNumberList[0]�еĵ������ظò����ϵĳ˿ͣ�ElevatorNumberList[1]�еĵ������ظò����µĳ˿�
	//ע����û�з���ֵ
	
	
	//LXN_Building.m_floor[i].InitDeletePersonList(DeletePersonList);//���򳬹�����ʱ���Ҫ��¥�ݵ��˵��б����ò������
	/*for(k=0;k<DeleteListSize;k++)
	{
		//�Ӹò�ĵȴ����б���ɾ���򳬹�����ʱ���Ҫ��¥�ݵ��ˣ����б�Ϊ���ܵ��ݵ����б�
		//LXN_Building.m_floor[i].DeleteWaitingPerList(DeletePersonList[k]);�þ�ŵ��������ڿ���ʱ��
		LXN_Person[DeletePersonList[k]].SetCurrentfloor();//��ʾ�����Ѿ�ѡ����¥�ݣ����Ѿ�����
		//LXN_Person[DeletePersonList[k]].GetStairseWorkStateTime();�ú����ɷ��ظó˿���һ�ΰ����ݰ�ť��ʱ����
	}
	*/
	////////////////
	//ע��������Ҫ���г˿͵�����ʱ��ļ���
	//��Ҫ����ʱ��ģ�⣬��ģ����ѡ��˿͵ĺ����н���
	///////////////

	//�˴�Ӧ�ý�LeftPersonList���࣬�ֱ����������
	int* Up=new int[LXN_Building.m_floor[i].GetWorkFinishedNumber()];//���ڴ洢Ҫ��¥�ĳ˿͵�Ŀ�꼯��
	int* Down=new int[LXN_Building.m_floor[i].GetWorkFinishedNumber()];//���ڴ洢Ҫ��¥�ĳ˿͵�Ŀ�꼯��
	int UpCount=0;
	int DownCount=0;
	for(int j=0;j<LXN_Building.m_floor[i].GetWorkFinishedNumber();j++)
	{//�ո���ɹ�������
		if(LXN_Person[WaitingPersonList[j]].GetAimfloor()>i)//����ó˿�Ŀ�����ڸò�
			Up[UpCount++]=WaitingPersonList[j];//���ó˿ͱ�Ŵ���Up������
		else if(LXN_Person[WaitingPersonList[j]].GetAimfloor()<i)//����ó˿�Ŀ���С�ڸò�
			Down[DownCount++]=WaitingPersonList[j];//���ó˿ͱ�Ŵ���Down������
	}
	if(ElevatorNumberList[0]!=-1)
	{
LXN_Building.m_Elevator[ElevatorNumberList[0]].AddOneButton(i,Up,UpCount);//֪ͨ��ѡ��ĵ��ݣ�ʹ�����ڸò�ͣ��
//Ӧ����˿��б�
LXN_Building.m_Elevator[ElevatorNumberList[0]].SetButton(Up,LXN_Person,
					UpCount);//���ò�Up�˿͵�Ŀ��㼯�ϵ�����ѡ�����У��ı���ݵİ�ť����,Ӧ����Up
	}
	if(ElevatorNumberList[1]!=-1)
	{
LXN_Building.m_Elevator[ElevatorNumberList[1]].AddOneButton(i,Down,DownCount);//֪ͨ��ѡ��ĵ��ݣ�ʹ�����ڸò�ͣ��
//Ӧ����˿��б�
LXN_Building.m_Elevator[ElevatorNumberList[1]].SetButton(Down,LXN_Person,
					DownCount);		
	}
	//���ò�Down�˿͵�Ŀ��㼯�ϵ�����ѡ�����У��ı���ݵİ�ť����,Ӧ����Down
    //��ʱ�Ѿ����˿ͷ��ಢ�ң�����ͬ��Ŀ��㼯�ϣ������˲�ͬ�ĵ�����
    //ElevatorNumberList[0]�еĵ������ظò����ϵĳ˿ͣ�ElevatorNumberList[1]�еĵ������ظò����µĳ˿�
	//����֪����Ҫ�ߵ�ʲô��֮�󣬱������ʱ��ģ��ı���״̬

	/*for(k=0;k<LXN_Building.m_floor[i].GetLeftPersonNumber();k++)
	{
		//LXN_Building.m_floor[i].DeleteWaitingPerList(LeftPersonList[k]);//�Ӹò�ȴ��˿��б���ɾ�����ϵ��ݵĳ˿�,�þ�������棬���ڸı�¥���״̬
		LXN_Person[LeftPersonList[k]].SetCurrentfloor();//��ʾ�����Ѿ��ϵ��ݣ����ҵ�����Ŀ��㣨ע�����涨��һ�ϵ��������޸��˵�״̬��ʹ�����Ŀ��㣩
		//LXN_Person[LeftPersonList[k]].GetElevatorWorkStateTime(FloorButton);//�ú����ɷ��������ݵ�����һ�ΰ����ݰ�ť��ʱ����
		//��������Sleep()��ʱ��ģ��
	}*///�ϵ���֮��Ӧ�õ�����״̬�ı�ʱ�ڽ��иı�
	 //�������������¥������֮��Ĺ�ϵ�����ͽ�����
	//��ʼ��������״̬�ĸı䣬��Sleep(500);��״̬�޸ķ���һ��ͬһ��while������״̬�ı仯
	//�������WorkFinishedList�˿��б�
	DestroyData(LXN_Building.m_floor[i].m_WorkFinishedList);
			
	LXN_Building.m_floor[i].GetDeleteWaitingPersonListLength(LXN_Person);
	//����¥�������ڵȴ����˼�ȥ5s������ʱ�䣬�������ʱ��С��0���˵��б�����DeletePersonList�����ܼ�������ϵ��ݵ��ˣ����ϵ��ݵ���Ӧ���ڵ���״̬�ı�ʱ����
	delete [] FloorButton;//�ͷ��ڴ�
	delete [] WaitingPersonList;
	delete [] ElevatorNumberList;
	delete [] Up;
	delete [] Down;
	
		//ʣ�µ�����¥���״̬����ֻ��Ҫ���ݹ���ʱ��仯����
	}

		//�˴�����״̬�ı亯��
	
		//TimeStateChange();
		//�ú���������5��Ϊһ�����ڣ�5��֮���˳�while
		//�ú������OpenGL���ɻ��Ƴ�ͼ�ν���
		//�ú������Լ����Ƿ�ı䵱ǰ���ݵ�״̬�������Ƿ񵽴���һ�㣬��Ϊ����ͣ��Ϊ15s������¥Ϊ5s
		//���ԣ�����ѭ������ʱ�����еĵ��ݶ�������ĳһ���λ�ã����������ĳ�����м�
		//���Ƿ�ȴ����ܵ�����״̬���Ƶģ�����Ӧ�ý��˵�����ʱ������ݵ�״̬�����
		//Sleep(500);
	       GetTimeChangeButton();
			for(i=0;i<10;i++)//�øı�ĸı䣬û��ļ�������ԭ״
			{
				    //�ı���ݵ�״̬�����ڲ��������⣬��Ȼ��������������������Ǹú����ڲ��ɽ���ɸѡ
				    //���ϵ��ݵ���Ӧ���ڵ���״̬�ı�ʱ����
				    LXN_Building.m_Elevator[i].ChangState(LXN_Person);
			}
			for(i=1;i<11;i++)
			{
				//�ı�¥��״̬,����LXN_Person���Ը�������״̬
					LXN_Building.m_floor[i].SetElevatorAndPersonNumber(LXN_Building.m_Elevator,LXN_Person);
					
			}
			//��ʱ���ݣ�¥���״̬���Ѹ�	
			GetAllElevatorNumber();
			
		//��Ҫ��DeletePersonList,LeftPersonList��Ϊbuidingfloors����ĳ�Ա
		//��Ҫ��Person�����������ʱ���Ա���ó�Ա��ʾ��һ�ΰ���ť��ʱ�������ֱ�Ϊ�����ݺ���¥�ݵļ����
}
void Door()//�������������¥�����������ҳ�ʼ��Person��������
{
	//AddPersonNumber=rand()%50;
	////////Test////////////////
	//srand((unsigned)time(NULL));
	int Number=rand()%5;
	
	////////////////////
	if(PersonNumberLastLimit+Number<=PersonNumberMax)//ע���������ܳ������
	{
		AddPersonNumber=Number;
	PersonNumberFirstLimit=PersonNumberLastLimit;
	PersonNumberLastLimit+=AddPersonNumber;
	LXN_Building.ChangeTotalpeopleNumber(AddPersonNumber);//���Ӵ�¥�������
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