#include<iostream>
#include"Elevator.h"
#include"Person.h"
void Elevator::AddOneButton(int Button,int* PersonList,int PersonNumber)//�����������һ��Ŀ���
{
	if(Button==m_State.GetCurrentfloor())
	{
		for(int i=0;i<PersonNumber;i++)
		{
			if(m_State.GetElevatorPersonNumber()<24)
		{
		AddData(m_State.ElevatorList,PersonList[i]);
		m_State.AddPerson(1);
	    }

		}
	}
	//���˿��б�������
	else
	{
		
	//����Button�������жϵ��ݵķ���
	int ButtonUpflag=0;
	int ButtonDownflag=0;
	for(int i=1;i<m_State.GetCurrentfloor();i++)//����һ�㵽�ò�Ҫ��Ҫͣ
	{
		if(m_Button[i]==ButtonPress)//����Ҫͣ��
			ButtonUpflag=1;
	}
	for(int i=m_State.GetCurrentfloor();i<11;i++)//���ò㵽��ʮ��Ҫ��Ҫͣ
	{
		if(m_Button[i]==ButtonPress)//����Ҫͣ��
			ButtonDownflag=1;
	}

	if(ButtonUpflag==1&&ButtonDownflag==0&&Button<m_State.GetCurrentfloor())//����Ҫͣ��,�Ҽ����Button�ȸõ�������¥��С
	m_Button[Button]=ButtonPress;//��õ���Button���������Ŀ���
	else if(ButtonUpflag==1&&ButtonDownflag==0&&Button>m_State.GetCurrentfloor())//��Ҫͣ�£��Ҽ���Button�ȸõ������ڲ��
		m_TempButton[Button]=ButtonPress;//��õ�����ʱButton���������Ŀ���
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&Button>m_State.GetCurrentfloor())//����Ҫͣ�£��Ҽ���Button�ȸõ������ڲ��
		m_Button[Button]=ButtonPress;////��õ���Button���������Ŀ���
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&Button<m_State.GetCurrentfloor())////����Ҫͣ�£��Ҽ���Button�ȸõ������ڲ�С
		m_TempButton[Button]=ButtonPress;//��õ�����ʱButton���������Ŀ���
	else if(ButtonUpflag==0&&ButtonDownflag==0)
	{
		ChangeButton();
		//m_Button[Button]=ButtonPress;
		
		int ButtonUpflag=0;
	int ButtonDownflag=0;
	for(int i=1;i<m_State.GetCurrentfloor();i++)//����һ�㵽�ò�Ҫ��Ҫͣ
	{
		if(m_Button[i]==ButtonPress)//����Ҫͣ��
			ButtonUpflag=1;
	}
	for(int i=m_State.GetCurrentfloor();i<11;i++)//���ò㵽��ʮ��Ҫ��Ҫͣ
	{
		if(m_Button[i]==ButtonPress)//����Ҫͣ��
			ButtonDownflag=1;
	}
		if(ButtonUpflag==1&&ButtonDownflag==0&&Button<m_State.GetCurrentfloor())//����Ҫͣ��,�Ҽ����Button�ȸõ�������¥��С
	m_Button[Button]=ButtonPress;//��õ���Button���������Ŀ���
	else if(ButtonUpflag==1&&ButtonDownflag==0&&Button>m_State.GetCurrentfloor())//��Ҫͣ�£��Ҽ���Button�ȸõ������ڲ��
		m_TempButton[Button]=ButtonPress;//��õ�����ʱButton���������Ŀ���
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&Button>m_State.GetCurrentfloor())//����Ҫͣ�£��Ҽ���Button�ȸõ������ڲ��
		m_Button[Button]=ButtonPress;////��õ���Button���������Ŀ���
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&Button<m_State.GetCurrentfloor())////����Ҫͣ�£��Ҽ���Button�ȸõ������ڲ�С
		m_TempButton[Button]=ButtonPress;//��õ�����ʱButton���������Ŀ���
	else if(ButtonUpflag==0&&ButtonDownflag==0)
         m_Button[Button]=ButtonPress;
	}
	for(int i=0;i<PersonNumber;i++)
	AddData(m_AddPersonButton[Button],PersonList[i]);
	
}
	
}
void Elevator::GetButton(int* &ButtonArray)
{//��ȡButton����,��ButtonAray����ʱӦע���Ƿ�Ҫ���䴫��Button��
	int i;
	for(i=1;i<11;i++)
		ButtonArray[i]=m_Button[i];
}
void Elevator::ChangeButton()//���¼����Button����Button�����У����е��ݵ���һ���ƶ�
{
	for(int i=1;i<11;i++)
		m_Button[i]=m_TempButton[i];//���¼����Button����Button�����У����е��ݵ���һ���ƶ�
	for(int i=1;i<11;i++)
		m_TempButton[i]=Un_ButtonPress;//����ʱButton���
}
void Elevator::CheckAndChangeButton()//����ElevatorState�еĵ�ǰ�����ı�Button���飬��վ������Un_ButtonPress
{
	m_Button[m_State.GetCurrentfloor()]=Un_ButtonPress;
	//���˸ò����޸�Button����
}
void Elevator::SetButton(int* LeftPerList,Person* PersonArray,int LeftPerListLength)//����Ҫͣ����¥���,ͣ��֮����ͣ�µ���һ��˿�Ŀ��㼯�Ͼ���,�ú�������һ������
{
	//ע��Ҫ���˿͵�Ŀ�����࣬�ֱ�����Button�������ʱButton������
	
	if(PersonArray[LeftPerList[0]].GetCurrentfloor()==m_State.GetCurrentfloor())
	{//�����ѡ���ݾ�����һ��

	int ButtonUpflag=0;
	int ButtonDownflag=0;
	for(int i=1;i<m_State.GetCurrentfloor();i++)//����һ�㵽�ò�Ҫ��Ҫͣ
	{
		if(m_Button[i]==ButtonPress)//����Ҫͣ��
			ButtonUpflag=1;
	}

	for(int i=m_State.GetCurrentfloor();i<11;i++)//���ò㵽��ʮ��Ҫ��Ҫͣ
	{
		if(m_Button[i]==ButtonPress)//����Ҫͣ��
			ButtonDownflag=1;
	}
	    
		///////////////////////////////////
		for(int i=0;i<LeftPerListLength;i++)
		{
			if(ButtonUpflag==1&&ButtonDownflag==0&&PersonArray[LeftPerList[i]].GetAimfloor()<m_State.GetCurrentfloor())//����Ҫͣ��,�Ҽ����Button�ȸõ�������¥��С
	m_Button[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//��õ���Button���������Ŀ���
	else if(ButtonUpflag==1&&ButtonDownflag==0&&PersonArray[LeftPerList[i]].GetAimfloor()>m_State.GetCurrentfloor())//��Ҫͣ�£��Ҽ���Button�ȸõ������ڲ��
		m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//��õ�����ʱButton���������Ŀ���
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&PersonArray[LeftPerList[i]].GetAimfloor()>m_State.GetCurrentfloor())//����Ҫͣ�£��Ҽ���Button�ȸõ������ڲ��
		m_Button[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;////��õ���Button���������Ŀ���
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&PersonArray[LeftPerList[i]].GetAimfloor()<m_State.GetCurrentfloor())////����Ҫͣ�£��Ҽ���Button�ȸõ������ڲ�С
		m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//��õ�����ʱButton���������Ŀ���
	else if(ButtonUpflag==0&&ButtonDownflag==0)
	{
     
	  m_Button[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;
	  //ȫ������Button��
	}
		}
		///////////////////////////////////////
	}
	else
	{

		///////////////////Test//////////////////////////
		for(int i=0;i<LeftPerListLength;i++)
		 m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;
		/*
	int ButtonUpflag=0;
	int ButtonDownflag=0;
	for(int i=1;i<m_State.GetCurrentfloor();i++)//����һ�㵽�ò�Ҫ��Ҫͣ
	{
		if(m_Button[i]==ButtonPress)//����Ҫͣ��
			ButtonUpflag=1;
	}

	for(int i=m_State.GetCurrentfloor();i<11;i++)//���ò㵽��ʮ��Ҫ��Ҫͣ
	{
		if(m_Button[i]==ButtonPress)//����Ҫͣ��
			ButtonDownflag=1;
	}
	if(ButtonUpflag==0&&ButtonDownflag==0)
	{
		 ChangeButton();//����ʱButton��������
	  //���жϷ���
	}
	for(int i=0;i<LeftPerListLength;i++)
	{
		if(ButtonUpflag==1&&ButtonDownflag==0&&PersonArray[LeftPerList[i]].GetAimfloor()<m_State.GetCurrentfloor())//����Ҫͣ��,�Ҽ����Button�ȸõ�������¥��С
	m_Button[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//��õ���Button���������Ŀ���
	else if(ButtonUpflag==1&&ButtonDownflag==0&&PersonArray[LeftPerList[i]].GetAimfloor()>m_State.GetCurrentfloor())//��Ҫͣ�£��Ҽ���Button�ȸõ������ڲ��
		m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//��õ�����ʱButton���������Ŀ���
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&PersonArray[LeftPerList[i]].GetAimfloor()>m_State.GetCurrentfloor())//����Ҫͣ�£��Ҽ���Button�ȸõ������ڲ��
		m_Button[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;////��õ���Button���������Ŀ���
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&PersonArray[LeftPerList[i]].GetAimfloor()<m_State.GetCurrentfloor())////����Ҫͣ�£��Ҽ���Button�ȸõ������ڲ�С
		m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//��õ�����ʱButton���������Ŀ���
	else if(ButtonUpflag==0&&ButtonDownflag==0)
	{
     
	  m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;
	  //ȫ��������ʱButton��
	}
	}*/
	}
}

void Elevator::ChangState(Person* PersonArray)
	//�ı䵱ǰ״̬�����õ�ǰ����,��������,��������״̬������Ϊ���ϵ��ݵ��˵��б����ڻ�ȡ�˿͵�Ŀ�������Ƴ˿�����
{	//��Ϊÿ��һ�㣬���������ܱ仯
	//ע������ı��˵��ݵ�����״̬����Ӧ����ChangButton����,�θı�Ϊ˲��
	//���ݾ�ֹʱ��������һ����ʾ��ֹʱ���ı���StopTime���ݴ��ж�״̬�Ƿ�ı�
	//����һ��������������
	if(m_State.StopTime>0)//˵����ֹʱ�仹δ��
		m_State.DecreaseStopTime();//��С��ֹʱ�䣬״̬���ı�
	else
{
		//��ʱҪ����Button����
		//��Button���������е�Ԫ�ؾ�ΪUn_ButtonPress�ǵ��ݵķ���һ���ı�
		//����Button�������жϵ��ݵķ���
	int ButtonDownflag=0;
	for(int i=1;i<m_State.GetCurrentfloor();i++)//����һ�㵽�ò�Ҫ��Ҫͣ
	{
		if(m_Button[i]==ButtonPress)//����Ҫͣ��
			ButtonDownflag=1;
	}
	int ButtonUpflag=0;
	for(int i=m_State.GetCurrentfloor();i<11;i++)//���ò㵽��10��Ҫ��Ҫͣ
	{
		if(m_Button[i]==ButtonPress)//����Ҫͣ�£����ʾ���������˶�
			ButtonUpflag=1;
	}
	//���ButtonDownflag==1��ʾ��������
	//���ButtonUpflag==1��ʾ��������
	if(ButtonDownflag==1&&ButtonUpflag==0)
	{//��ʾ�����������˶�
	m_State.SetDeractionState(DownState);
	//���õ��ݷ���״̬
	//��ʱ���ݵķ�������
	 
	 
     if(m_Button[m_State.GetCurrentfloor()-1]==ButtonPress)
	       {
	//�����һ���ӳButton������ΪButtonPress
	//��ʾ����һ����Ҫͣ��
	
    LinkList p;//ɸѡ��Ҫ�µ��ݵ���
	for(p=m_State.ElevatorList->next;p!=NULL;)
	{ if(PersonArray[p->data].GetAimfloor()==m_State.GetCurrentfloor()-1) 
	           {//��ʾ�ó˿�Ŀ��㼴Ϊ��һ��
				   LinkList q=p->next;
			 m_State.DestroyPerson(1); //����������������1
			  PersonArray[p->data].SetCurrentfloor();//�˵�Ŀ���󣬸ı���״̬
			 PersonArray[p->data].SetInWorkState();//��������빤��״̬
			 DeleteData(m_State.ElevatorList,p->data);//�ӵ������б���ɾ���ó˿�
			   p=q;
		        }
		else
		{
			p=p->next;
		}
	}
		for(p=m_AddPersonButton[m_State.GetCurrentfloor()-1]->next;
		p!=NULL;p=p->next)
	{
		if(PersonArray[p->data].GetPatientTime()>5&&m_State.GetElevatorPersonNumber()<24)//�������һ��ʱ������ʱ�仹δ��
		{
			m_State.AddPerson(1);//������м������
			AddData(m_State.ElevatorList,p->data);
			PersonArray[p->data].m_PatientTime=1000;//��ʾ�����Ѿ�������ʱ����
		}
		else//�������ʱ�䵽��
		{
			PersonArray[p->data].SetCurrentfloor();
			PersonArray[p->data].SetInWorkState();//��ʾ����¥�ݣ�������
		}
	}


	 m_Button[m_State.GetCurrentfloor()-1]=Un_ButtonPress;//�ı���ݵ�Button����
	 m_TempButton[m_State.GetCurrentfloor()-1]=Un_ButtonPress;
	 //��������Ϊͣ��״̬
	 //��ʼ���ȴ�ʱ��15s
		m_State.InitStopTime();
	 }
	 //�ı�������ڲ�,��Ϊ��ǰ����-1
	 m_State.SetCurrentfloor(m_State.GetCurrentfloor()-1);
	 m_State.CheckStopState();
	}
	else if(ButtonDownflag==0&&ButtonUpflag==1)
	{//��ʾ���������˶�
		m_State.SetDeractionState(UpState);
		 
	 if(m_Button[m_State.GetCurrentfloor()+1]==ButtonPress)
	 {
		
    LinkList p;//ɸѡ��Ҫ�µ��ݵ���
	for(p=m_State.ElevatorList->next;p!=NULL;)
		{if(PersonArray[p->data].GetAimfloor()==m_State.GetCurrentfloor()+1) 
	    {//��ʾ�ó˿�Ŀ��㼴Ϊ��һ��
			 LinkList q=p->next;
			 m_State.DestroyPerson(1); //����������������1
			 PersonArray[p->data].SetCurrentfloor();//�˵�Ŀ���󣬸ı���״̬
			 PersonArray[p->data].SetInWorkState();//��������빤��״̬
			 DeleteData(m_State.ElevatorList,p->data);//�ӵ������б���ɾ���ó˿�
			 p=q;
		}
		else
		{
			p=p->next;
		}
	 }
	 

		for(p=m_AddPersonButton[m_State.GetCurrentfloor()+1]->next;
		p!=NULL;p=p->next)
	{
		if(PersonArray[p->data].GetPatientTime()>5&&m_State.GetElevatorPersonNumber()<24)//�������һ��ʱ������ʱ�仹δ��
		{
			m_State.AddPerson(1);//������м������
			AddData(m_State.ElevatorList,p->data);
			PersonArray[p->data].m_PatientTime=1000;//��ʾ�����Ѿ�������ʱ����
		}
		else//�������ʱ�䵽��
		{
			PersonArray[p->data].SetCurrentfloor();
			PersonArray[p->data].SetInWorkState();//��ʾ����¥�ݣ�������
		}
	}
	 m_Button[m_State.GetCurrentfloor()+1]=Un_ButtonPress;//�ı���ݵ�Button����
	 m_TempButton[m_State.GetCurrentfloor()+1]=Un_ButtonPress;
	 //��������Ϊͣ��״̬
	 //��ʼ���ȴ�ʱ��15s
		m_State.InitStopTime();
	 }
	 //�ı�������ڲ�,��Ϊ��ǰ����+1
	 m_State.SetCurrentfloor(m_State.GetCurrentfloor()+1);
	 m_State.CheckStopState();
	}
	else if(ButtonDownflag==0&&ButtonUpflag==0)
	{//��ʾ��ʱ��������ɹ�����������һ������
		
		ChangeButton();//����ʱButton����Button��
		//��Ҫ����״̬�ı�
		/////////////Test//////////////
		m_Button[m_State.GetCurrentfloor()]=Un_ButtonPress;
		//m_State.SetDeractionState(StopState);//����������ΪStopState״̬
		int Stateflag=0;
		for(int i=1;i<11;i++)
		{//����г˿�ѡ��
			if(m_Button[i]==ButtonPress)
				Stateflag=1;
		}
	if(m_State.GetDrectionState()==UpState&&Stateflag)
	{//˵���õ��ݸղŵ�״̬Ϊ����״̬������Ҫ�ı���״̬
			m_State.SetDeractionState(DownState);
			//����ĳ����µ�״̬
			//��ʱ�������һ�����޸ĵ��ݵ�״̬
			
     if(m_Button[m_State.GetCurrentfloor()-1]==ButtonPress)
	 {
	//�����һ���ӳButton������ΪButtonPress
	//��ʾ����һ����Ҫͣ��
    LinkList p;//ɸѡ��Ҫ�µ��ݵ���
	for(p=m_State.ElevatorList->next;p!=NULL;)
		{if(PersonArray[p->data].GetAimfloor()==m_State.GetCurrentfloor()-1) 
	    {//��ʾ�ó˿�Ŀ��㼴Ϊ��һ��
			LinkList q=p->next;
			 m_State.DestroyPerson(1); //����������������1
			  PersonArray[p->data].SetCurrentfloor();//�˵�Ŀ���󣬸ı���״̬
			 PersonArray[p->data].SetInWorkState();//��������빤��״̬
			 DeleteData(m_State.ElevatorList,p->data);//�ӵ������б���ɾ���ó˿�
			p=q;
		}
		else
		{
			p=p->next;
		}
	}


		for(p=m_AddPersonButton[m_State.GetCurrentfloor()-1]->next;
		p!=NULL;p=p->next)
	{
		if(PersonArray[p->data].GetPatientTime()>5&&m_State.GetElevatorPersonNumber()<24)//�������һ��ʱ������ʱ�仹δ��
		{
			m_State.AddPerson(1);//������м������
			AddData(m_State.ElevatorList,p->data);
			PersonArray[p->data].m_PatientTime=1000;//��ʾ�����Ѿ�������ʱ����
		}
		else//�������ʱ�䵽��
		{
			PersonArray[p->data].SetCurrentfloor();
			PersonArray[p->data].SetInWorkState();//��ʾ����¥�ݣ�������
		}
	}
	 m_Button[m_State.GetCurrentfloor()-1]=Un_ButtonPress;//�ı���ݵ�Button����
	  m_TempButton[m_State.GetCurrentfloor()-1]=Un_ButtonPress;
	 //��������Ϊͣ��״̬
	 //��ʼ���ȴ�ʱ��15s
		m_State.InitStopTime();
		}
	 if(m_State.GetCurrentfloor()!=1)
	 m_State.SetCurrentfloor(m_State.GetCurrentfloor()-1);
	        //¥���һ
	}
	else if(m_State.GetDrectionState()==DownState&&Stateflag)
	{
      
     m_State.SetDeractionState(UpState);
		
	 if(m_Button[m_State.GetCurrentfloor()+1]==ButtonPress)
	 {//�����һ���Button״̬ΪButtonPress
		  
    LinkList p;//ɸѡ��Ҫ�µ��ݵ���
	for(p=m_State.ElevatorList->next;p!=NULL;)
		{if(PersonArray[p->data].GetAimfloor()==m_State.GetCurrentfloor()+1) 
	    {//��ʾ�ó˿�Ŀ��㼴Ϊ��һ��
			LinkList q=p->next;
			 m_State.DestroyPerson(1); //����������������1
			  PersonArray[p->data].SetCurrentfloor();//�˵�Ŀ���󣬸ı���״̬
			 PersonArray[p->data].SetInWorkState();//��������빤��״̬
			 DeleteData(m_State.ElevatorList,p->data);//�ӵ������б���ɾ���ó˿�
			p=q;
		}
		else
		{
			p=p->next;
		}
	}

		for(p=m_AddPersonButton[m_State.GetCurrentfloor()+1]->next;
		p!=NULL;p=p->next)
	{
		if(PersonArray[p->data].GetPatientTime()>5&&m_State.GetElevatorPersonNumber()<24)//�������һ��ʱ������ʱ�仹δ��
		{
			m_State.AddPerson(1);//������м������
			AddData(m_State.ElevatorList,p->data);
			PersonArray[p->data].m_PatientTime=1000;//��ʾ�����Ѿ�������ʱ����
		}
		else//�������ʱ�䵽��
		{
			PersonArray[p->data].SetCurrentfloor();
			PersonArray[p->data].SetInWorkState();//��ʾ����¥�ݣ�������
		}
	}
	 
		 m_TempButton[m_State.GetCurrentfloor()+1]=Un_ButtonPress;
		 m_Button[m_State.GetCurrentfloor()+1]=Un_ButtonPress;//�ı���ݵ�Button����
	 //��������Ϊͣ��״̬
	 //��ʼ���ȴ�ʱ��15s
		m_State.InitStopTime();
	 }
	  //�ı�������ڲ�,��Ϊ��ǰ����+1
	 if(m_State.GetCurrentfloor()!=10)
	 m_State.SetCurrentfloor(m_State.GetCurrentfloor()+1);
	}
	}
}

}
