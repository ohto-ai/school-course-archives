void RemoveStudent	(StuNodeLink Stu)
{
	if(Stu==NULL)
		return;
	if(Stu->Last==NULL)//头结点
		return;
	Stu->Last->Next=Stu->Next;
	if(Stu->Next!=NULL)
		Stu->Next->Last=Stu->Last;
	free(Stu);
}
void RemoveBook		(BokNodeLink Bok)
{
	if(Bok==NULL)
		return;
	if(Bok->Last==NULL)//头结点
		return;
	Bok->Last->Next=Bok->Next;
	if(Bok->Next!=NULL)
		Bok->Next->Last=Bok->Last;
	free(Bok); 
}
void RemoveBorrow	(BorNodeLink Bor)
{
	if(Bor==NULL)
		return;
	if(Bor->Last==NULL)//头结点
		return;
	Bor->Last->Next=Bor->Next;
	if(Bor->Next!=NULL)
		Bor->Next->Last=Bor->Last;
	free(Bor);
}

void FreeStu()
{
	if(StuListHead.Next==NULL)//0
		return;
	if(StuListHead.Next->Next==NULL)//1
	{
		free(StuListHead.Next);
		return;
	}
	StuNodeLink Stu;
	for(Stu=StuListHead.Next->Next;Stu->Next!=NULL;Stu=Stu->Next)
	{
		free(Stu->Last);
	}
	free(Stu->Next);
	free(Stu);
}
void FreeBok()
{
	if(BokListHead.Next==NULL)//0
		return;
	if(BokListHead.Next->Next==NULL)//1
	{
		free(BokListHead.Next);
		return;
	}
	BokNodeLink Bok;
	for(Bok=BokListHead.Next->Next;Bok->Next!=NULL;Bok=Bok->Next)
	{
		free(Bok->Last);
	}
	free(Bok->Next);
	free(Bok);
}

void FreeBor()
{
	if(BorListHead.Next==NULL)//0
		return;
	if(BorListHead.Next->Next==NULL)//1
	{
		free(BorListHead.Next);
		return;
	}
	BorNodeLink Bor;
	for(Bor=BorListHead.Next->Next;Bor->Next!=NULL;Bor=Bor->Next)
	{
		free(Bor->Last);
	}
	free(Bor->Next);
	free(Bor);
}