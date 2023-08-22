#define StuFile "Student.LibD"
#define BokFile "Book.LibD"
#define BorFile "Borrow.LibD"

int SaveStu()
{
	FILE *fp=fopen(StuFile,"wb");
	StuNodeLink Stu;
	if(fp==NULL)
		return 1;
	int Count=CountStudent();
	fwrite(&Count,sizeof(int),1,fp);//д������
	for(Stu=StuListHead.Next;Stu!=NULL;Stu=Stu->Next)
	{
		fwrite(Stu,sizeof(StuNode),1,fp);
	}
	fclose(fp);
	return 0; 
}
int SaveBok()
{
	FILE *fp=fopen(BokFile,"wb");
	BokNodeLink Bok;
	if(fp==NULL)
		return 1;
	int Count=CountBook();
	fwrite(&Count,sizeof(int),1,fp);//д������
	for(Bok=BokListHead.Next;Bok!=NULL;Bok=Bok->Next)
	{
		fwrite(Bok,sizeof(BokNode),1,fp);
	}
	fclose(fp);
	return 0;
}
int SaveBor()
{
	FILE *fp=fopen(BorFile,"wb");
	BorNodeLink Bor;
	if(fp==NULL)
		return 1;
	int Count=CountBorrow();
	fwrite(&Count,sizeof(int),1,fp);//д������
	for(Bor=BorListHead.Next;Bor!=NULL;Bor=Bor->Next)
	{
		fwrite(Bor,sizeof(BorNode),1,fp);
	}
	fclose(fp);
	return 0;
}

int ReadStu()
{
	FILE *fp=fopen(StuFile,"rb");
	StuNode Stu;
	if(fp==NULL)
		return 1;
	int Count;
	int i;
	fread(&Count,sizeof(int),1,fp);//д������

	for(i=0;i<Count;++i)
	{
		fread(&Stu,sizeof(StuNode),1,fp);

		pStuListTail->Next=(StuNodeLink)calloc(1,sizeof(StuNode));

		pStuListTail->Next->Last=pStuListTail;	//�����½ڵ��ǰ��
		pStuListTail=pStuListTail->Next;		//���βָ��
		pStuListTail->Last->Next=pStuListTail;	//���þɽڵ�ĺ��
		
		//д������
		strcpy(pStuListTail->StuNum,Stu.StuNum);
		strcpy(pStuListTail->StuName,Stu.StuName);
		strcpy(pStuListTail->Department,Stu.Department);
	}
	fclose(fp);
	return 0;
}
int ReadBok()
{
	FILE *fp=fopen(BokFile,"rb");
	BokNode Bok;
	if(fp==NULL)
		return 1;
	int Count;
	int i;
	fread(&Count,sizeof(int),1,fp);//д������

	for(i=0;i<Count;++i)
	{
		fread(&Bok,sizeof(BokNode),1,fp);

		pBokListTail->Next=(BokNodeLink)calloc(1,sizeof(BokNode));

		pBokListTail->Next->Last=pBokListTail;	//�����½ڵ��ǰ��
		pBokListTail=pBokListTail->Next;		//���βָ��
		pBokListTail->Last->Next=pBokListTail;	//���þɽڵ�ĺ��
		
		//д������
		strcpy(pBokListTail->BookNum,Bok.BookNum);
		strcpy(pBokListTail->BookName,Bok.BookName);
		strcpy(pBokListTail->PublishHouse,Bok.PublishHouse);
		pBokListTail->HasBorrow=Bok.HasBorrow;
		pBokListTail->Price=Bok.Price;
	}
	fclose(fp);
	return 0;
}
int ReadBor()
{
	FILE *fp=fopen(BorFile,"rb");
	BorNode Bor;
	if(fp==NULL)
		return 1;
	int Count;
	int i;
	fread(&Count,sizeof(int),1,fp);//д������

	for(i=0;i<Count;++i)
	{
		fread(&Bor,sizeof(BorNode),1,fp);

		pBorListTail->Next=(BorNodeLink)calloc(1,sizeof(BorNode));

		pBorListTail->Next->Last=pBorListTail;	//�����½ڵ��ǰ��
		pBorListTail=pBorListTail->Next;		//���βָ��
		pBorListTail->Last->Next=pBorListTail;	//���þɽڵ�ĺ��
		
		//д������
		strcpy(pBorListTail->BookNum,Bor.BookNum);
		strcpy(pBorListTail->StuNum,Bor.StuNum);
		pBorListTail->BDate=Bor.BDate;
		pBorListTail->RDate=Bor.RDate;
		pBorListTail->Fine=Bor.Fine;
	}
	fclose(fp);
	return 0;
}


int SaveData()
{
	return (SaveStu()<<2)|(SaveBok()<<1)|SaveBor();
}
int ReadData()
{
	return (ReadStu()<<2)|(ReadBok()<<1)|ReadBor();
}
