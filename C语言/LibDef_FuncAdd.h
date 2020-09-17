
//���ѧ��
StuNodeLink AddStudent(char*StuNum,		//ѧ��
				   char*StuName,		//����
				   char*Department	//ϵ��
				   )
{
	//�����ڴ�
	if(NULL==(pStuListTail->Next=(StuNodeLink )calloc(1,sizeof(StuNode))))
		return NULL; 
	
	pStuListTail->Next->Last=pStuListTail;	//�����½ڵ��ǰ��
	pStuListTail=pStuListTail->Next;		//���βָ��
	pStuListTail->Last->Next=pStuListTail;	//���þɽڵ�ĺ��
	
	//д������
	strcpy(pStuListTail->StuNum,StuNum);	
	strcpy(pStuListTail->StuName,StuName);
	strcpy(pStuListTail->Department,Department);
	return pStuListTail;
}
//����鼮
BokNodeLink AddBook(char*BokNum,			//���
				char*BokName,		//����
				char*PublishHouse,	//������
				double Price			//����
				)
{
	//�����ڴ�
	if(NULL==(pBokListTail->Next=(BokNodeLink )calloc(1,sizeof(BokNode))))
		return NULL;
	
	pBokListTail->Next->Last=pBokListTail;	//�����½ڵ��ǰ��
	pBokListTail=pBokListTail->Next;		//���βָ��
	pBokListTail->Last->Next=pBokListTail;	//���þɽڵ�ĺ��
	
	//д������
	strcpy(pBokListTail->BookNum,BokNum);
	strcpy(pBokListTail->BookName,BokName);
	strcpy(pBokListTail->PublishHouse,PublishHouse);
	pBokListTail->HasBorrow=false;
	pBokListTail->Price=Price;
	return pBokListTail;
}
//����
int LogBor(StuNodeLink Stu,		//ѧ��
		   BokNodeLink Bok		//ͼ��
		   )
{
	if(Stu==NULL||Bok==NULL)
		return -1;
	if(Bok->HasBorrow)//�Ѿ�������
		return -2;
	//����µĽ��ļ�¼
	//�����ڴ�
	if(NULL==(pBorListTail->Next=(BorNodeLink )calloc(1,sizeof(BorNode))))
		return -3;
	
	
	pBorListTail->Next->Last=pBorListTail;	//�����½ڵ��ǰ��
	pBorListTail=pBorListTail->Next;		//���βָ��
	pBorListTail->Last->Next=pBorListTail;	//���þɽڵ�ĺ��
	
	//��¼ʱ��
	pBorListTail->BDate=time(NULL);	//�������ʱ��
	pBorListTail->RDate=0;			//�����δ�黹
	//��¼�鼮��ѧ��
	strcpy(pBorListTail->StuNum,Stu->StuNum);
	strcpy(pBorListTail->BookNum,Bok->BookNum);
	//���÷���Ϊ0
	pBorListTail->Fine=0;
	
	Bok->HasBorrow=true;			//����Ѿ�������
	
	return 0;
}
int LogRet(BorNodeLink Bor		//���ļ�¼
		   )
{
	if(Bor==NULL)
		return -1;
	//��¼ʱ��
	Bor->RDate=time(NULL);	//�������ʱ��
	
	BokNodeLink Tmp=FindFirstBook(Bor->BookNum,NULL,NULL);
	if(Tmp)
		Tmp->HasBorrow=false;//����Ѿ�����
	
	return 0;
}
