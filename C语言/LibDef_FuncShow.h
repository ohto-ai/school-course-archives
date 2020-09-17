 
extern int OutCutString(int Len,const char*Formt,...);
extern HANDLE HConsoleOut;

#define _PUT_STU_TITLE_ puts("\nѧ��         ����         ����ϵ��")
#define _PUT_STU_ \
			OutCutString(13," %-12s",Stu->StuNum);\
			OutCutString(11," %-10s",Stu->StuName);\
			OutCutString(32," %-30s\n",Stu->Department)

#define _PUT_BOK_TITLE_ puts("\nͼ����   ����                 ������                �۸�  ״̬")
#define _PUT_BOK_ \
			OutCutString(11,"%-10s ",Bok->BookNum);\
			OutCutString(21,"%-20s ",Bok->BookName);\
			OutCutString(21,"%-20s ",Bok->PublishHouse);\
			OutCutString(7,"%6.2f ",Bok->Price);\
			OutCutString(6,"%-4s\n",Bok->HasBorrow?"���":"�ڼ�")
 
#define _PUT_BOR_TITLE_ puts("\nѧ��        ͼ����    ��������    ��������\t���ڷ���")
#define _PUT_BOR_NUM_ \
			OutCutString(13,"%-12s ",Bor->StuNum);\
			OutCutString(11,"%-10s ",Bor->BookNum);

#define _PUT_BOR_TIME_ OutCutString(11,"%4d/%02d/%02d ",TmpTime->tm_year+1900,TmpTime->tm_mon+1,TmpTime->tm_mday);

#define _PUT_BOR_BTIMEERROR_ OutCutString(11,"%9s  ","TimeError")
#define _PUT_BOR_RTIMEERROR_ OutCutString(11,"%9s  ","��δ�黹")
#define _PUT_BOR_FINE_ OutCutString(7,"%6.2f\n",Bor->Fine)

#define _PUT_FINE_TITLE_ puts("\nѧ��\t\t����\t�鼮���\t���ڷ���")
#define _PUT_FINE_ printf("%s\t%s\t%s\t\t%8.2f\n",Stu->StuNum,Stu->StuName,Tmp->BookNum,Tmp->Fine)



int ShowStudent(StuNodeLink Stu)
{
	if(Stu==NULL)
		return -1;
	
	SetConsoleTextAttribute(HConsoleOut,TEXT_TITLE_COL);
	_PUT_STU_TITLE_;
	SetConsoleTextAttribute(HConsoleOut,TEXT_STU_COL);
	_PUT_STU_;
	SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);
	return 0;
}
int ShowBook	(BokNodeLink Bok)
{
	if(Bok==NULL)
		return -1;
	
	SetConsoleTextAttribute(HConsoleOut,TEXT_TITLE_COL);
	_PUT_BOK_TITLE_;
	if(Bok->HasBorrow)
		SetConsoleTextAttribute(HConsoleOut,TEXT_BOK_COL_D);
	else
		SetConsoleTextAttribute(HConsoleOut,TEXT_BOK_COL);
	_PUT_BOK_;
	SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);
	return 0;
}
int ShowBorrow	(BorNodeLink Bor)
{
	if(Bor==NULL)
		return -1;
	tm *TmpTime;//ʱ��ṹ��
	CalculateFine(Bor);//���㷣��
	
	SetConsoleTextAttribute(HConsoleOut,TEXT_TITLE_COL);
	_PUT_BOR_TITLE_;
	if(Bor->RDate==0)//��δ�黹
		SetConsoleTextAttribute(HConsoleOut,TEXT_BOR_COL_D);
	else
		SetConsoleTextAttribute(HConsoleOut,TEXT_BOR_COL);
	_PUT_BOR_NUM_;
	if(Bor->BDate!=0)
	{
		TmpTime=localtime(&Bor->BDate);//ת����������
		_PUT_BOR_TIME_;
	}
	else
	{
		_PUT_BOR_BTIMEERROR_;
	}
	if(Bor->RDate!=0)
	{
		TmpTime=localtime(&Bor->RDate);//ת����������
		_PUT_BOR_TIME_;
	}
	else
	{
		_PUT_BOR_RTIMEERROR_;
	}
	_PUT_BOR_FINE_;
	SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);
	return 0;
}
int ShowStudentList(void)
{	
	StuNodeLink Stu;
	int Count=0;
	SetConsoleTextAttribute(HConsoleOut,TEXT_TITLE_COL);
	_PUT_STU_TITLE_;
	SetConsoleTextAttribute(HConsoleOut,TEXT_STU_COL);
	for(Stu=StuListHead.Next;Stu!=NULL;Stu=Stu->Next)
	{
		++Count;
		_PUT_STU_;
	}
	SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);
	return Count;
}
int ShowBookList	(void)
{
	BokNodeLink Bok;
	int Count=0;
	SetConsoleTextAttribute(HConsoleOut,TEXT_TITLE_COL);
	_PUT_BOK_TITLE_;
	
	for(Bok=BokListHead.Next;Bok!=NULL;Bok=Bok->Next)
	{
		++Count;
		if(Bok->HasBorrow)
			SetConsoleTextAttribute(HConsoleOut,TEXT_BOK_COL_D);
		else
			SetConsoleTextAttribute(HConsoleOut,TEXT_BOK_COL);
		_PUT_BOK_;
	}
	SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);
	return Count;
}
int ShowBorrowList	(void)
{
	BorNodeLink Bor;
	int Count=0;
	tm *TmpTime;//ʱ��ṹ��
	SetConsoleTextAttribute(HConsoleOut,TEXT_TITLE_COL);
	_PUT_BOR_TITLE_;
	
	for(Bor=BorListHead.Next;Bor!=NULL;Bor=Bor->Next)
	{
		++Count;
		CalculateFine(Bor);//���㷣��
		if(Bor->RDate==0)//��δ�黹
			SetConsoleTextAttribute(HConsoleOut,TEXT_BOR_COL_D);
		else
			SetConsoleTextAttribute(HConsoleOut,TEXT_BOR_COL);
		_PUT_BOR_NUM_;
		if(Bor->BDate!=0)
		{
			TmpTime=localtime(&Bor->BDate);//ת����������
			_PUT_BOR_TIME_;
		}
		else
		{
			_PUT_BOR_BTIMEERROR_;
		}
		if(Bor->RDate!=0)
		{
			TmpTime=localtime(&Bor->RDate);//ת����������
			_PUT_BOR_TIME_;
		}
		else
		{
			_PUT_BOR_RTIMEERROR_;
		}
		_PUT_BOR_FINE_;
	}
	SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);
	return Count;
}
int ShowFine(StuNodeLink Stu)
{
	if(Stu==NULL)
		return -1;
	int Count=0;
	BorNodeLink Tmp;
	SetConsoleTextAttribute(HConsoleOut,TEXT_TITLE_COL);
	_PUT_FINE_TITLE_;
	SetConsoleTextAttribute(HConsoleOut,TEXT_FINE_COL);

	ResetLastFindBorrow();
	while(NULL!=(Tmp=FindBorrow(Stu,NULL)))
	{
		++Count;
		CalculateFine(Tmp);//���㷣��
		_PUT_FINE_;
	}
	SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);
	return Count;
}
int ShowFineList()
{
	int Count=0;
	StuNodeLink Stu;
	BorNodeLink Tmp;
	SetConsoleTextAttribute(HConsoleOut,TEXT_TITLE_COL);
	_PUT_FINE_TITLE_;
	SetConsoleTextAttribute(HConsoleOut,TEXT_FINE_COL);

	ResetLastFindBorrow();
	ResetLastFindStudent();
	while(NULL!=(Tmp=FindBorrow(NULL,NULL)))
	{
		++Count;
		CalculateFine(Tmp);//���㷣��
		Stu=FindStudent(Tmp->StuNum,NULL,NULL);
		_PUT_FINE_;
	}
	SetConsoleTextAttribute(HConsoleOut,TEXT_DEF_COL);
	return Count;
}