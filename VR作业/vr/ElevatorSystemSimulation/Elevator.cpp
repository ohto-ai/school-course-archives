#include<iostream>
#include"Elevator.h"
#include"Person.h"
void Elevator::AddOneButton(int Button,int* PersonList,int PersonNumber)//用于用于添加一个目标层
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
	//将乘客列表传入其中
	else
	{
		
	//根据Button数组先判断电梯的方向
	int ButtonUpflag=0;
	int ButtonDownflag=0;
	for(int i=1;i<m_State.GetCurrentfloor();i++)//检查第一层到该层要不要停
	{
		if(m_Button[i]==ButtonPress)//若需要停下
			ButtonUpflag=1;
	}
	for(int i=m_State.GetCurrentfloor();i<11;i++)//检查该层到第十层要不要停
	{
		if(m_Button[i]==ButtonPress)//若需要停下
			ButtonDownflag=1;
	}

	if(ButtonUpflag==1&&ButtonDownflag==0&&Button<m_State.GetCurrentfloor())//若需要停下,且加入的Button比该电梯所在楼层小
	m_Button[Button]=ButtonPress;//向该电梯Button数组中添加目标层
	else if(ButtonUpflag==1&&ButtonDownflag==0&&Button>m_State.GetCurrentfloor())//若要停下，且加入Button比该电梯所在层大
		m_TempButton[Button]=ButtonPress;//向该电梯临时Button数组中添加目标层
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&Button>m_State.GetCurrentfloor())//若不要停下，且加入Button比该电梯所在层大
		m_Button[Button]=ButtonPress;////向该电梯Button数组中添加目标层
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&Button<m_State.GetCurrentfloor())////若不要停下，且加入Button比该电梯所在层小
		m_TempButton[Button]=ButtonPress;//向该电梯临时Button数组中添加目标层
	else if(ButtonUpflag==0&&ButtonDownflag==0)
	{
		ChangeButton();
		//m_Button[Button]=ButtonPress;
		
		int ButtonUpflag=0;
	int ButtonDownflag=0;
	for(int i=1;i<m_State.GetCurrentfloor();i++)//检查第一层到该层要不要停
	{
		if(m_Button[i]==ButtonPress)//若需要停下
			ButtonUpflag=1;
	}
	for(int i=m_State.GetCurrentfloor();i<11;i++)//检查该层到第十层要不要停
	{
		if(m_Button[i]==ButtonPress)//若需要停下
			ButtonDownflag=1;
	}
		if(ButtonUpflag==1&&ButtonDownflag==0&&Button<m_State.GetCurrentfloor())//若需要停下,且加入的Button比该电梯所在楼层小
	m_Button[Button]=ButtonPress;//向该电梯Button数组中添加目标层
	else if(ButtonUpflag==1&&ButtonDownflag==0&&Button>m_State.GetCurrentfloor())//若要停下，且加入Button比该电梯所在层大
		m_TempButton[Button]=ButtonPress;//向该电梯临时Button数组中添加目标层
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&Button>m_State.GetCurrentfloor())//若不要停下，且加入Button比该电梯所在层大
		m_Button[Button]=ButtonPress;////向该电梯Button数组中添加目标层
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&Button<m_State.GetCurrentfloor())////若不要停下，且加入Button比该电梯所在层小
		m_TempButton[Button]=ButtonPress;//向该电梯临时Button数组中添加目标层
	else if(ButtonUpflag==0&&ButtonDownflag==0)
         m_Button[Button]=ButtonPress;
	}
	for(int i=0;i<PersonNumber;i++)
	AddData(m_AddPersonButton[Button],PersonList[i]);
	
}
	
}
void Elevator::GetButton(int* &ButtonArray)
{//获取Button数组,给ButtonAray，此时应注意是否要将其传入Button中
	int i;
	for(i=1;i<11;i++)
		ButtonArray[i]=m_Button[i];
}
void Elevator::ChangeButton()//将新加入的Button导入Button数组中，进行电梯的下一轮移动
{
	for(int i=1;i<11;i++)
		m_Button[i]=m_TempButton[i];//将新加入的Button导入Button数组中，进行电梯的下一轮移动
	for(int i=1;i<11;i++)
		m_TempButton[i]=Un_ButtonPress;//将临时Button清空
}
void Elevator::CheckAndChangeButton()//根据ElevatorState中的当前层数改变Button数组，到站了则置Un_ButtonPress
{
	m_Button[m_State.GetCurrentfloor()]=Un_ButtonPress;
	//到了该层则修改Button数组
}
void Elevator::SetButton(int* LeftPerList,Person* PersonArray,int LeftPerListLength)//传入要停留的楼层号,停下之后由停下的这一层乘客目标层集合决定,该函数构建一个数组
{
	//注意要将乘客的目标层分类，分别填入Button数组和临时Button数组中
	
	if(PersonArray[LeftPerList[0]].GetCurrentfloor()==m_State.GetCurrentfloor())
	{//如果所选电梯就在这一层

	int ButtonUpflag=0;
	int ButtonDownflag=0;
	for(int i=1;i<m_State.GetCurrentfloor();i++)//检查第一层到该层要不要停
	{
		if(m_Button[i]==ButtonPress)//若需要停下
			ButtonUpflag=1;
	}

	for(int i=m_State.GetCurrentfloor();i<11;i++)//检查该层到第十层要不要停
	{
		if(m_Button[i]==ButtonPress)//若需要停下
			ButtonDownflag=1;
	}
	    
		///////////////////////////////////
		for(int i=0;i<LeftPerListLength;i++)
		{
			if(ButtonUpflag==1&&ButtonDownflag==0&&PersonArray[LeftPerList[i]].GetAimfloor()<m_State.GetCurrentfloor())//若需要停下,且加入的Button比该电梯所在楼层小
	m_Button[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//向该电梯Button数组中添加目标层
	else if(ButtonUpflag==1&&ButtonDownflag==0&&PersonArray[LeftPerList[i]].GetAimfloor()>m_State.GetCurrentfloor())//若要停下，且加入Button比该电梯所在层大
		m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//向该电梯临时Button数组中添加目标层
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&PersonArray[LeftPerList[i]].GetAimfloor()>m_State.GetCurrentfloor())//若不要停下，且加入Button比该电梯所在层大
		m_Button[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;////向该电梯Button数组中添加目标层
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&PersonArray[LeftPerList[i]].GetAimfloor()<m_State.GetCurrentfloor())////若不要停下，且加入Button比该电梯所在层小
		m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//向该电梯临时Button数组中添加目标层
	else if(ButtonUpflag==0&&ButtonDownflag==0)
	{
     
	  m_Button[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;
	  //全部倒入Button中
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
	for(int i=1;i<m_State.GetCurrentfloor();i++)//检查第一层到该层要不要停
	{
		if(m_Button[i]==ButtonPress)//若需要停下
			ButtonUpflag=1;
	}

	for(int i=m_State.GetCurrentfloor();i<11;i++)//检查该层到第十层要不要停
	{
		if(m_Button[i]==ButtonPress)//若需要停下
			ButtonDownflag=1;
	}
	if(ButtonUpflag==0&&ButtonDownflag==0)
	{
		 ChangeButton();//将临时Button导入其中
	  //在判断方向
	}
	for(int i=0;i<LeftPerListLength;i++)
	{
		if(ButtonUpflag==1&&ButtonDownflag==0&&PersonArray[LeftPerList[i]].GetAimfloor()<m_State.GetCurrentfloor())//若需要停下,且加入的Button比该电梯所在楼层小
	m_Button[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//向该电梯Button数组中添加目标层
	else if(ButtonUpflag==1&&ButtonDownflag==0&&PersonArray[LeftPerList[i]].GetAimfloor()>m_State.GetCurrentfloor())//若要停下，且加入Button比该电梯所在层大
		m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//向该电梯临时Button数组中添加目标层
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&PersonArray[LeftPerList[i]].GetAimfloor()>m_State.GetCurrentfloor())//若不要停下，且加入Button比该电梯所在层大
		m_Button[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;////向该电梯Button数组中添加目标层
	else if(ButtonUpflag!=1&&ButtonDownflag==1&&PersonArray[LeftPerList[i]].GetAimfloor()<m_State.GetCurrentfloor())////若不要停下，且加入Button比该电梯所在层小
		m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;//向该电梯临时Button数组中添加目标层
	else if(ButtonUpflag==0&&ButtonDownflag==0)
	{
     
	  m_TempButton[PersonArray[LeftPerList[i]].GetAimfloor()]=ButtonPress;
	  //全部倒入临时Button中
	}
	}*/
	}
}

void Elevator::ChangState(Person* PersonArray)
	//改变当前状态，设置当前层数,设置人数,电梯上下状态，参数为搭上电梯的人的列表，用于获取乘客的目标层而控制乘客数量
{	//因为每到一层，人数均可能变化
	//注意如果改变了电梯的上下状态，则应调用ChangButton函数,次改变为瞬变
	//电梯静止时，设置了一个表示静止时长的变量StopTime，据此判断状态是否改变
	//到下一层人数可能增加
	if(m_State.StopTime>0)//说明静止时间还未到
		m_State.DecreaseStopTime();//减小静止时间，状态不改变
	else
{
		//此时要利用Button数组
		//当Button数组里所有的元素均为Un_ButtonPress是电梯的方向一定改变
		//根据Button数组先判断电梯的方向
	int ButtonDownflag=0;
	for(int i=1;i<m_State.GetCurrentfloor();i++)//检查第一层到该层要不要停
	{
		if(m_Button[i]==ButtonPress)//若需要停下
			ButtonDownflag=1;
	}
	int ButtonUpflag=0;
	for(int i=m_State.GetCurrentfloor();i<11;i++)//检查该层到第10层要不要停
	{
		if(m_Button[i]==ButtonPress)//若需要停下，则表示电梯向上运动
			ButtonUpflag=1;
	}
	//如果ButtonDownflag==1表示电梯向下
	//如果ButtonUpflag==1表示电梯向上
	if(ButtonDownflag==1&&ButtonUpflag==0)
	{//表示，电梯向下运动
	m_State.SetDeractionState(DownState);
	//设置电梯方向状态
	//此时电梯的方向向下
	 
	 
     if(m_Button[m_State.GetCurrentfloor()-1]==ButtonPress)
	       {
	//如果下一层对映Button数组中为ButtonPress
	//表示在下一层需要停下
	
    LinkList p;//筛选出要下电梯的人
	for(p=m_State.ElevatorList->next;p!=NULL;)
	{ if(PersonArray[p->data].GetAimfloor()==m_State.GetCurrentfloor()-1) 
	           {//表示该乘客目标层即为下一层
				   LinkList q=p->next;
			 m_State.DestroyPerson(1); //怎电梯中人数减少1
			  PersonArray[p->data].SetCurrentfloor();//人到目标层后，改变其状态
			 PersonArray[p->data].SetInWorkState();//设置其进入工作状态
			 DeleteData(m_State.ElevatorList,p->data);//从电梯人列表中删除该乘客
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
		if(PersonArray[p->data].GetPatientTime()>5&&m_State.GetElevatorPersonNumber()<24)//如果到下一层时，忍耐时间还未到
		{
			m_State.AddPerson(1);//向电梯中加入该人
			AddData(m_State.ElevatorList,p->data);
			PersonArray[p->data].m_PatientTime=1000;//表示该人已经无忍耐时间了
		}
		else//如果忍耐时间到了
		{
			PersonArray[p->data].SetCurrentfloor();
			PersonArray[p->data].SetInWorkState();//表示他走楼梯，并工作
		}
	}


	 m_Button[m_State.GetCurrentfloor()-1]=Un_ButtonPress;//改变电梯的Button数组
	 m_TempButton[m_State.GetCurrentfloor()-1]=Un_ButtonPress;
	 //将其设置为停留状态
	 //初始化等待时间15s
		m_State.InitStopTime();
	 }
	 //改变电梯所在层,即为当前层数-1
	 m_State.SetCurrentfloor(m_State.GetCurrentfloor()-1);
	 m_State.CheckStopState();
	}
	else if(ButtonDownflag==0&&ButtonUpflag==1)
	{//表示电梯向上运动
		m_State.SetDeractionState(UpState);
		 
	 if(m_Button[m_State.GetCurrentfloor()+1]==ButtonPress)
	 {
		
    LinkList p;//筛选出要下电梯的人
	for(p=m_State.ElevatorList->next;p!=NULL;)
		{if(PersonArray[p->data].GetAimfloor()==m_State.GetCurrentfloor()+1) 
	    {//表示该乘客目标层即为下一层
			 LinkList q=p->next;
			 m_State.DestroyPerson(1); //怎电梯中人数减少1
			 PersonArray[p->data].SetCurrentfloor();//人到目标层后，改变其状态
			 PersonArray[p->data].SetInWorkState();//设置其进入工作状态
			 DeleteData(m_State.ElevatorList,p->data);//从电梯人列表中删除该乘客
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
		if(PersonArray[p->data].GetPatientTime()>5&&m_State.GetElevatorPersonNumber()<24)//如果到下一层时，忍耐时间还未到
		{
			m_State.AddPerson(1);//向电梯中加入该人
			AddData(m_State.ElevatorList,p->data);
			PersonArray[p->data].m_PatientTime=1000;//表示该人已经无忍耐时间了
		}
		else//如果忍耐时间到了
		{
			PersonArray[p->data].SetCurrentfloor();
			PersonArray[p->data].SetInWorkState();//表示他走楼梯，并工作
		}
	}
	 m_Button[m_State.GetCurrentfloor()+1]=Un_ButtonPress;//改变电梯的Button数组
	 m_TempButton[m_State.GetCurrentfloor()+1]=Un_ButtonPress;
	 //将其设置为停留状态
	 //初始化等待时间15s
		m_State.InitStopTime();
	 }
	 //改变电梯所在层,即为当前层数+1
	 m_State.SetCurrentfloor(m_State.GetCurrentfloor()+1);
	 m_State.CheckStopState();
	}
	else if(ButtonDownflag==0&&ButtonUpflag==0)
	{//表示此时电梯已完成工作，进入下一次运送
		
		ChangeButton();//将临时Button导入Button中
		//需要进行状态改变
		/////////////Test//////////////
		m_Button[m_State.GetCurrentfloor()]=Un_ButtonPress;
		//m_State.SetDeractionState(StopState);//将电梯设置为StopState状态
		int Stateflag=0;
		for(int i=1;i<11;i++)
		{//如果有乘客选它
			if(m_Button[i]==ButtonPress)
				Stateflag=1;
		}
	if(m_State.GetDrectionState()==UpState&&Stateflag)
	{//说明该电梯刚才的状态为向上状态，现在要改变其状态
			m_State.SetDeractionState(DownState);
			//将其改成向下的状态
			//此时便根据下一层来修改电梯的状态
			
     if(m_Button[m_State.GetCurrentfloor()-1]==ButtonPress)
	 {
	//如果下一层对映Button数组中为ButtonPress
	//表示在下一层需要停下
    LinkList p;//筛选出要下电梯的人
	for(p=m_State.ElevatorList->next;p!=NULL;)
		{if(PersonArray[p->data].GetAimfloor()==m_State.GetCurrentfloor()-1) 
	    {//表示该乘客目标层即为下一层
			LinkList q=p->next;
			 m_State.DestroyPerson(1); //怎电梯中人数减少1
			  PersonArray[p->data].SetCurrentfloor();//人到目标层后，改变其状态
			 PersonArray[p->data].SetInWorkState();//设置其进入工作状态
			 DeleteData(m_State.ElevatorList,p->data);//从电梯人列表中删除该乘客
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
		if(PersonArray[p->data].GetPatientTime()>5&&m_State.GetElevatorPersonNumber()<24)//如果到下一层时，忍耐时间还未到
		{
			m_State.AddPerson(1);//向电梯中加入该人
			AddData(m_State.ElevatorList,p->data);
			PersonArray[p->data].m_PatientTime=1000;//表示该人已经无忍耐时间了
		}
		else//如果忍耐时间到了
		{
			PersonArray[p->data].SetCurrentfloor();
			PersonArray[p->data].SetInWorkState();//表示他走楼梯，并工作
		}
	}
	 m_Button[m_State.GetCurrentfloor()-1]=Un_ButtonPress;//改变电梯的Button数组
	  m_TempButton[m_State.GetCurrentfloor()-1]=Un_ButtonPress;
	 //将其设置为停留状态
	 //初始化等待时间15s
		m_State.InitStopTime();
		}
	 if(m_State.GetCurrentfloor()!=1)
	 m_State.SetCurrentfloor(m_State.GetCurrentfloor()-1);
	        //楼层减一
	}
	else if(m_State.GetDrectionState()==DownState&&Stateflag)
	{
      
     m_State.SetDeractionState(UpState);
		
	 if(m_Button[m_State.GetCurrentfloor()+1]==ButtonPress)
	 {//如果上一层的Button状态为ButtonPress
		  
    LinkList p;//筛选出要下电梯的人
	for(p=m_State.ElevatorList->next;p!=NULL;)
		{if(PersonArray[p->data].GetAimfloor()==m_State.GetCurrentfloor()+1) 
	    {//表示该乘客目标层即为下一层
			LinkList q=p->next;
			 m_State.DestroyPerson(1); //怎电梯中人数减少1
			  PersonArray[p->data].SetCurrentfloor();//人到目标层后，改变其状态
			 PersonArray[p->data].SetInWorkState();//设置其进入工作状态
			 DeleteData(m_State.ElevatorList,p->data);//从电梯人列表中删除该乘客
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
		if(PersonArray[p->data].GetPatientTime()>5&&m_State.GetElevatorPersonNumber()<24)//如果到下一层时，忍耐时间还未到
		{
			m_State.AddPerson(1);//向电梯中加入该人
			AddData(m_State.ElevatorList,p->data);
			PersonArray[p->data].m_PatientTime=1000;//表示该人已经无忍耐时间了
		}
		else//如果忍耐时间到了
		{
			PersonArray[p->data].SetCurrentfloor();
			PersonArray[p->data].SetInWorkState();//表示他走楼梯，并工作
		}
	}
	 
		 m_TempButton[m_State.GetCurrentfloor()+1]=Un_ButtonPress;
		 m_Button[m_State.GetCurrentfloor()+1]=Un_ButtonPress;//改变电梯的Button数组
	 //将其设置为停留状态
	 //初始化等待时间15s
		m_State.InitStopTime();
	 }
	  //改变电梯所在层,即为当前层数+1
	 if(m_State.GetCurrentfloor()!=10)
	 m_State.SetCurrentfloor(m_State.GetCurrentfloor()+1);
	}
	}
}

}
