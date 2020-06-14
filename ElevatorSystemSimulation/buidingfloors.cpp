#include<iostream>
#include"Elevator.h"
#include"buidingfloors.h"
#include"Person.h"
void buidingfloors::GetWaitingPersonList(int* &WaitingList)
{//�ɵõ�����ĵȴ��б�
	int i;
	LinkList p;
	for(i=0,p=m_WaitingPersonList->next;p!=NULL;p=p->next,i++)
		WaitingList[i]=p->data;
}

void buidingfloors::AddWaitingPerList(int person)
{//��Person�ı�ż���ȴ��б�������
	AddData(m_WaitingPersonList,person);
}
void buidingfloors::AddAllPersonList(int person)
{//�����ΪPerson���˼���¥�������б���
	AddData(m_AllPersonList,person);
}

void buidingfloors::DeleteWaitingPerList(int person)
{//�����ΪPerson���˴��б�������ɾ��
	DeleteData(m_WaitingPersonList,person);
}
void buidingfloors::SetWaitingPerNumber(int AddPersonNumber)
{//�ڴ˿�����ӻ�ɾ���ȴ�����������һ��ʹ��
	m_WaitingPerNumber+=AddPersonNumber;
}
void buidingfloors::SetAllPerNumber(int AddPersonNumber)
{
	m_AllPerNumber+=AddPersonNumber;
}
int buidingfloors::GetAllPerNumber()
{//��ȡ����ȫ������
	return m_AllPerNumber;
}

int buidingfloors::GetWaitingPerNumber()
{//��ȡ����ȴ�����
	return m_WaitingPerNumber;
}
void  buidingfloors::GetDeleteWaitingPersonListLength(Person* PersonArray)
//�ú�����ȡ�ò�ĳ˿��б����ڻ�ȡ����ʱ�䣬
{//�����ڸú������𲽼��ٳ˿͵�����ʱ�䣨ʮ����Ҫ��
//�𲽼��ٹ���ʱ�䣬��ȡ����ʱ����ɵ��ˣ��ı���״̬���ı�¥���״̬
	LinkList p;
	for(p=m_AllPersonList->next;p!=NULL;p=p->next)
	{
		if(PersonArray[p->data].GetState()==OutWork)//���û���ڹ���
		PersonArray[p->data].m_PatientTime-=5;
		else//����ڹ���
		{
		    PersonArray[p->data].m_WorkTime-=5;//���ٹ���ʱ��
			if(PersonArray[p->data].m_WorkTime<=0)
			{//�ı�״̬�����˼�����ɹ����б���
				PersonArray[p->data].SetOutWorkState();//��ʾ���ڷǹ���״̬
				AddWorkFinishedList(p->data);//����ò����ɹ����б���
				PersonArray[p->data].InitAimFloor();
			}
		}
	}

}

void buidingfloors::GetFloorButton(int *FloorButton,int* &ElevatorNumber,Elevator* EleVatorArray,Person* PersonArray)
{//�ڴ˳�ʼ���㰴ť�����������¼�������Ϊ�ò�˿͵�Ŀ��㼯�ϣ��ڶ�������Ϊ��ѡ��ĵ��ݺţ����ڴ�����Ӧ�ĵ���Button���飬�Կ��Ƶ���
//�ú�������ѡ����ݣ�ѡ��һ̨����̨���ݣ���Ϊ������������
	int* Up=new int[GetWorkFinishedNumber()];//���ڴ洢Ҫ��¥�ĳ˿͵�Ŀ�꼯��
	int* Down=new int[GetWorkFinishedNumber()];//���ڴ洢Ҫ��¥�ĳ˿͵�Ŀ�꼯��
	int DownCount=0;
	int UpCount=0;
	LinkList p;
	for(p=m_WorkFinishedList->next;p!=NULL;p=p->next)
	{
		if(PersonArray[p->data].GetAimfloor()>m_CurrentFloor)//����ó˿�Ŀ�����ڸò�
			Up[UpCount++]=p->data;//���ó˿ͱ�Ŵ���Up������
		else if(PersonArray[p->data].GetAimfloor()<m_CurrentFloor)//����ó˿�Ŀ���С�ڸò�
			Down[DownCount++]=p->data;//���ó˿ͱ�Ŵ���Down������
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
					flagCurrentState=1;//��ʾ�ò������ϵĵ���
					SuitableUpElevatorNumber[ElevatorCount++]=i;
			}
		}
		if(flagCurrentState==1)//��������е���
			ElevatorNumber[0]=SuitableUpElevatorNumber[0];///��ֱ��ѡһ̨
		else{
			////////////////////Ӧ���޸�ѡ���ݲ���
			/////////////////////////////////
			

		for(int i=0;i<10;i++)
		{
			if(EleVatorArray[i].m_State.GetCurrentfloor()<m_CurrentFloor&&(EleVatorArray[i].m_State.GetDrectionState()==UpState||EleVatorArray[i].m_State.GetDrectionState()==StopState))
			{
					flagDownUpState=1;//��ʾ���ڸò��·��������ϻ�ֹ�ĵ���
					SuitableUpElevatorNumber[ElevatorCount++]=i;
			}
		}
		if(flagDownUpState==1)//�����ڸò��·��������ϵĵ���
		{
			//�ڴ�ѡ��һ̨���ݣ�������ѡ��
			int i;
			int Max=0;
			int MaxNumber=0;
			for(i=0;i<ElevatorCount;i++)
			{
				if(EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor()>Max)
				{//���ڲ���ߵĵ��ݣ���ΪUp���ϳ˿�Ҫѡ���ĵ���
						Max=EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor();
				        MaxNumber=SuitableUpElevatorNumber[i];
				}  
			}
			ElevatorNumber[0]=MaxNumber;//ѡ�����ݸ�����ElevatorNumber

		}
		else if(flagDownUpState!=1)
		{
			for(int i=0;i<10;i++)
			{
			if(EleVatorArray[i].m_State.GetCurrentfloor()<m_CurrentFloor&&EleVatorArray[i].m_State.GetDrectionState()==DownState)
			{
				flagDownDownState=1;//��ʾ���ڸò��·��������µĵ���
				SuitableUpElevatorNumber[ElevatorCount++]=i;
			}
			}
			if(flagDownDownState==1)//�����ڸò��·��������µĵ���
			{
				//�ڴ�ѡ��һ̨���ݣ�������ѡ��
				int i;
				int Min=11;
				int MinNumber=0;
				for(i=0;i<ElevatorCount;i++)
			{
				if(EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor()<Min)
				{//���ڲ���͵ĵ��ݣ���ΪUp���ϳ˿�Ҫѡ���ĵ���
						Min=EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor();
				        MinNumber=SuitableUpElevatorNumber[i];
				}  
			}
			ElevatorNumber[0]=MinNumber;//ѡ�����ݸ�����ElevatorNumber
			}
			else if(flagDownDownState!=1)
			{
				for(int i=0;i<10;i++)
				{
					if(EleVatorArray[i].m_State.GetCurrentfloor()>m_CurrentFloor&&(EleVatorArray[i].m_State.GetDrectionState()==DownState||EleVatorArray[i].m_State.GetDrectionState()==StopState))
					{
							flagUpDownState=1;//��ʾ���ڸò��Ϸ������»�ֹ�ĵ���
							SuitableUpElevatorNumber[ElevatorCount++]=i;
					}
				}
				if(flagUpDownState==1)//�����ڸò��Ϸ��������»�ֹ�ĵ���
				{
					//�ڴ�ѡ��һ̨���ݣ�������ѡ��
				int i;
				int Min=11;
				int MinNumber=0;
				for(i=0;i<ElevatorCount;i++)
			    {
				if(EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor()<Min)
				{//���ڲ���͵ĵ��ݣ���ΪUp���ϳ˿�Ҫѡ���ĵ���
						Min=EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor();
				        MinNumber=SuitableUpElevatorNumber[i];
				}  
			    }
			    ElevatorNumber[0]=MinNumber;//ѡ�����ݸ�����ElevatorNumber

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
				{//���ڲ���ߵĵ��ݣ���ΪUp���ϳ˿�Ҫѡ���ĵ���
						Max=EleVatorArray[SuitableUpElevatorNumber[i]].m_State.GetCurrentfloor();
				        MaxNumber=SuitableUpElevatorNumber[i];
				}  
			}
			ElevatorNumber[0]=MaxNumber;//ѡ�����ݸ�����ElevatorNumber
					//�ڴ�ѡ��һ̨���ݣ�������ѡ��
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
					flagCurrentState=1;//��ʾ�ò������µĵ���
					SuitableUpElevatorNumber[ElevatorCount++]=i;
			}
		}
		if(flagCurrentState==1)//��������е���
			ElevatorNumber[1]=SuitableUpElevatorNumber[0];///��ֱ��ѡһ̨
		else{

		for(int i=0;i<10;i++)
		{
			if(EleVatorArray[i].m_State.GetCurrentfloor()>m_CurrentFloor&&(EleVatorArray[i].m_State.GetDrectionState()==DownState||EleVatorArray[i].m_State.GetDrectionState()==StopState))
			{
					flagUpDownState=1;//��ʾ���ڸò��Ϸ������»�ֹ�ĵ���
					SuitableDownElevatorNumber[ElevatorCount++]=i;
			}
		}
		if(flagUpDownState==1)//�����ڸò��Ϸ������»�ֹ�ĵ���
		{
			    int i;
				int Min=11;
				int MinNumber=0;
				for(i=0;i<ElevatorCount;i++)
			    {
				if(EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor()<Min)
				{//���ڲ���͵ĵ��ݣ���ΪDown���ϳ˿�Ҫѡ���ĵ���
						Min=EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor();
				        MinNumber=SuitableDownElevatorNumber[i];
				}  
			    }
			    ElevatorNumber[1]=MinNumber;//ѡ�����ݸ�����ElevatorNumber
			//�ڴ�ѡ��һ̨���ݣ�������ѡ��
		}
		else if(flagUpDownState!=1)
		{
			for(int i=0;i<10;i++)
			{
				if(EleVatorArray[i].m_State.GetCurrentfloor()>m_CurrentFloor&&EleVatorArray[i].m_State.GetDrectionState()==UpState)
			{
					flagUpUpState=1;//��ʾ���ڸò��Ϸ������ϵĵ���
					SuitableDownElevatorNumber[ElevatorCount++]=i;
			}
			}
			if(flagUpUpState==1)//��ʾ�����ڸò��Ϸ������ϵĵ���
			{
			int i;
			int Max=0;
			int MaxNumber=0;
			for(i=0;i<ElevatorCount;i++)
			{
				if(EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor()>Max)
				{//���ڲ���ߵĵ��ݣ���ΪDown���ϳ˿�Ҫѡ���ĵ���
						Max=EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor();
				        MaxNumber=SuitableDownElevatorNumber[i];
				}  
			}
			ElevatorNumber[1]=MaxNumber;//ѡ�����ݸ�����ElevatorNumber
				//�ڴ�ѡ��һ̨���ݣ�������ѡ��
			}
			else if(flagUpUpState!=1)
			{
				for(int i=0;i<10;i++)
				{
					if(EleVatorArray[i].m_State.GetCurrentfloor()<m_CurrentFloor&&(EleVatorArray[i].m_State.GetDrectionState()==UpState||EleVatorArray[i].m_State.GetDrectionState()==StopState))
			    {
					flagDownUpState=1;//��ʾ���ڸò��·������ϻ�ֹ�ĵ���
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
				{//���ڲ���ߵĵ��ݣ���ΪDown���ϳ˿�Ҫѡ���ĵ���
						Max=EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor();
				        MaxNumber=SuitableDownElevatorNumber[i];
				}  
			}
			ElevatorNumber[1]=MaxNumber;//ѡ�����ݸ�����ElevatorNumber
					//�ڴ�ѡ��һ̨���ݣ�������ѡ��
				}
				else if(flagDownUpState!=1)
				{
					for(int i=0;i<10;i++)
					{
						if(EleVatorArray[i].m_State.GetCurrentfloor()<m_CurrentFloor&&EleVatorArray[i].m_State.GetDrectionState()==DownState)
			        {
					//��ʾ���ڸò��·������µĵ���
					SuitableDownElevatorNumber[ElevatorCount++]=i;
			        }
					}
				int i;
				int Min=11;
				int MinNumber=0;
				for(i=0;i<ElevatorCount;i++)
			    {
				if(EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor()<Min)
				{//���ڲ���͵ĵ��ݣ���ΪDown���ϳ˿�Ҫѡ���ĵ���
						Min=EleVatorArray[SuitableDownElevatorNumber[i]].m_State.GetCurrentfloor();
				        MinNumber=SuitableDownElevatorNumber[i];
				}  
			    }
			    ElevatorNumber[1]=MinNumber;//ѡ�����ݸ�����ElevatorNumber
					//�ڴ�ѡ��һ̨���ݣ�������ѡ��
				}
			}
		}
		}
		if(UpCount==0)//�����������
			ElevatorNumber[0]=-1;//����-1
		if(DownCount==0)//�����������
			ElevatorNumber[1]=-1;//����-1
		delete [] Up;//�ͷ��ڴ�
		delete [] Down;//�ͷ��ڴ�
}
int buidingfloors::GetWorkFinishedNumber()//��ȡ�����ո���ɵ��˵�����
{
	int i=0;
	LinkList p;
	for(p=m_WorkFinishedList->next;p!=NULL;p=p->next)
		i++;
	return i;
}
void buidingfloors::AddWorkList(int Person)//�����ΪPerson���˼��룬�����б���
{
	AddData(m_WorkList,Person);
}

void buidingfloors::GetWorkFinishedList(int* &WorkFinishedList)//���Ի�øո���ɹ������ˣ����ı���״̬
{
	LinkList p;
	int i=0;
	for(p=m_WorkFinishedList->next;p!=NULL;p=p->next,i++)
		WorkFinishedList[i]=p->data;
}
void buidingfloors::AddWorkFinishedList(int Person)//�����ΪPerson���˼��빤������б��У�����һ��ʹ�ã����ı���״̬
{
	AddData(m_WorkFinishedList,Person);
}
void buidingfloors::SetCurrentFloor(int FloorNumber)//��ʼ���ò���
{
	m_CurrentFloor=FloorNumber;
}
void  buidingfloors::SetElevatorAndPersonNumber(Elevator* ElevatorArray,Person* PersonArray)
{//�����������¸ò������״̬
	//�ֽ������б��ÿ�
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
		{//ѡ�����ڵ���ĵ���
			ElevatorCount++;
		}
	}
	m_ElevatorNumber=ElevatorCount;//ѡ��������
	for(int i=1;PersonArray[i].m_InBuiding!=0;i++)
	{
		if(PersonArray[i].GetCurrentfloor()==m_CurrentFloor)//������˴��ڵ�ǰ��
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
int  buidingfloors::GetElevatorNumber()//��ȡ����ĵ����������Թ���ʾ
{
	return m_ElevatorNumber;
}