static StuNodeLink LastFindStu=NULL;
static BokNodeLink LastFindBok=NULL;
static BorNodeLink LastFindBor=NULL;

StuNodeLink GetLastFindStudent(void)
{
	if(LastFindStu!=NULL)
		return LastFindStu->Last;
	else
		return NULL;
}
StuNodeLink ResetLastFindStudent(void)
{
	return LastFindStu=StuListHead.Next;
}

StuNodeLink FindStudent(char*StuNum,char*StuName,char*Department) 
{
	
	if(StuNum!=NULL&&StuNum[0]==0)
		StuNum=NULL;
	if(StuName!=NULL&&StuName[0]==0)
		StuName=NULL;
	if(Department!=NULL&&Department[0]==0)
		Department=NULL;
	if(LastFindStu==NULL){
		LastFindStu=StuListHead.Next;
		return NULL;
	}
	//������һ������״̬
	static char*sStuNum=NULL;
	static char*sStuName=NULL;
	static char*sDepartment=NULL;
	if(sStuNum!=StuNum
		&&sStuName!=StuName
		&&sDepartment!=Department)//���ϴ�������ͬ
	{
		sStuNum=StuNum;
		sStuName=StuName;
		sDepartment=Department;
		LastFindStu=StuListHead.Next;//��������
	}
	StuNodeLink TmpNode;
	for(TmpNode=LastFindStu;TmpNode!=NULL;TmpNode=TmpNode->Next)
	{
		if(	(StuNum==NULL?true:(!strcmp(TmpNode->StuNum,StuNum)))
			&&(StuName==NULL?true:(!strcmp(TmpNode->StuName,StuName)))
			&&(Department==NULL?true:(!strcmp(TmpNode->Department,Department)))	)//�ҵ�
		{
			LastFindStu=TmpNode->Next;
			return TmpNode;
		}
	}
	//���ҵ����
	return LastFindStu=NULL;
}
StuNodeLink FindFirstStudent(char*StuNum,char*StuName,char*Department)
{
	if(StuNum!=NULL&&StuNum[0]==0)
		StuNum=NULL;
	if(StuName!=NULL&&StuName[0]==0)
		StuName=NULL;
	if(Department!=NULL&&Department[0]==0)
		Department=NULL;
	StuNodeLink TmpNode;
	for(TmpNode=StuListHead.Next;TmpNode!=NULL;TmpNode=TmpNode->Next)
	{
		if(	(StuNum==NULL?true:(!strcmp(TmpNode->StuNum,StuNum)))
			&&(StuName==NULL?true:(!strcmp(TmpNode->StuName,StuName)))
			&&(Department==NULL?true:(!strcmp(TmpNode->Department,Department)))	)//�ҵ�
		{
			return TmpNode;
		}
	}
	//���ҵ����
	return NULL;
}

///////////////////////
BokNodeLink GetLastFindBook(void)
{
	if(LastFindBok!=NULL)
		return LastFindBok->Last;
	else
		return NULL;
}
BokNodeLink ResetLastFindBook(void)
{
	return LastFindBok=BokListHead.Next;
}
BokNodeLink FindBook(char*BokNum,char*BokName,char*PublishHouse)
{
	if(BokNum!=NULL&&BokNum[0]==0)
		BokNum=NULL;
	if(BokName!=NULL&&BokName[0]==0)
		BokName=NULL;
	if(PublishHouse!=NULL&&PublishHouse[0]==0)
		PublishHouse=NULL;
	if(LastFindBok==NULL){
		LastFindBok=BokListHead.Next;
		return NULL;
	}
	//������һ������״̬
	static char*sBokNum=NULL;
	static char*sBokName=NULL;
	static char*sPublishHouse=NULL;
	if(sBokNum!=BokNum
		&&sBokName!=BokName
		&&sPublishHouse!=PublishHouse)//���ϴ�������ͬ
	{
		sBokNum=BokNum;
		sBokName=BokName;
		sPublishHouse=PublishHouse;
		LastFindBok=BokListHead.Next;//��������
	}
	BokNodeLink TmpNode;
	for(TmpNode=LastFindBok;TmpNode!=NULL;TmpNode=TmpNode->Next)
	{
		if(	(BokNum==NULL?true:(!strcmp(TmpNode->BookNum,BokNum)))
			&&(BokName==NULL?true:(!strcmp(TmpNode->BookName,BokName)))
			&&(PublishHouse==NULL?true:(!strcmp(TmpNode->PublishHouse,PublishHouse)))	)//�ҵ�
		{
			LastFindBok=TmpNode->Next;
			return TmpNode;
		}
	}
	//���ҵ����
	return LastFindBok=NULL;
}
BokNodeLink FindFirstBook(char*BokNum,char*BokName,char*PublishHouse)
{
	
	if(BokNum!=NULL&&BokNum[0]==0)
		BokNum=NULL;
	if(BokName!=NULL&&BokName[0]==0)
		BokName=NULL;
	if(PublishHouse!=NULL&&PublishHouse[0]==0)
		PublishHouse=NULL;
	BokNodeLink TmpNode;
	for(TmpNode=BokListHead.Next;TmpNode!=NULL;TmpNode=TmpNode->Next)
	{
		if(	(BokNum==NULL?true:(!strcmp(TmpNode->BookNum,BokNum)))
			&&(BokName==NULL?true:(!strcmp(TmpNode->BookName,BokName)))
			&&(PublishHouse==NULL?true:(!strcmp(TmpNode->PublishHouse,PublishHouse)))	)//�ҵ�
		{
			return TmpNode;
		}
	}
	//���ҵ����
	return NULL;
}

///////////////////////
BorNodeLink GetLastFindBorrow(void)
{
	if(LastFindBor!=NULL)
		return LastFindBor->Last;
	else
		return NULL;
}
BorNodeLink ResetLastFindBorrow(void)
{
	return LastFindBor=BorListHead.Next;
}
BorNodeLink FindBorrow(StuNodeLink Stu,BokNodeLink Bok)
{
	if(LastFindBor==NULL){
		LastFindBor=BorListHead.Next;
		return NULL;
	}
	//������һ������״̬
	static StuNodeLink sStu=NULL;
	static BokNodeLink sBok=NULL;
	if(sStu!=Stu&&sBok!=Bok)//���ϴ�������ͬ
	{
		sStu=Stu;
		sBok=Bok;
		LastFindBor=BorListHead.Next;//��������
	}
	BorNodeLink TmpNode;
	for(TmpNode=LastFindBor;TmpNode!=NULL;TmpNode=TmpNode->Next)
	{
		if(	(Stu==NULL?true:(!strcmp(TmpNode->StuNum,Stu->StuNum)))
			&&(Bok==NULL?true:(!strcmp(TmpNode->BookNum,Bok->BookNum)))	)//�ҵ�
		{
			LastFindBor=TmpNode->Next;
			return TmpNode;
		}
	}
	//���ҵ����
	return LastFindBor=NULL;
}
BorNodeLink FindFirstBorrow(StuNodeLink Stu,BokNodeLink Bok)
{
	if(Stu==NULL&&Bok==NULL)
		return NULL;
	BorNodeLink TmpNode;
	for(TmpNode=BorListHead.Next;TmpNode!=NULL;TmpNode=TmpNode->Next)
	{
		if(	(Stu==NULL?true:(!strcmp(TmpNode->StuNum,Stu->StuNum)))
			&&(Bok==NULL?true:(!strcmp(TmpNode->BookNum,Bok->BookNum)))	)//�ҵ�
		{
			return TmpNode;
		}
	}
	//���ҵ����
	return NULL;
}
//////////////////////
BorNodeLink FindUnRet(StuNodeLink Stu,BokNodeLink Bok)
{
	if(LastFindBor==NULL){
		LastFindBor=BorListHead.Next;
		return NULL;
	}
	//������һ������״̬
	static StuNodeLink sStu=NULL;
	static BokNodeLink sBok=NULL;
	if(sStu!=Stu&&sBok!=Bok)//���ϴ�������ͬ
		LastFindBor=BorListHead.Next;//��������
	BorNodeLink TmpNode;
	for(TmpNode=LastFindBor;TmpNode!=NULL;TmpNode=TmpNode->Next)
	{
		if(	(Stu==NULL?true:(!strcmp(TmpNode->StuNum,Stu->StuNum)))
			&&(Bok==NULL?true:(!strcmp(TmpNode->BookNum,Bok->BookNum)))
			&&TmpNode->RDate==0)//�ҵ�
		{
			LastFindBor=TmpNode->Next;
			return TmpNode;
		}
	}
	//���ҵ����
	return LastFindBor=NULL;
}